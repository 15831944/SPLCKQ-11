// TESTReadADD.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTReadADD.h"
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

// CTESTReadADD

IMPLEMENT_DYNAMIC(CTESTReadADD, CWnd)

CTESTReadADD::CTESTReadADD()
{

}

CTESTReadADD::~CTESTReadADD()
{
}


BEGIN_MESSAGE_MAP(CTESTReadADD, CWnd)
END_MESSAGE_MAP()
void CTESTReadADD::C3762_TEST(HTREEITEM hTree)
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
	INT16U allfailcnt = 0;;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	while (hNextItem)
	{
		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			switch(atol(strName.Mid(0,2)))
			{
			case 1://
				{

					plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,1);
				    sAckAmtMsg  ReadAmtMsg;
					gSimMeter.SetSimMeterRunFg(1);//����ģ�������
					gSimMeter.ClrALLNoAckDi();
					gSimMeter.ClrReadAmtCnt();
					gSimMeter.SetAckAmtFg(0);
						for(INT8U i=0;i<2;i++)
						{
							if(((i+1)%2)==0)
							{
                               ChangeAmtBps(2400);
							}
							else
							{
                              ChangeAmtBps(9600);

							}
								while(1)
								{
									if(gSimMeter.QueReadAmtCnt() >= 12)
									{
										gSimMeter.QueReadAmtMsg(ReadAmtMsg);
											break;
									}
								}
					
								for(INT8U m=0;m+1<ReadAmtMsg.s_RcvCnt;m++)
								{
									ReadAmtMsg.s_Time[m]=QueSysTimeVal(ReadAmtMsg.s_Time[m],ReadAmtMsg.s_Time[m+1]);
								}
								for(INT8U m=0;m<11;m++)
								{
									if((m==2) ||(m==5)||(m==7)||(m==9))
									{
										//�л�BPS���ط����
										if((ReadAmtMsg.s_Time[0]>=60*1000)&&(ReadAmtMsg.s_Time[0]>=70*1000))
										{
											ack = DACK_SUCESS;
										}
										else
										{
											ack = DACK_FAILURE;
										}
									}
									else
									{
										//ͬһBPS���ط����
										if((ReadAmtMsg.s_Time[0]>=6*1000)&&(ReadAmtMsg.s_Time[0]>=8*1000))
										{
											ack = DACK_SUCESS;
										}
										else
										{
											ack = DACK_FAILURE;
										}
									}
									StaSucessCnt(ack,resucnt,refailcnt);
								}
                              
								
						}

						 ChangeAmtBps(2400);
						 gSimMeter.ClrReadAmtCnt();
					     gSimMeter.SetAckAmtFg(1);
						 Sleep(60*1000);
						 if(gSimMeter.QueReadAmtCnt() == 1)
						 {
							ack = DACK_SUCESS;
						}
						else
						{
							ack = DACK_FAILURE;
						}

						 StaSucessCnt(ack,resucnt,refailcnt);

						    if(refailcnt==0)
							{
								ack = DACK_SUCESS;
							}
							else
							{
								ack = DACK_FAILURE;
							}
		
						plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,strName+"  �����",1);
		
				}
				break;
			default://
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


// CTESTReadADD message handlers


