
// TestUSBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestUSB.h"
#include "TestUSBDlg.h"
#include "afxdialogex.h"
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#include<thread>
#include<chrono>
#include"messageHandler.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()






// CTestUSBDlg 对话框
CTestUSBDlg::CTestUSBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTUSB_DIALOG, pParent)
	, m_nRelNum(0)
	, m_nRadioType(CONTROL_TYPE_HANDLE_DIRECT)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	handler= new messageHandler();
	
}

void CTestUSBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestUSBDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CTestUSBDlg::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_SCAN_DEVICE, &CTestUSBDlg::OnBnClickedButtonScanDevice)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_MSG, &CTestUSBDlg::OnBnClickedButtonClearMsg)
	//	ON_BN_CLICKED(IDC_CHECK_COM_HANDLE, &CTestUSBDlg::OnBnClickedCheckComHandle)
	//	ON_BN_CLICKED(IDC_CHECK_COM_SIMTOUCH, &CTestUSBDlg::OnBnClickedCheckComSimtouch)
	//	ON_BN_CLICKED(IDC_CHECK_DIRECT, &CTestUSBDlg::OnBnClickedCheckDirect)
	ON_BN_CLICKED(IDC_RADIO1, &CTestUSBDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CTestUSBDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CTestUSBDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_0, &CTestUSBDlg::OnBnClickedButtonOpen0)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_1, &CTestUSBDlg::OnBnClickedButtonOpen1)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_2, &CTestUSBDlg::OnBnClickedButtonOpen2)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_3, &CTestUSBDlg::OnBnClickedButtonOpen3)

	ON_MESSAGE(WM_RECVDATA_0, OnReceiveDataDev0)
	ON_MESSAGE(WM_RECVDATA_1, OnReceiveDataDev1)
	ON_MESSAGE(WM_RECVDATA_2, OnReceiveDataDev2)
	ON_MESSAGE(WM_RECVDATA_3, OnReceiveDataDev3)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_0, &CTestUSBDlg::OnBnClickedButtonClose0)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_1, &CTestUSBDlg::OnBnClickedButtonClose1)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_2, &CTestUSBDlg::OnBnClickedButtonClose2)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_3, &CTestUSBDlg::OnBnClickedButtonClose3)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_DEV_0, &CTestUSBDlg::OnBnClickedButtonQueryDev0)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_DEV_1, &CTestUSBDlg::OnBnClickedButtonQueryDev1)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_DEV_2, &CTestUSBDlg::OnBnClickedButtonQueryDev2)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_DEV_3, &CTestUSBDlg::OnBnClickedButtonQueryDev3)
	ON_BN_CLICKED(IDC_BUTTON_MSG_ENTER_COM_0, &CTestUSBDlg::OnBnClickedButtonMsgEnterCom0)
	ON_BN_CLICKED(IDC_BUTTON_MSG_ENTER_COM_1, &CTestUSBDlg::OnBnClickedButtonMsgEnterCom1)
	ON_BN_CLICKED(IDC_BUTTON_MSG_ENTER_COM_2, &CTestUSBDlg::OnBnClickedButtonMsgEnterCom2)
	ON_BN_CLICKED(IDC_BUTTON_MSG_ENTER_COM_3, &CTestUSBDlg::OnBnClickedButtonMsgEnterCom3)
	ON_BN_CLICKED(IDC_BUTTON_MSG_ENTER_HID_0, &CTestUSBDlg::OnBnClickedButtonMsgEnterHid0)
	ON_BN_CLICKED(IDC_BUTTON_MSG_ENTER_HID_1, &CTestUSBDlg::OnBnClickedButtonMsgEnterHid1)
	ON_BN_CLICKED(IDC_BUTTON_MSG_ENTER_HID_2, &CTestUSBDlg::OnBnClickedButtonMsgEnterHid2)
	ON_BN_CLICKED(IDC_BUTTON_MSG_ENTER_HID_3, &CTestUSBDlg::OnBnClickedButtonMsgEnterHid3)
	ON_BN_CLICKED(IDC_BUTTON_WRITEINFO_1, &CTestUSBDlg::OnBnClickedButtonWriteinfo1)
	ON_BN_CLICKED(IDC_BUTTON_WRITEINFO_2, &CTestUSBDlg::OnBnClickedButtonWriteinfo2)
	ON_BN_CLICKED(IDC_BUTTON_WRITEINFO_3, &CTestUSBDlg::OnBnClickedButtonWriteinfo3)
	ON_BN_CLICKED(IDC_BUTTON_WRITEINFO_4, &CTestUSBDlg::OnBnClickedButtonWriteinfo4)
	ON_BN_CLICKED(IDC_BUTTON_NOUSERECT_A, &CTestUSBDlg::OnBnClickedButtonNouserectA)
	ON_BN_CLICKED(IDC_BUTTON_NOUSERECT_CLEAR_A, &CTestUSBDlg::OnBnClickedButtonNouserectClearA)
