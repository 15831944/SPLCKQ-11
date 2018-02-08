
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "DlgConnection.h"
#include "MainFrm.h"
#include "Tools.h"
#include "cSerBuf_LoopRcv.h"
#include "DlgSelect.h"
//extern cSerBuf_LoopRcv  m_loopRcv64507;
extern cSerBuf_LoopRcv m_loopRcv13762;

#define BIT_SET(x, bitn)    (x |=   (1 << bitn))
#define BIT_CLR(x, bitn)    (x &=  ~(1 << bitn))
#define IS_BIT_SET(x, bitn) ((x & (1 << bitn)) != 0)
#define IS_BIT_CLR(x, bitn) ((x & (1 << bitn)) == 0)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

//BEGIN_MESSAGE_MAP
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_MESSAGE(WM_COMMNOTIFY, OnComm)
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_CONNECT_OPEN, &CMainFrame::OnConnectOpen)
	ON_COMMAND(ID_CONNECT_CLOSE, &CMainFrame::OnConnectClose)
	ON_COMMAND(ID_NETWORT_OPEN, &CMainFrame::OnNetwortOpen)
	ON_UPDATE_COMMAND_UI(ID_CONNECT_OPEN, &CMainFrame::OnUpdateConnectOpen)
	ON_UPDATE_COMMAND_UI(ID_CONNECT_CLOSE, &CMainFrame::OnUpdateConnectClose)
	ON_WM_TIMER()
	ON_COMMAND(ID_3762_OPEN, &CMainFrame::On3762Open)
	ON_COMMAND(ID_FRAMESHOW, &CMainFrame::OnFrameshow)
	ON_COMMAND(ID_COPYFRAME, &CMainFrame::OnCopyframe)
	ON_WM_CLOSE()
	ON_COMMAND(ID_JZQ, &CMainFrame::OnJzq)
	ON_UPDATE_COMMAND_UI(ID_JZQ, &CMainFrame::OnUpdateJzq)
	ON_COMMAND(ID_CKQ20, &CMainFrame::OnCkq20)
	ON_UPDATE_COMMAND_UI(ID_CKQ20, &CMainFrame::OnUpdateCkq20)
END_MESSAGE_MAP()


//static UINT indicators[] =
//{
//	ID_SEPARATOR,           // ״̬��ָʾ��
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
//};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
	m_bNetWork = FALSE;
	m_bNetWorkOpen = FALSE;
	m_bConnected = FALSE;
	m_bsetopen=TRUE;
	m_bsetclos=FALSE;
	m_bFrame3762 = FALSE;
	m_bFrame698 = FALSE;
	m_bCommunictStop = FALSE;
	m_strMAddress = _T("");
	m_376seq = 0;
	m_nConnectType = 0;
	m_PeiZhi_db=".\\�����ļ�\\13762Data.accdb";
	m_bCKQ=TRUE;
	m_bJZQ=!m_bCKQ;
}

