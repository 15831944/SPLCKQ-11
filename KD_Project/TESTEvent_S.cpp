// TESTEvent_S.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTEvent_S.h"
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

// CTESTEvent_S

IMPLEMENT_DYNAMIC(CTESTEvent_S, CWnd)

CTESTEvent_S::CTESTEvent_S()
{

}

CTESTEvent_S::~CTESTEvent_S()
{
}


BEGIN_MESSAGE_MAP(CTESTEvent_S, CWnd)
END_MESSAGE_MAP()
void CTESTEvent_S::C3762_TEST(HTREEITEM hTree)
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
	INT16U allSucesscnt = 0;
	INT16U allfailcnt = 0;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	  gSimJzq.SetHostAdd();
	  gSimJzq.Router_PaRst();
	while (hNextItem)
	{
		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			switch(atol(strName.Mid(0,2)))
			{
			case 1://1.	����ַCCO����  ��ʵ�ʱ�ģ���-��ȷ��

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    ack= TestOneAddSetPa();
				ack=TestOneEventAckOKNO(0x01,0x01);
			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
			case 2://2.	����ַCCO����  ��ʵ�ʱ�ģ���-�ط���

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    ack= TestOneAddSetPa();
				ack=TestOneEventAckOKNO(0x02,0x01);
			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
			case 3://3.	 ����ַCCO����  ��ʵ�ʱ�ģ���-���ظ�

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    ack= TestOneAddSetPa();
				ack=TestOneEventNoAckSeqErr(0x03,0x01);
			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
		  case 4://4.	 ����ַCCO����  ��ʵ�ʱ�ģ���-��SEQ��һ��

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    ack= TestOneAddSetPa();
				ack=TestOneEventNoAckSeqErr(0x04,0x01);
			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
			case 5://5.	���ַCCO����  ��ʵ�ʱ�ģ�����ȷ��

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    ack= TesMoreAddSetPa();
				ack=TestMoreEventAckOKNO(0x01,0x01);
			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
			case 6://6.	���ַCCO����  ��ʵ�ʱ�ģ����ط���

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    ack= TesMoreAddSetPa();
				ack=TestMoreEventAckOKNO(0x02,0x01);
			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
			case 7://���ַCCO����  ��ʵ�ʱ�ģ���SEQ��һ��

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    ack= TesMoreAddSetPa();
				ack=TestOneEventNoAckSeqErr(0x03,0x01);
			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
			case 8://���ַCCO����  ��ʵ�ʱ�ģ���SEQ��һ��

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    ack= TesMoreAddSetPa();
				ack=TestOneEventNoAckSeqErr(0x04,0x01);
			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
			case 9://9.	���ֻظ�����

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    ack= TesMoreAddSetPa();
				ack=TestMoreEventPartNoAck(0x01);
			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
	
			default:
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
	ack = QueAckFormAckCnt(allfailcnt);
	plog.saveLog_testresult(DATA_FILE,TIME,"�ܽ���� ",ack,2);
}



// CTESTEvent_S message handlers