END_MESSAGE_MAP()


// CTestUSBDlg 消息处理程序

BOOL CTestUSBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	SetDlgItemText(IDC_EDIT_INFO_1, L"01 00 a0 a1");
	SetDlgItemText(IDC_EDIT_INFO_2, L"02 00 a0 a1");
	SetDlgItemText(IDC_EDIT_INFO_3, L"03 00 a0 a1");
	SetDlgItemText(IDC_EDIT_INFO_4, L"04 00 a0 a1");


	// TODO: 在此添加额外的初始化代码
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	m_hInst = LoadLibrary(L"Irt_Hw_Service.dll");
	if (m_hInst)
	{
		Irt_Get_DeviceCount = (ADP_Irt_Get_DeviceCount)GetProcAddress(m_hInst, "Irt_Get_DeviceCount");
		Irt_OpenDevice = (ADP_Irt_OpenDevice)GetProcAddress(m_hInst, "Irt_OpenDevice");
		Irt_CloseDevice = (ADP_Irt_CloseDevice)GetProcAddress(m_hInst, "Irt_CloseDevice");
		Irt_Get_DeviceInfo = (ADP_Irt_Get_DeviceInfo)GetProcAddress(m_hInst, "Irt_Get_DeviceInfo");
		Irt_Dev_Read = (ADP_Irt_Dev_Read)GetProcAddress(m_hInst, "Irt_Dev_Read");
		Irt_Dev_Write = (ADP_Irt_Dev_Write)GetProcAddress(m_hInst, "Irt_Dev_Write");
		DispList(L"动态链接库加载完成");
		OnBnClickedButtonScanDevice();
	}
	else
	{
		MessageBox(L"无法打开设备链接库", L"错误", MB_ICONERROR);
		OnOK();
	}

	SetDlgItemInt(IDC_EDIT1, 0);
	SetDlgItemInt(IDC_EDIT2, 32767);
	SetDlgItemInt(IDC_EDIT3, 24575);
	SetDlgItemInt(IDC_EDIT4, 32767);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestUSBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestUSBDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestUSBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestUSBDlg::OnBnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}


void CTestUSBDlg::OnBnClickedButtonScanDevice()
{
	// TODO: 在此添加控件通知处理程序代码
	int count;
	CString str;
	Irt_Get_DeviceCount(&count);
	str.Format(L"枚举到:%d个设备",count);
	DispList(str);
}


void CTestUSBDlg::OnBnClickedButtonClearMsg()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nRelNum = 0;
	((CListBox*)GetDlgItem(IDC_LIST1))->ResetContent();
}


int CTestUSBDlg::DispList(CString strRel)
{
	CTime t = CTime::GetCurrentTime();
	CString str;
	str.Format(_T("%04d:%02d时%02d分%02d秒："), m_nRelNum++, t.GetHour(), t.GetMinute(), t.GetSecond(),t.GetTickCount());
	str += strRel;
	int index = ((CListBox*)GetDlgItem(IDC_LIST1))->InsertString(-1, str);
	((CListBox*)GetDlgItem(IDC_LIST1))->SetCurSel(index);
	return 0;
}



void CTestUSBDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nRadioType = CONTROL_TYPE_HANDLE_DIRECT;
}


void CTestUSBDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nRadioType = CONTROL_TYPE_HANDLE_SIM_TOUCH;
}


void CTestUSBDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nRadioType = CONTROL_TYPE_DIRECT_READWRITE;
}


void CTestUSBDlg::OnBnClickedButtonOpen0()
{
	// TODO: 在此添加控件通知处理程序代码
	BtOpenDevice(0);
}


void CTestUSBDlg::OnBnClickedButtonOpen1()
{
	// TODO: 在此添加控件通知处理程序代码
	BtOpenDevice(1);
}


void CTestUSBDlg::OnBnClickedButtonOpen2()
{
	// TODO: 在此添加控件通知处理程序代码
	BtOpenDevice(2);
}


void CTestUSBDlg::OnBnClickedButtonOpen3()
{
	// TODO: 在此添加控件通知处理程序代码
	BtOpenDevice(3);
}



LRESULT CTestUSBDlg::OnReceiveDataDev0(WPARAM wParam, LPARAM lParam)
{
	return OnReceiveDataDev(0,wParam,lParam);
}
LRESULT CTestUSBDlg::OnReceiveDataDev1(WPARAM wParam, LPARAM lParam)
{
	return OnReceiveDataDev(1, wParam, lParam);
}
LRESULT CTestUSBDlg::OnReceiveDataDev2(WPARAM wParam, LPARAM lParam)
{
	return OnReceiveDataDev(2, wParam, lParam);
}
LRESULT CTestUSBDlg::OnReceiveDataDev3(WPARAM wParam, LPARAM lParam)
{
	return OnReceiveDataDev(3, wParam, lParam);
}


void CTestUSBDlg::OnBnClickedButtonClose0()
{
	// TODO: 在此添加控件通知处理程序代码
	BtCloseDevice(0);
}


void CTestUSBDlg::OnBnClickedButtonClose1()
{
	// TODO: 在此添加控件通知处理程序代码
	BtCloseDevice(1);
}


void CTestUSBDlg::OnBnClickedButtonClose2()
{
	// TODO: 在此添加控件通知处理程序代码
	BtCloseDevice(2);
}


void CTestUSBDlg::OnBnClickedButtonClose3()
{
	// TODO: 在此添加控件通知处理程序代码
	BtCloseDevice(3);
}



void CTestUSBDlg::OnBnClickedButtonQueryDev0()
{
	// TODO: 在此添加控件通知处理程序代码
	QueryDev(0);
}


void CTestUSBDlg::OnBnClickedButtonQueryDev1()
{
	// TODO: 在此添加控件通知处理程序代码
	QueryDev(1);
}


void CTestUSBDlg::OnBnClickedButtonQueryDev2()
{
	// TODO: 在此添加控件通知处理程序代码
	QueryDev(2);
}


void CTestUSBDlg::OnBnClickedButtonQueryDev3()
{
	// TODO: 在此添加控件通知处理程序代码
	QueryDev(3);
}

void CTestUSBDlg::OnBnClickedButtonMsgEnterCom0()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_EnterIndivualComMode(0);
}


void CTestUSBDlg::OnBnClickedButtonMsgEnterCom1()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_EnterIndivualComMode(1);
}


void CTestUSBDlg::OnBnClickedButtonMsgEnterCom2()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_EnterIndivualComMode(2);
}


void CTestUSBDlg::OnBnClickedButtonMsgEnterCom3()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_EnterIndivualComMode(3);
}

void CTestUSBDlg::OnBnClickedButtonMsgEnterHid0()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_EnterTouchMode(0);
}


void CTestUSBDlg::OnBnClickedButtonMsgEnterHid1()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_EnterTouchMode(1);
}


