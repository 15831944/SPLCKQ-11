
// MainFrm.h : CMainFrame ��Ľӿ�
//
#include "ChildFrm.h"
#include "FrameSetNet.h"
#include "Frame3762.h"
#include "Form698.h"
#include "MainTestFrame.h"
#include "cSerBuf_LoopRcv.h"
#include "GW13762.h"
#include "CSG13762.h"
#include "SimMeter.h"
#include "Tools.h"
#include "cSerBuf_LoopRcv.h"
#include "FrameShowWnd.h"
#include "FrameShowWndTree.h"
#include "gPublicObjct.h"
#include "resource.h"
#include "LogFile.h"
#include "Tools.h"
#include "AccessData.h"
#include "CKQViewTabErrMet.h"
#pragma once
#define MAXBLOCK 4096

#define CONNECTCKQ  1
#define CONNECTCCO  2
#define CONNECTSTA  3

#define OPENNET 1
#define OPEN13762 2
#define OPEN698 3

#define START_CODE	0X68
#define END_CODE	0X16

#define DOWN 0//���з���
#define UP	 1//���з���

#define LAUNCH 1
#define ANSWER 0

#define MASTER_NOD	0
#define SLAVE_NOD	1

#define BPLC 3 //����ز�

#define R_INFOR_SIZE 6

#define AFN_FN_LENGTH 3

#define  DATA_FILE	 0
#define  DataIfo	1
#define  PARS_FILE	2
#define  OUTPUT 0
#define  TIME 1
#define  NOTIME 0
#define  INPUT_DATA	 1

#define MAX_BUF_LENGTH 4096

#define AUTO_TEST 1
#define AUTO_TEST_START_NOD_ADDR 1
#define READ_SLAVE_NOD_NUM_MAX 0XFF
#define COM_ACK_TIMEOUT_SECONDS 5//15//5//���ڵȴ���Ƭ����Ӧʱ��

#define FLASH_READ_LENGTH 1024
#define NOD_NUM_OF_1KFLASH 64//1KFLASH�ϵĽڵ���Ϣ����
#define AFN_MAX_NUM 23

#define SAVE_LOG 1//�Ƿ񱣴�LOG�ļ�

#define MAX_NOD_ADDR 999999999999//�ڵ��ַ���ֵ
#define FLASH_DELED_DATA 0XFFFFFFFFFFFF//ɾ����Ľڵ��ַ


enum AFN
{
	AFN00=0,AFN01,AFN02,AFN03,AFN04,AFN05,AFN06,AFN10=0X10,AFN11,AFN12,AFN13,AFNF0=0XF0
};

enum ProtocolType
{
	TRANSPARENT_TRANS=0,DLT645_1997,DLT645_2007
};

enum enum_AUTO_TEST_SATE{AUTO_TEST_WRITE_READ=0,	AUTO_TEST_ADD_DEL,	AUTO_TEST_ELECTRICAL_METER,	AUTO_TEST_3762PROTOCAL,	 AUTO_TEST_FLOW_METER ,AUTO_TEST_CHAOBIAO, TEST_STAT_RESET_READ};//LCJ3

typedef union
{
	BYTE bitByte;
	struct 
	{
		BYTE comunate_mod:6;
		BYTE prm:1;
		BYTE dir:1;
	}bits;
}UN_C_DATA;//control data

typedef union
{
	BYTE bitByte[6];
	struct 
	{
		BYTE route			:1;//·�ɱ�ʶ
		BYTE subNode		:1;
		BYTE module			:1;
		BYTE collisDetect	:1;
		BYTE routeLevel		:4;//byte1

		BYTE channel		:4;
		BYTE errCorrect		:4;//byte 2

		BYTE prediAnserBn	;//byte 3 predictAnswerbyteNum

		WORD rate			:15;
		WORD rateUnit		:1;//���ʵ�λ byte4-5

		BYTE serialNum		;//byte 6
	}bits;
}UN_DOWN_R_DATA;//control data

typedef union
{
	BYTE bitByte[6];
	struct 
	{
		BYTE route			:1;//·�ɱ�ʶ
		BYTE resved1		:1;
		BYTE module			:1;
		BYTE resved2		:1;
		BYTE routeLevel		:4;//byte1

		BYTE channel		:4;
		BYTE resved3		:4;//byte 2

		BYTE RealPhaseLine	:4;//byte 3 predictAnswerbyteNum
		BYTE meterChStyle	:4;

		BYTE finalCmdQual	:4;
		BYTE finalAnsQual	:4;//���ʵ�λ byte4

		BYTE events			:1;//byte 5
		BYTE resved4		:7;

		BYTE serialNum;			//byte6
	}bits;
}UN_UP_R_DATA;//������Ϣ����

