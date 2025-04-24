#define _CRT_SECURE_NO_WARNINGS
#include"stdafx.h"
#include"Serial.h"
CSerial::CSerial() {
	openFlag = false;
	hSerial = NULL;
}


CSerial::~CSerial() {
	Close();
}

BOOL CSerial::Open(int Port, int nBaud) {
	// Port端口号，nBaud波特率
	if (openFlag) return true;

	// Port端口号
	char szPort[15];
	if (Port > 9)
		sprintf(szPort, "\\\\.\\COM%d", Port);// 出现与 “LPCWSTR“ 类型的形参不兼容
	else
		sprintf(szPort, "COM%d", Port);

	// 打开指定串口
	hSerial = CreateFileA(szPort,     /* 设备名，COM1,COM2等 */
		GENERIC_READ | GENERIC_WRITE, /* 访问模式，可同时读写 */
		0,                            /* 共享模式，0表示不共享 */
		NULL,                         /* 安全性设置，一般使用NULL */
		OPEN_EXISTING,                /* 该参数表示设备必须存在，否则创建失败 */
		FILE_ATTRIBUTE_NORMAL,		  /* 明确设置没有属性 */
		NULL);
	if (hSerial == NULL) return false;

	// 设置串口的超时时间，均设为0，表示不使用超时限制
	COMMTIMEOUTS  CommTimeouts;
	CommTimeouts.ReadIntervalTimeout = 0;
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;
	CommTimeouts.ReadTotalTimeoutConstant = 0;
	CommTimeouts.WriteTotalTimeoutMultiplier = 0;
	CommTimeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(hSerial, &CommTimeouts);

	// 串口初始化参数
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.BaudRate = nBaud;// Ardiuno CBR_115200
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		errors = GetLastError();
		printf("ALERT: Could not set Serial Port parameters");
		CloseHandle(hSerial);
		return false;
	}

	openFlag = true;
	return openFlag;
}

BOOL CSerial::Close() {
	if (!openFlag || hSerial == NULL)return true;

	CloseHandle(hSerial);
	openFlag = false;
	hSerial = NULL;

	return true;
}

bool CSerial::ReadData(char* buffer, unsigned int limit) {
	if (!openFlag || hSerial == NULL) return false;

	// 从缓冲区读取limit大小的数据
	DWORD BytesRead = (DWORD)limit;
	if (!ReadFile(hSerial, buffer, BytesRead, &BytesRead, NULL)) {
		errors = GetLastError();
		PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_RXABORT);// 清空串口缓冲区
		return false;
	}

	return (BytesRead == (DWORD)limit);
}

unsigned int CSerial::ReadAll(char* buffer) {
	// 读取后的数据存在buffer这里
	if (!openFlag || hSerial == NULL) return false;

	DWORD dwErrorFlags; //错误标志
	COMSTAT comStat; //通讯状态
	OVERLAPPED m_osRead; //异步输入输出结构体

	memset(&m_osRead, 0, sizeof(m_osRead));
	m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, L"ReadEvent");

	ClearCommError(hSerial, &dwErrorFlags, &comStat); //清除通讯错误，获得设备当前状态

	DWORD BytesRead = (DWORD)comStat.cbInQue;// 获取缓冲区所有数据的长度
	//if (limit < (int)BytesRead)
		//BytesRead = (DWORD)limit;

	if (!ReadFile(hSerial, buffer, BytesRead, &BytesRead, NULL)) {
		if (GetLastError() == ERROR_IO_PENDING) {
			//如果串口正在读取中
			//GetOverlappedResult函数的最后一个参数设为TRUE
			//函数会一直等待，直到读操作完成或由于错误而返回
			GetOverlappedResult(hSerial, &m_osRead, &BytesRead, TRUE);
		}
		else {
			ClearCommError(hSerial, &dwErrorFlags, &comStat); //清除通讯错误
			CloseHandle(m_osRead.hEvent); //关闭并释放hEvent的内存
			return -1;
		}
	}

	return BytesRead;// 返回读取得到数据长度
}


bool CSerial::SendData(char* buffer, unsigned int length) {
	if (!openFlag || hSerial == NULL) return false;

	// 向缓冲区写入指定大小length的数据 
	DWORD bytesSend;
	if (!WriteFile(hSerial, (void*)buffer, length, &bytesSend, NULL)) {
		errors = GetLastError();
		PurgeComm(hSerial, PURGE_TXCLEAR | PURGE_TXABORT);// 清空串口缓冲区
		return false;
	}

	return true;
}
