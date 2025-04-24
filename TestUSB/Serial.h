#pragma once
#include"stdafx.h"
class CSerial
{
private:
	HANDLE hSerial;//串口Com的类
	bool openFlag;//串口是否打开
	DWORD errors;
public:
	CSerial();

	~CSerial();

	BOOL Open(int Port, int nBaud);// 设置和打开串口
	BOOL Close(void);// 关闭串口
	bool ReadData(char* buffer, unsigned int limit);//接收数据
	unsigned int ReadAll(char* buffer);
	bool SendData(char* buffer, unsigned int length);//发送数据
};