CMainFrame::~CMainFrame()
{
	m_FrameShowWnd.ShowWindow(SW_HIDE);
	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = FALSE;    // ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = TRUE;    // ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = TRUE; // ��ѡ�������ұ�Ե�����ĵ��˵�
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// �����û�����Ĺ���������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	LoadStatusBar();
	

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// ���ù�������ͣ�����ڲ˵��滻
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// �����û�����Ĺ�����ͼ��
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}
	if((m_hPostMsgEvent=CreateEvent(NULL, FALSE, TRUE, NULL))==NULL)
		return FALSE;

	memset(&m_osRead, 0, sizeof(OVERLAPPED));
	memset(&m_osWrite, 0, sizeof(OVERLAPPED));

	// Ϊ�ص��������¼������ֹ����ã���ʼ��Ϊ���źŵ�
	if((m_osRead.hEvent=CreateEvent(NULL, FALSE, FALSE, NULL))==NULL)
		return FALSE;

	// Ϊ�ص�д�����¼������ֹ����ã���ʼ��Ϊ���źŵ�
	if((m_osWrite.hEvent=CreateEvent(NULL, FALSE, FALSE, NULL))==NULL)
		return FALSE;
	// ���ò˵����Ի�(���ʹ�õ�����)
	// TODO: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
	/*CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);*/

	// ���ĵ�����Ӧ�ó��������ڴ��ڱ������ϵ�˳����н�������
	// ���Ľ��������Ŀ����ԣ���Ϊ��ʾ���ĵ�����������ͼ��
	ModifyStyle(0, FWS_PREFIXTITLE);

	m_Font70.CreatePointFont(90,_T("����"));
	m_Font100.CreatePointFont(100,_T("����"));
	m_Font120.CreatePointFont(125,_T("����"));


	CString strObjectView("��Ϣ����");  
	if (!m_FrameShowWnd.Create(strObjectView, this, CRect(0, 0, 200, 200), TRUE, 1001, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))  
	{  
		TRACE0("δ�ܴ�������Ϣ���ڡ�����\n");  
		return 0; // δ�ܴ���  
	}
	m_FrameShowWnd.EnableDocking(CBRS_ALIGN_ANY); //ʹ��ͣ���븡��  
	DockPane(&m_FrameShowWnd);
	m_FrameShowWnd.ShowWindow(SW_HIDE);

	CString strObjectView2("��������");  
	if (!mm_FrameShowWndTree.Create(strObjectView2, this, CRect(0, 0, 600, 400), TRUE, 1002, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))  
	{  
		TRACE0("δ�ܴ������������ˡ�����\n");  
		return 0; // δ�ܴ���  
	}
	mm_FrameShowWndTree.EnableDocking(CBRS_ALIGN_ANY); //ʹ��ͣ���븡��  
	DockPane(&mm_FrameShowWndTree);
	mm_FrameShowWndTree.ShowWindow(SW_SHOW);


	return 0;
}

void CMainFrame::OnFrameshow()
{
	m_FrameShowWnd.ShowWindow(SW_SHOW);
}
void CMainFrame::Creat_File()
{

//#if 0
//	//��ʼ�����ص�����Ϣ
//	displayComData = false;
//	GetDlgItem(IDC_BUTTON10)->SetWindowText("��ʾ������Ϣ");
//#endif

	///////////�򿪱��ֲ��Ե�LOG�ļ�
	CString str,strTemp;
	SYSTEMTIME st;
	GetLocalTime(&st);
	CFileException fileException;

	str = _T(".\\��־\\DataFile-");
	strTemp.Format(_T("%.4d��%.2d��%.2d��"),st.wYear,st.wMonth,st.wDay);
	//strTemp.Format(_T("%.4d��%.2d��%.2d��%.2d��%.2d��%.2d��"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	if(!cfileData.Open(str+ strTemp +_T(".txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite 
		| CFile::shareDenyNone, &fileException))
	{
		//TRACE( "Can't open file, error = %u\n",fileException.m_cause );
		AfxMessageBox(_T("Can't open file,�Զ���������LOG�޷�����"));
		bAutoTestRunCmd = false;
	}else TRACE("open data file ok \r\n");

	//str = _T(".\\log_3762\\ParsFile-");		
	//if(!cfileParse.Open(str+ strTemp +_T(".txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite 
	//	| CFile::shareDenyNone, &fileException))
	//{
	//	//TRACE( "Can't open file, error = %u\n",fileException.m_cause );
	//	AfxMessageBox(_T("Can't open PARSE file���Զ����Խ���LOG�޷�����"));
	//	bAutoTestRunCmd = false;
	//}else TRACE("open parse file ok \r\n");

	cfileData.Write(str,str.GetLength());
}
void CMainFrame::Close_File()
{
	cfileData.Close();
	cfileParse.Close();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// ���ཫִ�������Ĺ���

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}
BOOL CMainFrame::LoadStatusBar()
{
	UINT indicators[] =
	{
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR
	};
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return FALSE;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_POPOUT,0);
	m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_POPOUT,30);
	m_wndStatusBar.SetPaneText(1,_T("����:"));
	m_wndStatusBar.SetPaneInfo(2,ID_SEPARATOR,SBPS_POPOUT,150);
	m_wndStatusBar.SetPaneText(2,_T("�ر�"));
	m_wndStatusBar.SetPaneInfo(3,ID_SEPARATOR,SBPS_STRETCH,0);
	SetTimer(IDS_STATUSBARSYSTIME,500,NULL);
	return TRUE;
}






