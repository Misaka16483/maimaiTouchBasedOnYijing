
// TestUSB.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
// CTestUSBApp: 
// �йش����ʵ�֣������ TestUSB.cpp
//
class CTestUSBApp : public CWinApp
{
public:
	CTestUSBApp();

// ��д
public:
	virtual BOOL InitInstance();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestUSBApp theApp;