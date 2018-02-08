// TESTReadMeter_NOBINGF_M.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTReadMeter_NOBINGF_M.h"
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

// CTESTReadMeter_NOBINGF_M

IMPLEMENT_DYNAMIC(CTESTReadMeter_NOBINGF_M, CWnd)

	CTESTReadMeter_NOBINGF_M::CTESTReadMeter_NOBINGF_M()
{

}

CTESTReadMeter_NOBINGF_M::~CTESTReadMeter_NOBINGF_M()
{
}


BEGIN_MESSAGE_MAP(CTESTReadMeter_NOBINGF_M, CWnd)
END_MESSAGE_MAP()

void CTESTReadMeter_NOBINGF_M::C3762_TEST(HTREEITEM hTree)
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
	INT8U ack = DACK_FAILURE;
	pMainDlg->m_treeProject.Expand(hTree,TVE_EXPAND);//չ�����ڵ�
	HTREEITEM hNextItem = pMainDlg->m_treeProject.GetNextItem(hTree,TVGN_NEXTVISIBLE);
	CString strName;
	INT8U allSucesscnt = 0;
	INT8U allfailcnt = 0;;
	INT8U resucnt=0;
	INT8U refailcnt=0;
	TestSetPa();

	while (hNextItem)
	{
		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			ClrComBuf();//�崮��
			//plog.saveLog_strAll(TIME,"�崮�� ",0);
			switch(atol(strName.Mid(0,2)))
			{
			case 1://��������ת�����ԣ�ģ���
				{
					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
					ack=TestReadMeterCnt(100,0,1);
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;
			case 2://	�������ε㳭������ԣ�ģ���
				{
					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
					ack=TestReadMeterCnt(100,1,1);
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;
			case 3://	����DI���ԣ�ʵ�ʱ���ģ���
				{
					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
					ack=TestReadMeterErrDi(5,0);
					if(ack == DACK_SUCESS)
					{
						ack=TestReadMeterErrDi(5,1);
					}
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;	
			case 4://4.	AFN=02H , F1������֡���ԣ��м��޽��գ���ģ���
				{
					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
					ack=TestMoreReadMeterNoRcv(0);
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;	

			case 5://5.	AFN=13H , F1������֡���ԣ��м��޽��գ���ģ���
				{
					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
					ack=TestMoreReadMeterNoRcv(1);
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;	
			case  6: //6.	AFN=02H , F1��֡���ԣ��м�Ҫ���գ���ʵ�ʱ���ģ���
				{
					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);				
					ack=TestMoreReadMeterRcv(0);
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;	

			case 7://7.	AFN=13H , F1��֡���ԣ��м�Ҫ���գ���ʵ�ʱ���ģ���
				{
					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
					ack=TestMoreReadMeterRcv(1);
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;
			case 8://8.	��֡���ԣ�ģ���
				{
					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
					ack=TestReadMeterLongFame(5,0,1);
					if(ack == DACK_SUCESS)
					{
						ack=TestReadMeterLongFame(5,1,1);
					}
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;	
			case 9://9.	����δ�ɹ�����ʵ�ʱ���ģ���
				{
					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
					ack=TestSeqNONet(5,0);
					if(ack == DACK_SUCESS)
					{
						ack=TestSeqNONet(5,1);
					}
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;
			case 10://10.	AFN=02H , F1,���ֳɹ�����֡���ԡ�

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
				ack = TestPartAckNo(0);

				StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				break;
			case 11://11.	AFN=13H , F1,���ֳɹ�����֡���ԡ�
				{

					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);

					ack = TestPartAckNo(1);
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;

			case 12://12. AFN=02H �� F1���ط����������ʱ�����

				{


					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
					ack = TestIntevalTime(0);
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;
			case 13://13.	AFN=13H��F1���ط����������ʱ�����
				{


					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
					ack = TestIntevalTime(1);
					StaSucessCnt(ack,allSucesscnt,allfailcnt);
					plog.saveLog_testresultAll(TIME,strName+"����� ",ack,1);
				}
				break;

				//case 14://14.	AFN=02H , F1������֡���ԣ��м��޽��գ�
				//	  {

				//		
				//              plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,0);
				//         ack = TestMoreReadMeterNoRcv(0);
				//		 StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//		 plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				//		 plog.saveLog_testresultAll(TIME,"����� ",ack,0);
				//	  }
				//	  break;

				//case 15://15.	AFN=13H , F1������֡���ԣ��м��޽��գ�
				//	  {
				//              plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,0);
				//          ack = TestMoreReadMeterNoRcv(1);
				//		 StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//		 plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				//		 plog.saveLog_testresultAll(TIME,"����� ",ack,0);
				//	  }
				//	  break;
				//case 16://16.	AFN=02H , F1��֡���ԣ��м�Ҫ���գ�
				//	  {

				//		
				//              plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,0);
				//         ack = TestMoreReadMeterRcv(0);
				//		 StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//		 plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				//		 plog.saveLog_testresultAll(TIME,"����� ",ack,0);
				//	  }
				//	  break;

				//case 17://17.	AFN=13H , F1��֡���ԣ��м�Ҫ���գ�
				//	  {
				//	     plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,0);
				//          ack = TestMoreReadMeterRcv(1);
				//		 StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//		 plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				//		 plog.saveLog_testresultAll(TIME,"����� ",ack,0);
				//	  }
				//	  break;
			default:
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
void CTESTReadMeter_NOBINGF_M:: ClrComBuf()
{
	gSimMeter.ClrSimMeterComData();
	gSimJzq.ClrZjqComData();
	Sleep(10000);
}
// CTESTReadMeter_NOBINGF_M message handlers