UINT CommProcc(LPVOID pParam)
{
	OVERLAPPED os;
	DWORD dwMask, dwTrans;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	CMainFrame* pMain= (CMainFrame*)pParam;

	memset(&os, 0, sizeof(OVERLAPPED));
	os.hEvent=CreateEvent(NULL, FALSE, FALSE, NULL);

	if(os.hEvent==NULL)
	{
		AfxMessageBox(_T("�޷������¼�����!"));
		return (UINT)-1;
	}

	while(pMain->m_bConnected)
	{
		ClearCommError(pMain->hCom,&dwErrorFlags,&ComStat);

		if(ComStat.cbInQue)
		{
			// ���޵ȴ�WM_COMMNOTIFY��Ϣ��������
			WaitForSingleObject(pMain->m_hPostMsgEvent, INFINITE);
			ResetEvent(pMain->m_hPostMsgEvent);

			// ֪ͨ��ͼ
			PostMessage(pMain->m_hTermWnd, WM_COMMNOTIFY, EV_RXCHAR, 0);

			continue;
		}

		dwMask=0;

		if(!WaitCommEvent(pMain->hCom, &dwMask, &os)) // �ص�����
		{

			if(GetLastError()==ERROR_IO_PENDING)
				// ���޵ȴ��ص��������
				GetOverlappedResult(pMain->hCom, &os, &dwTrans, TRUE);
			else
			{
				CloseHandle(os.hEvent);
				return (UINT)-1;
			}
		}
	}

	CloseHandle(os.hEvent);
	return 0;
}
void CMainFrame::OnConnectOpen()
{
	CDlgConnection dlgConnection;
	CTools tools;
	INT16U temp16 = 0;
	while(1)
	{
		int nBTN = dlgConnection.DoModal();
		if (nBTN == IDOK)
		{
			COMMTIMEOUTS TimeOuts;

			tools._str16tobuf16(dlgConnection.m_strMainMAC , m_HostNodeAddress ,temp16,true);

			m_hTermWnd=this->GetSafeHwnd();
			int xunhuan=0;
			if(m_bConnected)
				return;
			hCom=CreateFile(_T("\\\\.\\")+dlgConnection.m_strCommPort,
				GENERIC_READ|GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
				NULL);
			SetupComm(hCom,MAXBLOCK,MAXBLOCK);
			SetCommMask(hCom, EV_RXCHAR);
			PurgeComm( hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR );  //��ɾ����롢��������� 

			// �Ѽ����ʱ��Ϊ��󣬰��ܳ�ʱ��Ϊ0������ReadFile�������ز���ɲ���
			TimeOuts.ReadIntervalTimeout=MAXDWORD; 
			TimeOuts.ReadTotalTimeoutMultiplier=0; 
			TimeOuts.ReadTotalTimeoutConstant=0; 

			//����д��ʱ��ָ��WriteComm��Ա�����е�GetOverlappedResult�����ĵȴ�ʱ��
			TimeOuts.WriteTotalTimeoutMultiplier=50;
			TimeOuts.WriteTotalTimeoutConstant=2000;

			SetCommTimeouts(hCom, &TimeOuts);

			DCB dcb;
			GetCommState(hCom,&dcb);
			dcb.BaudRate=_ttol(dlgConnection.m_strCommBaud);  //��������
			dcb.Parity=_ttol(dlgConnection.m_strCommParity);  //��ż��
			dcb.ByteSize=_ttol(dlgConnection.m_strCommDatabit);    //��ʼλ
			dcb.StopBits=_ttol(dlgConnection.m_strCommStopbit); //ֹͣλ
			if(SetCommState(hCom,&dcb))
			{
				m_pThread=AfxBeginThread(CommProcc, this, THREAD_PRIORITY_NORMAL, 
					0, CREATE_SUSPENDED, NULL); // �����������߳�

				if(m_pThread==NULL)
				{
					CloseHandle(hCom);
					return;
				}
				else	
				{
					SetStatusBat(GetCommMessage(dlgConnection.m_strCommPort,dlgConnection.m_strCommBaud,dlgConnection.m_strCommParity,dlgConnection.m_strCommDatabit,dlgConnection.m_strCommStopbit));
					m_bsetopen = false;
					m_bsetclos = true;
					m_bConnected=TRUE;
					m_nConnectType = CONNECTCKQ;
					m_pThread->ResumeThread(); // �ָ��߳�����
				}
				return;
			}
			else
			{
				AfxMessageBox(dlgConnection.m_strCommPort + _T(" ��ռ�û�δ�ҵ�!���鴮��"));
			}
		}
		else
		{
			break;
		}
	}
	
}
void CMainFrame::OnConnectClose()
{
	
	if(!m_bConnected)
		return;
	m_bsetclos=FALSE;
	m_bsetopen=TRUE;
	m_bConnected=FALSE;

	//����CommProc�߳���WaitSingleObject�����ĵȴ�
	SetEvent(m_hPostMsgEvent); 

	//����CommProc�߳���WaitCommEvent�ĵȴ�
	SetCommMask(hCom, 0); 

	//�ȴ������߳���ֹ
	WaitForSingleObject(m_pThread->m_hThread, INFINITE);
	m_pThread=NULL;
	SetStatusBat(_T("�ر�"));
	m_nConnectType = 0;
	CloseHandle(hCom);
}

