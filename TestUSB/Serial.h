#pragma once
#include"stdafx.h"
class CSerial
{
private:
	HANDLE hSerial;//����Com����
	bool openFlag;//�����Ƿ��
	DWORD errors;
public:
	CSerial();

	~CSerial();

	BOOL Open(int Port, int nBaud);// ���úʹ򿪴���
	BOOL Close(void);// �رմ���
	bool ReadData(char* buffer, unsigned int limit);//��������
	unsigned int ReadAll(char* buffer);
	bool SendData(char* buffer, unsigned int length);//��������
};
