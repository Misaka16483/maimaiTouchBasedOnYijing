#include "stdafx.h"
#include<algorithm>
#include<string>
#include<map>
#include"messageHandler.h"
#include<thread>
#include<sstream>
#include<set>
#include<shared_mutex>
#include<atomic>
#include<opencv2/opencv.hpp>
#include<Windows.h>
void setHighPriority() {
    HANDLE hThread= GetCurrentThread();
    if (SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST)) {
        AfxMessageBox(L"已设置高优先级");
    }
    else {
        AfxMessageBox(L"设置高优先级失败");
    }
}
messageHandler::messageHandler() {
    //sender = sender;
    setHighPriority();
    if (colorMatrixHeight == 0) {
        cv::Mat colorMatrixMat = cv::imread("D:\\maimai-windows-touch-panel-main\\image\\image_monitor.png");
        colorMatrixHeight = colorMatrixMat.rows;
        colorMatrixWidth = colorMatrixMat.cols;
        colorMatrixRed.resize(colorMatrixHeight);
        
        colorMatrixGreen.resize(colorMatrixHeight);
        colorMatrixBlue.resize(colorMatrixHeight);
        for (int i = 0; i < colorMatrixHeight; i++) {
            colorMatrixRed[i].resize(colorMatrixWidth);
            colorMatrixGreen[i].resize(colorMatrixWidth);
            colorMatrixBlue[i].resize(colorMatrixWidth);
            for (int j = 0; j < colorMatrixWidth; j++) {
                colorMatrixRed[i][j] = colorMatrixMat.at<cv::Vec3b>(i, j)[2];
                colorMatrixGreen[i][j] = colorMatrixMat.at<cv::Vec3b>(i, j)[1];
                colorMatrixBlue[i][j] = colorMatrixMat.at<cv::Vec3b>(i, j)[0];
            }
        }
    }
    serialPort = new CSerial;
    BOOL isSerialOpen = serialPort->Open(33, 9600);
    if (!isSerialOpen) {
        AfxMessageBox(L"串口打开失败");
    }
    else {
        read_Thread = std::thread(&messageHandler::readThread, this);
        read_Thread.detach();
        write_Thread = std::thread(&messageHandler::writeThread, this);
        write_Thread.detach();
    }
}
messageHandler::~messageHandler() {
    serialPort->Close();
    delete serialPort;
}
void messageHandler::writeThread() {
    while (1) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        if (start.load()) {
            std::shared_lock<std::shared_mutex> lock(mtx);
            serialPort->SendData(sendMessage, 9);
        }
    }
}


void messageHandler::readThread() {
    char buf[1024];
    std::string message;
    static int nRecvLen = 0;
    while (1) {
        Sleep(10);
        int nRet = serialPort->ReadAll(buf);
        nRecvLen += nRet;
        message += std::string(buf, nRet);
        if (nRecvLen == 6) {
            if (message[3] == 76 || message[3] == 69) {
                start.store(0);
            }
            if (message[3] == 114 || message[3] == 107) {
                char sendMessage[6];
                sendMessage[0] = 40;
                sendMessage[5] = 41;
                for (int i = 1; i < 5; i++) {
                    sendMessage[i] = message[i];
                }
                serialPort->SendData(sendMessage, 6);
            }
            if (message[3] == 65) {
                start.store(1);
            }
            message = "";
            nRecvLen = 0;
        }
    }
}
void messageHandler::handle(unsigned char* data, int dataLength) {
    //TODO
    std::set<std::string> BlockSet;
    unsigned char buf[10];
    std::set<std::string> result;
    for (int i = 1,j=0; i < dataLength; i++,j++) {
        buf[j] = data[i];
        if (j == 9) {
            j = -1;
            if (buf[0] == 0x07) {
                result = transferToMaiSerial(buf);
                BlockSet.insert(result.begin(), result.end());
            }
        }
    }
    std::vector<std::vector<int>> blockListInt(exp_list.size());
    for (int i = 0; i < exp_list.size(); i++) {
        blockListInt[i].resize(exp_list[i].size());
        for (int j = 0; j < exp_list[i].size(); j++) {
            if (BlockSet.find(exp_list[i][j]) != BlockSet.end()) {
                blockListInt[i][j] = 1;
            }
            else {
                blockListInt[i][j] = 0;
            }
        }
        /*for (auto& s : exp_list[i]) {
            if (BlockSet.find(s) != BlockSet.end()) {
                blockListInt[i].push_back(1);
            }
            else {
                blockListInt[i].push_back(0);
            }
        }*/
    }
    {
        std::unique_lock<std::shared_mutex> lock(mtx);
        for (int i = 0; i < blockListInt.size(); i++) {
            unsigned char sum = 0;
            for (int j = 0; j < blockListInt[i].size(); j++) {
                sum += blockListInt[i][j] * (1 << j);
            }
            sendMessage[i + 1] = sum;
        }
    }
}
std::set<std::string> messageHandler::transferToMaiSerial(unsigned char* message) {
    int x, y;
    int width, height;
    
    y=message[2]+(message[3]<<8);
    x=32768-(message[4]+(message[5]<<8));
    x = colorMatrixWidth * (double(x) / 32768.0);
    y = colorMatrixHeight * (double(y) / 32768.0);   //转换为屏幕坐标
    width=message[6]+(message[7]<<8);
    height=message[8]+(message[9]<<8);
    width = colorMatrixWidth * (double(width) / 32768.0);
    int lx = width;
    width *= 3;
    height = colorMatrixHeight * (double(height) / 32768.0);//转换为屏幕坐标
    int ly = height;
    height *= 3;
    std::set<std::string> BlockSet;
    
    if (width < 10 && height < 10) {
        //singlePoint
        if (x >= 0 && x < colorMatrixWidth && y >= 0 && y < colorMatrixHeight) {
            auto it = exp_image_dict.find(std::make_tuple(colorMatrixRed[y][x], colorMatrixGreen[y][x], colorMatrixBlue[y][x]));
            if (it != exp_image_dict.end()) {
                BlockSet.insert(it->second);
            }
        }  
    }
    else {
        //rectangle
        for (int i = x-lx; i < x + width; i +=20) {
            for (int j = y-ly; j < y + height; j +=20) {
                if (i >= 0 && i < colorMatrixWidth && j >= 0 && j < colorMatrixHeight) {
                    auto it = exp_image_dict.find(std::make_tuple(colorMatrixRed[j][i], colorMatrixGreen[j][i], colorMatrixBlue[j][i]));
                    if (it != exp_image_dict.end()) {
                        BlockSet.insert(it->second);
                    }
                }
            }
        }
    }
    //send to maiSerial
    //std::vector<std::string> blockList(BlockSet.begin(), BlockSet.end());
    return BlockSet;
}