LRESULT CMainFrame::OnComm(WPARAM wParam, LPARAM lParam)
{
	INT8U buf[1];
	CString str;
	int nLength;
	if(!m_bConnected || (wParam & EV_RXCHAR)!=EV_RXCHAR) // �Ƿ���EV_RXCHAR�¼�?
	{
		SetEvent(m_hPostMsgEvent); // ��������һ��WM_COMMNOTIFY��Ϣ
		return 0L;
	}

	nLength=ReadComm(buf,1);
	if(nLength)
	{
		m_loopRcv13762.InPutRcvByte(buf[0]);
	}
	SetEvent(m_hPostMsgEvent);//��������һ��WM_COMMNOTIFY��Ϣ
	return 0L;
}
DWORD CMainFrame::ReadComm(INT8U *buf, DWORD dwLength)
{
	DWORD length=0;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	length=min(dwLength, ComStat.cbInQue);
	ReadFile(hCom,buf,length,&length,&m_osRead);	
	return length;
}
void CMainFrame::OnUpdateConnectOpen(CCmdUI *pCmdUI)
{
	if (m_bsetopen)
	{
		pCmdUI-> Enable(TRUE); 
	}
	else
	{
		pCmdUI-> Enable(FALSE); 
	}
}
void CMainFrame::OnUpdateConnectClose(CCmdUI *pCmdUI)
{
	if (m_bsetclos)
	{
		pCmdUI-> Enable(TRUE); 
	}
	else
	{
		pCmdUI-> Enable(FALSE); 
	}
}
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
#if 0//no ms
	CTime t = CTime::GetCurrentTime();//��ȡ��ǰϵͳʱ��   
	m_strSysTime = t.Format("%H:%M:%S");
	m_strSysDateTime = t.Format("%Y��%m��%d�� %H:%M:%S");