typedef union
{
	UN_DOWN_R_DATA	R_down;
	UN_UP_R_DATA	R_up;
}UN_R_DATA;

typedef union
{
	BYTE data[3];
	struct 
	{
		BYTE test;
		WORD route			:15;//·�ɱ�ʶ
		WORD K				:1;
	}bits;
}UN_ST_TEST;


typedef struct
{
	BYTE DT1;
	BYTE DT2;
}ST_Fn;

typedef struct tpd_ST_1376_2_FRAME{
	WORD L;
	UN_C_DATA C;

	UN_R_DATA R;//������R��ѡ

	BYTE A1[6];
	BYTE A2[6];
	BYTE A3[6];

	BYTE AFN;

	ST_Fn Fn;

	BYTE CS;
}ST_1376_2_FRAME;


typedef struct tpd_SAVE_376_2_APNFN{

	unsigned char apn;
	unsigned char fn;
	unsigned char SEQ;

}SAVE_376_2_APNFN;

#define MAX_NOD_NUM 1024 //���ڵ���
#define MAX_READ_NUM 10//��Ƭ��һ�������ȡ�����ڵ��������������᷵�ط���
typedef struct TYPE_ST_RECV_NOD_INFOR//���սڵ���Ϣ
{
	WORD wTotlaNodNum;//�ܽ���������������Ҳ�ǵ�ǰд��Ľڵ�����
	WORD wSumCurrentNodNum;//��ǰ��������ۼ�
	BYTE byCurrentNodNum;//��ǰӦ��ڵ���Ŀ

	UINT64 L64NodAddrs[MAX_NOD_NUM];//���нڵ�ĵ�ַ,��Ϊ���ִ洢������Ƚ�
	WORD wAddrPos;//��ַ��������д��ָ��

	WORD wSlaveNodRdSN;//��ȡ�Ĵӽڵ����
	WORD wNeedReadNodTotalNum;//��Ҫ��ȡ�Ľڵ�����
	BYTE byRdNodNumNow;//������Ҫ��ȡ�Ľڵ�����
}ST_RECV_NOD_INFOR;

typedef struct TYPE_ST_FLASH_INFOR//���սڵ���Ϣ
{
	UINT64 U64FlashAddrs[MAX_NOD_NUM];//���нڵ�ĵ�ַ,��Ϊ���ִ洢������Ƚ�
	WORD wAddrPos;//��ַ��������д��ָ��
}ST_FLASH_INFOR;


typedef struct TYPDEF_ST_COM_BUF_INFOR
{
	INT16U ReadPos;//��ָ��
	INT16U WritePos;//дָ�룬һ���ڽ�����ʱ���ȡ����ȷ��һ֡����֮�󣬽�����дָ��Ļ������дָ��ͬʱ����
	INT16U wFrameLength;//һ֡����
}ST_COM_BUF_INFOR;

typedef struct TYPDEF_ST_COM_BUF
{
	ST_COM_BUF_INFOR stInfor;
	INT8U m_BufRcv[MAX_BUF_LENGTH];
}ST_COM_BUF;

#define ADD_SALVE_NODE_NUM_IN_ADT 200
#define DEL_SALVE_NODE_NUM_IN_ADT 100//ɾ���������ܳ���д�������
#define FINAL_ADD_SAVLE_NUM_1TIME_IN_ADT   (ADD_SALVE_NODE_NUM_IN_ADT - DEL_SALVE_NODE_NUM_IN_ADT)
typedef struct TYPDEF_ST_ADD_DEL_NOD_TEST
{
	BYTE del_node_num;//ɾ���ӽڵ�����

	BYTE before_del_pos;//��д��Ľڵ㣬��ʼɾ���ڵ��ǰһ���ڵ�λ�ã���ʣ�µ�ǰ�νڵ�����һ���ڵ�       ����������������1-200��������˵�ģ��������䰴�������
	BYTE after_del_pos;//��д��Ľڵ㣬ɾ���ڵ�����һ���ڵ�ĺ�һ���ڵ�λ�ã���ʣ�µĺ�νڵ�Ŀ�ʼ�ڵ�

	WORD nodCounter;//ADT ����ʱ����ַ��ڵ�����һ��
}ST_ADD_DEL_NOD_TEST;