void CTestUSBDlg::OnBnClickedButtonMsgEnterHid2()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_EnterTouchMode(2);
}


void CTestUSBDlg::OnBnClickedButtonMsgEnterHid3()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_EnterTouchMode(3);
}

void CTestUSBDlg::OnBnClickedButtonWriteinfo1()
{
	Cmd_Writeinfo(0);
}

void CTestUSBDlg::OnBnClickedButtonWriteinfo2()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_Writeinfo(1);
}


void CTestUSBDlg::OnBnClickedButtonWriteinfo3()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_Writeinfo(2);
}


void CTestUSBDlg::OnBnClickedButtonWriteinfo4()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmd_Writeinfo(3);
}
LRESULT CTestUSBDlg::OnReceiveDataDev(int devNum, WPARAM wParam, LPARAM lParam)
{
	CString str, se;
	UCHAR * pData = (PUCHAR)wParam;
	/*int i;
	//str.Format(L"收到设备%d的数据包:数据长度:%d",devNum, lParam);
	//DispList(str);
	str.Format(L"");
	for ( i = 0; i < 32; i++)
	{
		se.Format(L"%02x,", pData[i]);
		//printf("%02x ", pData[i]);
		str += se;
		if (i % 8 == 7)
			str += L"  ";
	}
	//DispList(str);
	str.Format(L"");
	for (; i < (int)lParam; i++)
	{
		se.Format(L"%02x,", pData[i]);
		//printf("%02x ", pData[i]);
		str += se;
		if (i % 8 == 7)
			str += L"  ";
	}*/
	this->handler->handle(pData, (int)lParam);
	return 0;
}

int CTestUSBDlg::BtOpenDevice(int nDevNum)
{
	CString str;
	int rel;
	//((CButton *)GetDlgItem(IDC_RADIO1))->EnableWindow(FALSE);
	//((CButton *)GetDlgItem(IDC_RADIO2))->EnableWindow(FALSE);
	//((CButton *)GetDlgItem(IDC_RADIO3))->EnableWindow(FALSE);
	rel = Irt_OpenDevice(nDevNum, m_nRadioType, m_hWnd, WM_RECVDATA_0 + nDevNum);
	if (rel)
	{
		str.Format(L"打开设备:%d,模式:%d,失败:%d", nDevNum, m_nRadioType, rel);
	}
	else
	{
		str.Format(L"打开设备:%d,模式:%d,成功", nDevNum, m_nRadioType);
	}
	DispList(str);
	return 0;
}
int CTestUSBDlg::BtCloseDevice(int nDevNum)
{
	int rel;
	CString str, se;
	rel = Irt_CloseDevice(nDevNum);
	str.Format(L"关闭设备:%d,返回%d", nDevNum, rel);
	DispList(str);
	return 0;
}

int CTestUSBDlg::QueryDev(int nDevNum)
{
	UCHAR  buf[80] = {0x05,0x1f,0xf7,0xfc};
	buf[4] = 0x10;
	int rel = Irt_Dev_Write(nDevNum, buf, 64);
	if (rel)
	{
		CString str;
		str.Format(L"下发指令失败:%d", rel);
		DispList(str);
	}
	return 0;
}



int CTestUSBDlg::Cmd_EnterIndivualComMode(int nDevNum)
{
	UCHAR  buf[80] = { 0x05,0x1f,0xf7,0xfc };
	buf[4] = 0x12;
	int rel = Irt_Dev_Write(nDevNum, buf, 64);
	if (rel)
	{
		CString str;
		str.Format(L"下发指令失败:%d", rel);
		DispList(str);
	}
	return 0;
}



int CTestUSBDlg::Cmd_EnterTouchMode(int nDevNum)
{
	UCHAR  buf[80] = { 0x05,0x1f,0xf7,0xfc };
	buf[4] = 0x14;
	int rel = Irt_Dev_Write(nDevNum, buf, 64);
	if (rel)
	{
		CString str;
		str.Format(L"下发指令失败:%d",rel);
		DispList(str);
	}
	return 0;
}