#else
	SYSTEMTIME st;
	GetLocalTime(&st);
	m_strSysTime.Format(_T("%.2d:%.2d.%.2d"), st.wHour, st.wMinute, st.wSecond);
	//m_strSysDateTime.Format(_T("%d��%d��%d�� %.2d:%.2d:%.2d:%.3d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#endif 




	if (nIDEvent == IDS_STATUSBARSYSTIME)
	{
		CClientDC dc(this);  
		CSize cs = dc.GetTextExtent(m_strSysTime);//��ȡ�ַ�������   
		m_wndStatusBar.SetPaneInfo(4,ID_SEPARATOR,SBPS_POPOUT,cs.cx);//�����ַ����������ô��񳤶�   
		m_wndStatusBar.SetPaneText(4,m_strSysTime,TRUE);
	}
	else
	{
		switch(nIDEvent)
		{
		case 0:
			break;
		}
	}
	
	CMDIFrameWndEx::OnTimer(nIDEvent);
}
void CMainFrame::SetStatusBat(CString strPort)
{
	m_wndStatusBar.SetPaneText(2,strPort,TRUE);
}
CString CMainFrame::GetCommMessage(CString strPort, CString strBaud , CString strParity , CString strDatabit, CString strStopbit)
{
	CString strData = strPort + _T("��") + strBaud + _T("��");
	switch(_ttoi(strParity))
	{
	case 0:
		strParity = "N";
		break;
	case 1:
		strParity = "E";
		break;
	case 2:
		strParity = "O";
		break;
	}
	switch(_ttoi(strStopbit))
	{
	case 0:
		strStopbit = "1";
		break;
	case 1:
		strStopbit = "1.5";
		break;
	case 2:
		strStopbit = "2";
		break;
	}
	strData += strParity + _T("��") + strDatabit + _T("��") + strStopbit + _T("��");
	return strData;
}
void CMainFrame::OnNetwortOpen()
{
	/*if(!m_bConnected)
	{
		AfxMessageBox(_T("���ȴ򿪴������ӳ�����!"));
		return;
	}*/
		
	m_nChooseView = OPENNET;
	CSPL_CKQApp* pApp=(CSPL_CKQApp*)AfxGetApp();
	if (m_bNetWork==FALSE)
	{
		pApp->m_pDocTemplate->OpenDocumentFile(NULL);
		m_pFrameNetWork=(CFrameSetNet *)GetActiveFrame();
		m_bNetWork=TRUE;
		return;
	}
	m_pFrameNetWork->MDIActivate();
}
void CMainFrame::On3762Open()
{
	if(!m_bConnected)
	{
		AfxMessageBox(_T("���ȴ򿪴������ӳ�����!"));
		return;
	}
	m_nChooseView = OPEN13762;
	///////////////////////////////////////////////////////////
	//DlgSelect dlgsetnw;
	//int nBTN = dlgsetnw.DoModal();
	//if(NW_OR_GW==0)
	//{
	//	m_PeiZhi=".\\�����ļ�\\13762���ؼ�.ini";
	//	m_PeiZhi_db=".\\�����ļ�\\13762Data.accdb";
	//}
	//else if(NW_OR_GW==1)
	//{
	//	m_PeiZhi=".\\�����ļ�\\13762���ؼ�NW.ini";
	//	m_PeiZhi_db=".\\�����ļ�\\13762DataNW.accdb";
	//}
	////////////////////////////////////////////////////////////
	CSPL_CKQApp* pApp=(CSPL_CKQApp*)AfxGetApp();
	pApp->m_pDocTemp3762->OpenDocumentFile(NULL);
	m_pFrame3762=(CFrame3762 *)GetActiveFrame();
	m_bFrame3762=TRUE;
	return;
	//if (m_bFrame3762==FALSE)
	//{
	//pApp->m_pDocTemp3762->OpenDocumentFile(NULL);
	//m_pFrame3762=(CFrame3762 *)GetActiveFrame();
	//m_bFrame3762=TRUE;
	//return;
	//}
	//m_pFrame3762->MDIActivate();
}

