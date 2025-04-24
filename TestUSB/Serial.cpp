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
	// Port�˿ںţ�nBaud������
	if (openFlag) return true;

	// Port�˿ں�
	char szPort[15];
	if (Port > 9)
		sprintf(szPort, "\\\\.\\COM%d", Port);// ������ ��LPCWSTR�� ���͵��ββ�����
	else
		sprintf(szPort, "COM%d", Port);

	// ��ָ������
	hSerial = CreateFileA(szPort,     /* �豸����COM1,COM2�� */
		GENERIC_READ | GENERIC_WRITE, /* ����ģʽ����ͬʱ��д */
		0,                            /* ����ģʽ��0��ʾ������ */
		NULL,                         /* ��ȫ�����ã�һ��ʹ��NULL */
		OPEN_EXISTING,                /* �ò�����ʾ�豸������ڣ����򴴽�ʧ�� */
		FILE_ATTRIBUTE_NORMAL,		  /* ��ȷ����û������ */
		NULL);
	if (hSerial == NULL) return false;

	// ���ô��ڵĳ�ʱʱ�䣬����Ϊ0����ʾ��ʹ�ó�ʱ����
	COMMTIMEOUTS  CommTimeouts;
	CommTimeouts.ReadIntervalTimeout = 0;
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;
	CommTimeouts.ReadTotalTimeoutConstant = 0;
	CommTimeouts.WriteTotalTimeoutMultiplier = 0;
	CommTimeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(hSerial, &CommTimeouts);

	// ���ڳ�ʼ������
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

	// �ӻ�������ȡlimit��С������
	DWORD BytesRead = (DWORD)limit;
	if (!ReadFile(hSerial, buffer, BytesRead, &BytesRead, NULL)) {
		errors = GetLastError();
		PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_RXABORT);// ��մ��ڻ�����
		return false;
	}

	return (BytesRead == (DWORD)limit);
}

unsigned int CSerial::ReadAll(char* buffer) {
	// ��ȡ������ݴ���buffer����
	if (!openFlag || hSerial == NULL) return false;

	DWORD dwErrorFlags; //�����־
	COMSTAT comStat; //ͨѶ״̬
	OVERLAPPED m_osRead; //�첽��������ṹ��

	memset(&m_osRead, 0, sizeof(m_osRead));
	m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, L"ReadEvent");

	ClearCommError(hSerial, &dwErrorFlags, &comStat); //���ͨѶ���󣬻���豸��ǰ״̬

	DWORD BytesRead = (DWORD)comStat.cbInQue;// ��ȡ�������������ݵĳ���
	//if (limit < (int)BytesRead)
		//BytesRead = (DWORD)limit;

	if (!ReadFile(hSerial, buffer, BytesRead, &BytesRead, NULL)) {
		if (GetLastError() == ERROR_IO_PENDING) {
			//����������ڶ�ȡ��
			//GetOverlappedResult���������һ��������ΪTRUE
			//������һֱ�ȴ���ֱ����������ɻ����ڴ��������
			GetOverlappedResult(hSerial, &m_osRead, &BytesRead, TRUE);
		}
		else {
			ClearCommError(hSerial, &dwErrorFlags, &comStat); //���ͨѶ����
			CloseHandle(m_osRead.hEvent); //�رղ��ͷ�hEvent���ڴ�
			return -1;
		}
	}

	return BytesRead;// ���ض�ȡ�õ����ݳ���
}


bool CSerial::SendData(char* buffer, unsigned int length) {
	if (!openFlag || hSerial == NULL) return false;

	// �򻺳���д��ָ����Сlength������ 
	DWORD bytesSend;
	if (!WriteFile(hSerial, (void*)buffer, length, &bytesSend, NULL)) {
		errors = GetLastError();
		PurgeComm(hSerial, PURGE_TXCLEAR | PURGE_TXABORT);// ��մ��ڻ�����
		return false;
	}

	return true;
}
