#pragma once
#include "afxcmn.h"
#include <vector>
#include "Tools.h"
#include "afxwin.h"
#include "DlgFile.h"
#include "DialogSyncNodeFile.h"

#define TIMER_ID_CYCLE (200)
#define TIMER_ID_LAST (300)
#define RM_SUCCESS (0)
#define RM_NO06F2 (1)
#define RM_06F2SEQERR (2)
#define RM_00F1SEQERR (3)
#define RM_NOACK (4)
#define RM_UNKNOWNERR (255)
// DlgExtReadMeter dialog

struct s_NodeList
{
	
	CString node;
	INT8U prot_type;//Э������
	INT8U is_met;//�Ƿ����ϱ�,�У� 1��û�� �� 0
	INT8U status;//״̬���ɹ�:1��ʧ�ܣ�0
};




class DlgExtReadMeter : public CDialogEx
{
	DECLARE_DYNAMIC(DlgExtReadMeter)

public:
	DlgExtReadMeter(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgExtReadMeter();

// Dialog Data
	enum { IDD = IDD_DIALOG_READMT };



public:
	
	bool m_bTerminateButtun;//����·�ɲ��ť

	CEdit m_editReadCycle;//�������ڼ��
	double m_fcycle;
	CEdit m_editReadLast;//�������ʱ��
	double m_flast;
	bool m_bSettimer;//����ʱ�ӱ�־
	CEdit m_ReadType;//�����ȡ����
	CEdit m_str645Frame;//Ҫ���͵�645֡����
	CEdit m_editShow;//��ӡ����
	CButton m_btnStartReadMT;
	CButton m_btnStopReadMT;
	CComboBox m_cbtnDi;

	CTools m_tools;


	sPartQGDW376_2CreatFrame m_ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame m_ptRecvQGDW376_2;

	INT32U m_Di;
	INT32U m_dotnum;//���ݵ�С������
	CWinThread* MyThread;
	
	CEdit m_RmStatus;
	BOOL m_bReadMeterStatus;//·�ɹ���״̬
	CEdit m_RmTotal;
	INT32U m_nTotal;
	CEdit m_RmSuccess;
	INT32U m_nReadSuccess;
	CEdit m_RmFail;
	INT32U m_nReadFail;
	INT32U m_iRound;

	Dlgfile *dlgfile;
	Dlgfile *dlgsavenodefile;
	//Dlgfile *dlgsyncnodefile;
	DialogSyncNodeFile *dlgsyncnodefile;

	

	INT32U m_EventID;
	

	std::vector<s_NodeList> v_snodelist;
	std::vector<s_NodeList>::iterator iter_node,iter_end;
	std::vector <s_NodeList> v_nodejzq;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


	

public:
	int ReadMeter();
	void SetWindowText(CString strData);
	void SetWindowText(INT32U idata);
	void Update();
	BOOL OnInitDialog();
	void router_start();
	void router_suspend();
	void router_resume();
	BOOL router_status();
	INT32U ReadNodeNumber();
	bool ReadMasterMAC(INT8U MAC[6]);

	void PrintNodeTable();
	INT8U GetNodeTable(INT32U nTotal);
	UINT SyncNodeFile(INT16U nodenumperframe);
	UINT SaveNodeFile();

	INT8U MatchNode_CheckRepeat(CString SearchStaMac,INT16U &StaIndex);
	void SaveFailureNode();

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedButton1Rm();//����·��
	afx_msg void OnBnClickedButton2Rm();//��ͣ·��
	afx_msg void OnBnClickedButton3Rm();//�ָ�·��
	afx_msg void OnBnClickedButton4Rm();//��ʼ·�ɳ���
	afx_msg void OnBnClickedButton6Rm();//���ñ����ļ�
	afx_msg void OnBnClickedButton5Rm();//����·�ɳ���
	


	
	CEdit m_editRound;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
};

static UINT ThreadReadMeter(LPVOID pParam);
static UINT ThreadSwitch(LPVOID pParam);