void CMainFrame::SendBufToCOMM(INT8U * sendbuf,INT16U sendLen , INT8U nType)
{
	DWORD  nsize = 0;
	m_loopRcv13762.ClrRcvBuf();


	SYSTEMTIME st;
	GetLocalTime(&st);
	m_strSysDateTime_tx.Format(_T("%d��%d��%d�� %.2d:%.2d:%.2d.%.3d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);


	switch(nType)
	{
	case 0:
		WriteFile(hCom,sendbuf,sendLen,&nsize,&m_osWrite);
		break;
	case 1:
		//WriteFile(m_hCom645,sendbuf,sendLen,&nsize,&m_osWrite2);
		break;
	}
	///////������־
	int nItem = m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem(nItem , m_strSysDateTime_tx);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 1, _T("����>>"));
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 2 , m_tools._buf16tostr16(sendbuf , sendLen , true));
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItem,FALSE);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.RedrawItems(nItem,nItem);

}

void CMainFrame::BF_SendBufToCOMM(INT8U * sendbuf,INT16U sendLen , INT8U nType)
{
	DWORD  nsize = 0;
	//m_loopRcv13762.ClrRcvBuf();


	SYSTEMTIME st;
	GetLocalTime(&st);
	m_strSysDateTime_tx.Format(_T("%d��%d��%d�� %.2d:%.2d:%.2d.%.3d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);


	switch(nType)
	{
	case 0:
		WriteFile(hCom,sendbuf,sendLen,&nsize,&m_osWrite);
		break;
	case 1:
		//WriteFile(m_hCom645,sendbuf,sendLen,&nsize,&m_osWrite2);
		break;
	}
	///////������־
	int nItem = m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem(nItem , m_strSysDateTime_tx);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 1, _T("����>>"));
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 2 , m_tools._buf16tostr16(sendbuf , sendLen , true));
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItem,FALSE);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.RedrawItems(nItem,nItem);

}
unsigned char CMainFrame::getFn(ST_Fn stFn)
{
	unsigned char fn = 0;
	char i = 0;
	
	for (;i<8;i++)
	{
		if (IS_BIT_SET(stFn.DT1,i))
		{
			fn = i+1;
			break;
		}
	}
	fn += (stFn.DT2 << 3); 

	return fn;
}

void CMainFrame::OnCopyframe()
{
	CString strCopy = m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemText (m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.m_itemYes , 2);
	if (strCopy == "")
	{
		return;
	}
	CStringA strA;
	strA = strCopy;
	if(OpenClipboard())   
	{   
		HGLOBAL   clipbuffer;   
		char   *   buffer;   
		EmptyClipboard();   
		clipbuffer   =   GlobalAlloc(GMEM_DDESHARE,   strA.GetLength()+1);   
		buffer   =   (char*)GlobalLock(clipbuffer);   
		strcpy(buffer, (LPSTR)(LPCSTR)strA);
		GlobalUnlock(clipbuffer);   
		SetClipboardData(CF_TEXT,clipbuffer);   
		CloseClipboard();   
	}
}


void CMainFrame::OnClose()
{
	
    CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if(6 == MessageBox(_T("������������У��Ƿ��˳���") , _T("ϵͳ��ʾ") ,MB_YESNO))
	{
		//m_access.DelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("TPShow"),_T(""));
		m_access.DelectDataFromTable(pMain->m_PeiZhi_db,_T("TPShow"),_T(""));
		CMDIFrameWndEx::OnClose();
	}
}