class CMainTestFrame;
class CFrameSetNet;
class CFrame3762;
//class CChildWnd13762;
class CForm698;
class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
public://��������
	CString m_data;
	CString m_dataMessage;
	INT8U m_376seq;
	CFont m_Font70;
	CFont m_Font100;
	CFont m_Font120;
	CString m_strSysDateTime;
	CString	m_strSysDateTime_rx;
	CString	m_strSysDateTime_tx;
	CString m_strSysTime;
	CStringList m_FenzuFnList;
	INT8U m_HostNodeAddress[6];
	CString m_strMAddress;
	CString GetRecvErrName(INT8U nChoose);
	CString GetAckErrName(INT8U nChoose);
public://�˵�����
	bool m_bCKQ;
	bool m_bJZQ;
	bool m_bsetopen;
	bool m_bsetclos;
	INT8U m_nChooseView;
public://�����жϲ���
	CString m_PeiZhi;
	CString m_PeiZhi_db;
	int NW_OR_GW;
public://״̬������
	CMFCStatusBar     m_wndStatusBar;
	BOOL LoadStatusBar();
	void SetStatusBat(CString strPort);
public://���ڲ���
	bool m_bCommunictStop;
	CWinThread* m_pThread;  // �������߳�
	volatile BOOL m_bConnected;  //�����Ƿ�����
	volatile HWND m_hTermWnd;    //������ͼ�Ĵ��ھ��
	volatile HANDLE m_hPostMsgEvent; // ����WM_COMMNOTIFY��Ϣ���¼�����
	OVERLAPPED m_osRead, m_osWrite; // �����ص���/д	
	volatile HANDLE hCom;  //COM�ھ��
	void SendBufToCOMM(INT8U * sendbuf,INT16U sendLen , INT8U nType = 0);
	void BF_SendBufToCOMM(INT8U * sendbuf,INT16U sendLen , INT8U nType = 0);
	//cSerBuf_LoopRcv  m_loopRcv64507;
	//cSerBuf_LoopRcv  m_loopRcv13762;
	DWORD ReadComm(INT8U *buf, DWORD dwLength);//�Ӵ����н������ݣ�ÿ��һ���ֽ�
	CString GetCommMessage(CString strPort, CString strBaud , CString strParity , CString strDatabit, CString strStopbit);//ͨ��������Ϣ��д����Ϣ��
// ���ڲ���
public:
	CMainTestFrame * m_pMainTestFrame;
	CFrameSetNet * m_pFrameNetWork;//�Ӵ��ڶ���ָ��
	bool m_bNetWork;//�ж��Ӵ����Ƿ��
	bool m_bNetWorkOpen;//�ж��Ӵ����Ƿ��
	CFrame3762 * m_pFrame3762;
	bool  m_bFrame3762;
	CAccessData m_access;
	CForm698 * m_pFrame698;
	bool  m_bFrame698;
public://�����Ӵ����ڹ�������
	int m_nConnectType;
// ����
public://��־
	bool bAutoTestRunCmd;//�߳����л���ֹͣ�ı�ʶ
	unsigned char getFn(ST_Fn stFn);
	void Creat_File();
	void Close_File();
public:
	CSplitterWnd m_litterWnd;
// ����
public:
	CTools m_tools;
	int m_nCopyFrame;
	CFrameShowWnd m_FrameShowWnd;
	CFrameShowWndTree mm_FrameShowWndTree;
	void InsertItemToOnlineList(CString strTableName );
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	
	CMFCToolBarImages m_UserImages;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg LRESULT OnComm(WPARAM wParam, LPARAM lParam);
	afx_msg void OnConnectOpen();
	afx_msg void OnConnectClose();
	afx_msg void OnNetwortOpen();
	afx_msg void OnUpdateConnectOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConnectClose(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void On3762Open();
	afx_msg void OnFrameshow();
	afx_msg void OnCopyframe();
	afx_msg void OnClose();
//	afx_msg void OnIdrRbmenuMeterr();
	afx_msg void OnJzq();
	afx_msg void OnUpdateJzq(CCmdUI *pCmdUI);
	afx_msg void OnCkq20();
	afx_msg void OnUpdateCkq20(CCmdUI *pCmdUI);
};


