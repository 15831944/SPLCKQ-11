// TESTInterChangEability_CCO.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTInterChangEability_CCO.h"
#include "ImitateMeterDlg.h"
#include "SimJZQ.h"
extern CSimJzq   gSimJzq;

#include "GW13762.h"
extern CGW13762 Cgw13762;

#include "SimMeter.h"
extern CSimMeter  gSimMeter;

#include "gPublicObjct.h"
#include "MyFunLib.h"

#include "LogFile.h"
extern CLogFile plog;

// CTESTInterChangEability_CCO

IMPLEMENT_DYNAMIC(CTESTInterChangEability_CCO, CWnd)

CTESTInterChangEability_CCO::CTESTInterChangEability_CCO()
{

}

CTESTInterChangEability_CCO::~CTESTInterChangEability_CCO()
{
}


BEGIN_MESSAGE_MAP(CTESTInterChangEability_CCO, CWnd)
END_MESSAGE_MAP()
void CTESTInterChangEability_CCO::C3762_TEST(HTREEITEM hTree)
{
	CImitateMeterDlg * pMainDlg = (CImitateMeterDlg *)theApp.m_pMainWnd;
	if (!pMainDlg->m_bConnected)
	{
		AfxMessageBox("���ģ�⼯��������!");
		return;
	}
	if (!pMainDlg->m_bConnected2)
	{
		AfxMessageBox("���ģ�����!");
		return;
	}
	INT8U ack;
	pMainDlg->m_treeProject.Expand(hTree,TVE_EXPAND);//չ�����ڵ�
	HTREEITEM hNextItem = pMainDlg->m_treeProject.GetNextItem(hTree,TVGN_NEXTVISIBLE);
	CString strName;
	INT8U allSucesscnt = 0;
	INT8U allfailcnt = 0;;
	INT8U resucnt=0;
	INT8U refailcnt=0;
	while (hNextItem)
	{
		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			switch(atol(strName.Mid(0,2)))
			{
			case 1://

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
				//ack = CCO_STASetHostNodeAddress();
				//StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName,0);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
			case 2://
				break;

			}
			if (m_hThreadsend==NULL)//������;ֹͣ����
			{
				break;
			}
		}
		hNextItem = pMainDlg->m_treeProject.GetNextItem(hNextItem,TVGN_NEXTVISIBLE);	
	}
	plog.saveLog_StaCnt(allSucesscnt,allfailcnt,DATA_FILE,TIME,"�ܲ��������� ");
	if(allfailcnt == 0)
		plog.saveLog_testresult(DATA_FILE,TIME,"�ܽ���� ",DACK_SUCESS,2);
	else
		plog.saveLog_testresult(DATA_FILE,TIME,"�ܽ���� ",DACK_FAILURE,2);
}


// CTESTInterChangEability_CCO message handlers