CString CMainFrame::GetRecvErrName(INT8U nChoose)
{
	CString str;
	switch(nChoose)
	{
	case 0:
		str = _T(">>>>ʧ��:ͨ�ų�ʱ");
		break;
	case 1:
		str = _T(">>>>ʧ��:��Ч���ݵ�Ԫ");
		break;
	case 2:
		str = _T(">>>>ʧ��:���ȴ�");
		break;
	case 3:
		str = _T(">>>>ʧ��:У�����");
		break;
	case 4:
		str = _T(">>>>ʧ��:��Ϣ�಻����");
		break;
	case 5:
		str = _T(">>>>ʧ��:��ʽ����");
		break;
	case 6:
		str = _T(">>>>ʧ��:����ظ�");
		break;
	case 7:
		str = _T(">>>>ʧ��:��Ų�����");
		break;
	case 8:
		str = _T(">>>>ʧ��:���Ӧ�ò���Ӧ��");
		break;
	case 9:
		str = _T(">>>>ʧ��:���ڵ�æ");
		break;
	case 10:
		str = _T(">>>>ʧ��:���ڵ㲻֧�ִ�����");
		break;
	case 11:
		str = _T(">>>>ʧ��:�ӽڵ㲻Ӧ��");
		break;
	case 12:
		str = _T(">>>>ʧ��:�ӽڵ㲻������");
		break;
	}
	return str;
}
CString CMainFrame::GetAckErrName(INT8U nChoose)
{
	CString str;
	switch(nChoose)
	{
	case 0x13://ʧ��
		str = _T("ʧ��");
		break;
	case 0x30://SEQ��һ��
		str = _T("SEQ��һ��");
		break;
	case 0x0A://���ڵ㲻֧�ִ�����
		str = _T("���ڵ㲻֧�ִ�����");
		break;
	case 0xA0://ͨѶ��ʱ
		str = _T("ͨѶ��ʱ");
		break;
	default:
		str = _T("��������");
		break;
	}
	return str;
}

void CMainFrame::InsertItemToOnlineList(CString strTableName)
{
	//ShowNetListView *pViewOnlineList=(ShowNetListView*)m_cSplitter.GetPane(0,1);//����OnCreate������
	m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.DeleteAllItems();
	CString strNumb;
	CString m_strlist[1000];
	CString str;
	CString str_nodeNum = _T("");
	CString strAllDatalist[500][6];
	CString f_strDatalist[6][500];
	int nNumb = 0 , nAlldataNumb;
	int n = 0 , m = 0 , i = 0;
	m_access.SelectDataFromTable(m_PeiZhi_db/*_T(".\\�����ļ�\\HistTPShow.accdb")*/, strTableName , _T("TP_MAC,TP_TEI,TP_PTEI,TP_ROLE") ,_T("") ,m_strlist ,nAlldataNumb);
	if(nAlldataNumb>0){
		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			m_tools.Split(m_strlist[n] , _T("$") ,strAllDatalist[n] , nNumb);
	        str.Format(_T("%d") , n + 1);
	        m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.InsertItem(n,str);
	        m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,1,strAllDatalist[n][0]);
	        m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,2,strAllDatalist[n][1]); 
			m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,3,strAllDatalist[n][2]);
			if(strAllDatalist[n][3]==_T("2")){
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("CCO"));
			}
			else if(strAllDatalist[n][3]==_T("4")){
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("STA"));
			}
			else if(strAllDatalist[n][3]==_T("6")){
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("PCO"));
			}
			else{
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("δ֪��ɫ"));
			}
		}
	}


	//pViewOnlineList->GetListCtrl().InsertItem(n , strNumb);
	//pViewOnlineList->GetListCtrl().SetItemText(n , 1 , strAddress);
	////pViewOnlineList->GetListCtrl().SetItemText(n , 1 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	//pViewOnlineList->GetListCtrl().SetItemText(n , 2 , strTEI);
	//pViewOnlineList->GetListCtrl().EnsureVisible(n,FALSE);
	//pViewOnlineList->GetListCtrl().RedrawItems(n,n);
}

void CMainFrame::OnJzq()
{
	// TODO: �ڴ���������������
	m_bJZQ=!m_bJZQ;
	m_bCKQ=!m_bJZQ;
}


void CMainFrame::OnUpdateJzq(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_bJZQ);   
}


void CMainFrame::OnCkq20()
{
	// TODO: �ڴ���������������
	m_bCKQ=!m_bCKQ;
	m_bJZQ=!m_bCKQ;
}


void CMainFrame::OnUpdateCkq20(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_bCKQ); 
}