int CTestUSBDlg::StrToHex(CString strsrc, PUCHAR pData)
{
	int rel, reg;
	for (rel = 0; rel * 3 + 1< strsrc.GetLength(); rel++)
	{
		::StrToIntEx(L"0x" + strsrc.Mid(rel * 3, 2), STIF_SUPPORT_HEX, &reg);
		pData[rel] = reg;
		if (rel > 31)
			break;
	}
	return rel;
}

void CTestUSBDlg::Cmd_Writeinfo(int nDevnum)
{
	// TODO: 在此添加控件通知处理程序代码
	// 写入自定义存储
	UCHAR buf[128] = { 0x05,0x1f,0xf7,0xfc };
	buf[4] = 0x16;
	int i,rel,len;
	CString str,se;
	UINT32 editId[4] = { IDC_EDIT_INFO_1 ,IDC_EDIT_INFO_2 ,IDC_EDIT_INFO_3,IDC_EDIT_INFO_4};

	GetDlgItemTextW(editId[nDevnum],str);
	len = StrToHex(str,&buf[8]);
	if (len > 16)
		len = 16;
	buf[6] = len;
	rel = Irt_Dev_Write(nDevnum, buf, 64);
	if (rel)
	{
		str.Format(L"下发指令失败:%d", rel);
		DispList(str);
	}
	else
	{
		str.Format(L"写入设备:%d共计:%d字节完成:",nDevnum,len);
		for (i = 0; i < len; i++)
		{
			se.Format(L"0x%02x,",buf[8+i]);
			str += se;
		}
		DispList(str);
	}
}





void CTestUSBDlg::OnBnClickedButtonNouserectA()
{
	// TODO: 在此添加控件通知处理程序代码
	int i, rel, len, nDevnum;
	nDevnum = 0;
	len = 9;
	CString str,se;
	USHORT reg[128];
	UCHAR buf[128] = { 0x05,0x1f,0xf7,0xfc };
	reg[0] = GetDlgItemInt(IDC_EDIT1);
	reg[1] = GetDlgItemInt(IDC_EDIT3);
	reg[2] = GetDlgItemInt(IDC_EDIT2);
	reg[3] = GetDlgItemInt(IDC_EDIT4);

	buf[4] = 0xb4;
	buf[5] = 0x01;
	buf[6] = len;
	buf[7] = 0x00;

	buf[8] = 0x01;
	memcpy(&buf[9], reg, 4 * 2);

	rel = Irt_Dev_Write(nDevnum, buf, 64);
	if (rel)
	{
		str.Format(L"下发指令失败:%d", rel);
		DispList(str);
	}
	else
	{
		str.Format(L"写入设备:%d共计:%d字节完成:", nDevnum, len);
		for (i = 0; i < len; i++)
		{
			se.Format(L"0x%02x,", buf[8 + i]);
			str += se;
		}
		DispList(str);
	}
}


void CTestUSBDlg::OnBnClickedButtonNouserectClearA()
{
	// TODO: 在此添加控件通知处理程序代码


	int i, rel, len, nDevnum;
	CString str,se;
	UCHAR buf[128] = { 0x05,0x1f,0xf7,0xfc};

	nDevnum = 0;
	len = 9;
	buf[4] = 0xb4;
	buf[5] = 0x02;
	buf[6] = len;
	buf[7] = 0x00;
	rel = Irt_Dev_Write(nDevnum, buf, 64);
	if (rel)
	{
		str.Format(L"下发指令失败:%d", rel);
		DispList(str);
	}
	else
	{
		str.Format(L"写入设备:%d共计:%d字节完成:", nDevnum, len);
		for (i = 0; i < len; i++)
		{
			se.Format(L"0x%02x,", buf[8 + i]);
			str += se;
		}
		DispList(str);
	}

}
