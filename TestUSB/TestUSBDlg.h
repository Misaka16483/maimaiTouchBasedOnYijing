
// TestUSBDlg.h : 头文件
//

#pragma once

#define WM_RECVDATA_0	WM_USER+1
#define WM_RECVDATA_1	WM_USER+2
#define WM_RECVDATA_2	WM_USER+3
#define WM_RECVDATA_3	WM_USER+4
#include"messageHandler.h"

// CTestUSBDlg 对话框
class CTestUSBDlg : public CDialogEx
{
	messageHandler* handler;
	
// 构造
public:
	CTestUSBDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTUSB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

// 实现
protected:
	HICON m_hIcon;

	// 动态链接库句柄
	HINSTANCE m_hInst;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonScanDevice();
	afx_msg void OnBnClickedButtonClearMsg();


public:
	ADP_Irt_Get_DeviceCount Irt_Get_DeviceCount;
	ADP_Irt_OpenDevice		Irt_OpenDevice;
	ADP_Irt_CloseDevice		Irt_CloseDevice;
	ADP_Irt_Get_DeviceInfo	Irt_Get_DeviceInfo;
	ADP_Irt_Dev_Read		Irt_Dev_Read;
	ADP_Irt_Dev_Write		Irt_Dev_Write;
	int DispList(CString strRel);
	int m_nRelNum;
//	afx_msg void OnBnClickedCheckComHandle();
//	afx_msg void OnBnClickedCheckComSimtouch();
//	afx_msg void OnBnClickedCheckDirect();
	CONTROL_TYPE m_nRadioType;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedButtonOpen0();
	afx_msg void OnBnClickedButtonOpen1();
	afx_msg void OnBnClickedButtonOpen2();
	afx_msg void OnBnClickedButtonOpen3();
	int BtOpenDevice(int nDevNum);
	LRESULT OnReceiveDataDev0(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveDataDev1(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveDataDev2(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveDataDev3(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveDataDev(int devNum,WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonClose0();
	afx_msg void OnBnClickedButtonClose1();
	afx_msg void OnBnClickedButtonClose2();
	afx_msg void OnBnClickedButtonClose3();
	int BtCloseDevice(int nDevNum);
	afx_msg void OnBnClickedButtonQueryDev0();
	afx_msg void OnBnClickedButtonQueryDev1();
	afx_msg void OnBnClickedButtonQueryDev2();
	afx_msg void OnBnClickedButtonQueryDev3();
	int QueryDev(int nDevNum);
	afx_msg void OnBnClickedButtonMsgEnterCom0();
	afx_msg void OnBnClickedButtonMsgEnterCom1();
	afx_msg void OnBnClickedButtonMsgEnterCom2();
	afx_msg void OnBnClickedButtonMsgEnterCom3();
	int Cmd_EnterIndivualComMode(int nDevNum);
	afx_msg void OnBnClickedButtonMsgEnterHid0();
	afx_msg void OnBnClickedButtonMsgEnterHid1();
	afx_msg void OnBnClickedButtonMsgEnterHid2();
	afx_msg void OnBnClickedButtonMsgEnterHid3();
	int Cmd_EnterTouchMode(int nDevNum);
	afx_msg void OnBnClickedButtonWriteinfo1();

	void Cmd_Writeinfo(int nDevnum);
	int StrToHex(CString strsrc, PUCHAR pData);
	afx_msg void OnBnClickedButtonWriteinfo2();
	afx_msg void OnBnClickedButtonWriteinfo3();
	afx_msg void OnBnClickedButtonWriteinfo4();
	afx_msg void OnBnClickedButtonNouserectA();
	afx_msg void OnBnClickedButtonNouserectClearA();
};
