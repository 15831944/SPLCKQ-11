// TESTEvent_M.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTEvent_M.h"

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

// CTESTEvent_M

IMPLEMENT_DYNAMIC(CTESTEvent_M, CWnd)

CTESTEvent_M::CTESTEvent_M()
{

}

CTESTEvent_M::~CTESTEvent_M()
{
}


BEGIN_MESSAGE_MAP(CTESTEvent_M, CWnd)
END_MESSAGE_MAP()
void CTESTEvent_M::C3762_TEST(HTREEITEM hTree)
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
			case 10://10.	STA���ظ����ԣ�ģ���

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    //ack= TesMoreAddSetPa();
				ack=TestStaNoAck();
			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
				break;
			case 11://11.	�¼�IO�仯��״̬�ֲ��仯���ԡ���ģ���

				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
			    //ack= TesMoreAddSetPa();
				ack=TestStaStaDataNoChang();
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

//	STA���ظ����ԣ�ģ���
INT8U CTESTEvent_M::TestStaNoAck(void)
{
	INT8U ack;
	gSimMeter.ClrALLNoAckDi();
	gSimMeter.ClrReadAmtCnt();
	gSimMeter.SetNoAckDi(0x04001501);
	MessageBoxDelayTime("��һֻSTA�����¼�",30*1000);
    sNoAckDiMsg  noackMsg;
	for(INT32U m=0;m<600;m++)
	{
		if(gSimMeter.QueNoDiAckmsg(0x04001501,noackMsg))
		{
			  if(noackMsg.s_RcvCnt>=3)
				break;
		}
		Sleep(1000);
	}

	ack=gSimMeter.CheckNoDiAckmsg(noackMsg);
	return ack;
}


//	STA״̬�ֲ��仯���ԣ�ģ���
INT8U CTESTEvent_M::TestStaStaDataNoChang(void)
{
 INT8U ack = DACK_FAILURE;
   INT8U AmtBuf[7+1];

	INT16U resucnt=0;
	INT16U refailcnt=0;

	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack = gSimJzq. Router_Stop();
 	 //gSimMeter.ChangeMeterData_645(0x04001501);
	 MessageBoxDelayTime("������¼�",30*1000);
	 ack = gSimJzq.EventOp(30*1000,50,0x01,DstDecodeDataFrame,AmtBuf,0);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 Sleep(100);
	 ack=CmpEventIsOnSta(AmtBuf,DstDecodeDataFrame.s_head.s_Msg_Seq,1,1);
	  StaSucessCnt(ack,resucnt,refailcnt);
	 //�����ϱ��б��¼����ҵ����¼�
	  ack=gSimJzq.ZjqNoRcvData(30*1000,50);
	  StaSucessCnt(ack,resucnt,refailcnt);

			 if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"STA״̬�ֲ��仯���ԣ�ģ��� ",1);
    return ack;
}


//----------------------------------------------------------------------
typedef struct
{
	INT8U  s_macadd[6+1];
	INT8U  s_PlcSeq;
    INT8U  s_sta;
	INT8U  s_Resendcnt;
	INT8U  s_maxcnt;
	INT32U  s_maxDlyTime;
	INT32U s_StartTime;
}sCCOEvent_ReportFmt;

//vSrcCnt�� ��ǰ���͵Ĵ�����CmpType��0 �ȶ������ϱ��б�  1 �ȶ����ϱ��б�
INT8U CEventPublic:: CmpEventIsOnSta(INT8U *vSrcAmtAdd,INT8U vSrcSeq,INT8U vSrcCnt,INT8U CmpType)
{
	INT8U ack;
	INT8U reack= DACK_FAILURE;
	INT16U cucnt;
	INT16U okcnt;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack =gSimJzq.HostSendRcv376_2NoBuf(0xF0,F2,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
	if(ack==DACK_SUCESS)
	{
      if(CmpType==0)
	  {
		   cucnt=DstDecodeDataFrame.s_RcvDataBuf[2];
		   for(INT16U m=0;  m<cucnt;m++)
		   {
			  if( CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[4+cucnt*8+2],vSrcAmtAdd,2)==EQU)
			  {
                if(vSrcSeq==DstDecodeDataFrame.s_RcvDataBuf[4+cucnt*8+2])
				{
                  if(vSrcCnt==DstDecodeDataFrame.s_RcvDataBuf[4+cucnt*8])
				  {
						reack = DACK_SUCESS;
						break;
				  }
				}
			  }

		   }

	  }
	  else
	  {
            cucnt=DstDecodeDataFrame.s_RcvDataBuf[2];
			okcnt=DstDecodeDataFrame.s_RcvDataBuf[4+cucnt*8+5];
		   for(INT16U m=0;  m<cucnt;m++)
		   {
			  if( CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[4+cucnt*8+5+1+m*8+2],vSrcAmtAdd,2)==EQU)
			  {
                if(vSrcSeq==DstDecodeDataFrame.s_RcvDataBuf[4+cucnt*8+5+1+m*8])
				{
					 reack = DACK_SUCESS;
					break;
				}
			  }

		   }

	  }

	}

	  plog.saveLog_testresult(DATA_FILE,TIME,"�ȶ��¼��ڲ����  ",reack,1);
 return reack;
}


//dan��ַ��������
INT8U   CEventPublic:: TestOneAddSetPa(void)
{
  INT8U ack = DACK_FAILURE;

	INT16U resucnt=0;
	INT16U refailcnt=0;
	//׼��
	 ack = gSimJzq.SetNodeAdd(0,1);
	 StaSucessCnt(ack,resucnt,refailcnt);
	ack = gSimJzq. Router_Stop();
	 ack=gSimJzq. QueAllNetSta(0,1,60);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 if(ack==DACK_SUCESS)
         {
			 if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		 }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"����ַ�������� ",1);
 return ack;
}

//���Ի�ȷ��0x01������0x02
INT8U  CEventPublic::  TestOneEventAckOKNO(INT8U acktype,INT8U CmpType)
{
   INT8U ack = DACK_FAILURE;
   INT8U AmtBuf[7+1];

	INT16U resucnt=0;
	INT16U refailcnt=0;

	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack = gSimJzq. Router_Stop();
 	 gSimMeter.ChangeMeterData_645(0x04001501);
	 MessageBoxDelayTime("������¼�",30*1000);
	 ack = gSimJzq.EventOp(30*1000,50,acktype,DstDecodeDataFrame,AmtBuf,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 Sleep(100);
	 ack=CmpEventIsOnSta(AmtBuf,DstDecodeDataFrame.s_head.s_Msg_Seq,1,1);
	  StaSucessCnt(ack,resucnt,refailcnt);
	 //�����ϱ��б��¼����ҵ����¼�
	  ack=gSimJzq.ZjqNoRcvData(30*1000,50);
	  StaSucessCnt(ack,resucnt,refailcnt);

	  ack = QueAckFormAckCnt(refailcnt);
		  
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"�¼����Գɹ� ",1);
    return ack;
}

//����SEQ��0x03,���ظ�0x04
INT8U CEventPublic::   TestOneEventNoAckSeqErr_Amt(INT8U acktype,INT8U CmpType)
{
 INT8U ack = DACK_FAILURE;
   INT8U AmtBuf[7+1];

	INT16U resucnt=0;
	INT16U refailcnt=0;
		sNoAckDiMsg   AFNnoack;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2;;

	 ack = gSimJzq.EventOp(30*1000,50,acktype,DstDecodeDataFrame,AmtBuf,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  Sleep(100);
	 ack=CmpEventIsOnSta(AmtBuf,DstDecodeDataFrame.s_head.s_Msg_Seq,1,0);
	  StaSucessCnt(ack,resucnt,refailcnt);
	    if((ack==DACK_SUCESS))
		   {
			   ack = DACK_FAILURE;
			    AFNnoack.s_Di=DstDecodeDataFrame.s_head.s_Msg_Seq;
				AFNnoack.s_RcvCnt=1;
				AFNnoack.s_Time[0]=GetSysTimeClk();
				for(INT8U m=0;m<26;m++)
				{
					ack = gSimJzq.EventOp(30*1000,50,acktype,DstDecodeDataFrame_2,AmtBuf,CmpType);
					if(ack==DACK_SUCESS)
					{
						ack=gSimJzq.CmpDecode3762(DstDecodeDataFrame,DstDecodeDataFrame_2);
						if(ack==DACK_SUCESS)
						{
                           AFNnoack.s_RcvCnt++;
						   if(AFNnoack.s_RcvCnt<=4)
				          {
							  AFNnoack.s_Time[AFNnoack.s_RcvCnt-1]=GetSysTimeClk();
						   }
						     Sleep(100);

	                         ack=CmpEventIsOnSta(AmtBuf,DstDecodeDataFrame.s_head.s_Msg_Seq, AFNnoack.s_RcvCnt,0);
							  StaSucessCnt(ack,resucnt,refailcnt);

						}
						else
						{
							
						 break;
						}
					}
					 if(AFNnoack.s_RcvCnt>=3)
						{
							break;
					    }
				  }
				}
			  Sleep(100);
		   ack=CmpEventIsOnSta(AmtBuf,DstDecodeDataFrame.s_head.s_Msg_Seq, AFNnoack.s_RcvCnt,1);
		   StaSucessCnt(ack,resucnt,refailcnt);

		 if(ack==DACK_SUCESS)
	   {
		  ack= gSimJzq.CmpReSendCntTime(AFNnoack,3,60*1000,180*1000);
	   }
		ack = QueAckFormAckCnt(refailcnt);
    plog.saveLog_NoAckMsg(DATA_FILE,TIME,"",AFNnoack,1);
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"�����¼��ظ�SEQ��0x03,���ظ�0x04 ",1);
    return ack;
}
//����acktype SEQ��0x03,���ظ�0x04  ; CmpType:0 ʵ�ʱ� 1 ����� 
INT8U CEventPublic::   TestOneEventNoAckSeqErr(INT8U acktype,INT8U CmpType)
{
   INT8U ack = DACK_FAILURE;
  

	INT16U resucnt=0;
	INT16U refailcnt=0;
	
	ack = gSimJzq. Router_Stop();
 	 gSimMeter.ChangeMeterData_645(0x04001501);
	 MessageBoxDelayTime("������¼�",30*1000);
	 ack=TestOneEventNoAckSeqErr_Amt(acktype,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	ack=gSimJzq.ZjqNoRcvData(60*1000*3,50);
	 StaSucessCnt(ack,resucnt,refailcnt);

		ack = QueAckFormAckCnt(refailcnt);
    return ack;
}

//���ַ��������
INT8U CEventPublic::  TesMoreAddSetPa(void)
{
  INT8U ack = DACK_FAILURE;

	INT16U resucnt=0;
	INT16U refailcnt=0;
	//׼��
	 ack = gSimJzq.SetNodeAdd(0,5);
	 StaSucessCnt(ack,resucnt,refailcnt);
	ack = gSimJzq. Router_Stop();
	 ack=gSimJzq. QueAllNetSta(0,5,60);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 if(ack==DACK_SUCESS)
         {
			ack = QueAckFormAckCnt(refailcnt);
		 }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"���ַ�������� ",1);
 return ack;
}

//���ַ���Ի�ȷ��0x01������0x02
INT8U CEventPublic::   TestMoreEventAckOKNO(INT8U acktype,INT8U CmpType)
{
   INT8U ack = DACK_FAILURE;
   INT8U AmtBuf[7+1];

	INT16U resucnt=0;
	INT16U refailcnt=0;

	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack = gSimJzq. Router_Stop();
 	 gSimMeter.ChangeMeterData_645(0x04001501);
	 MessageBoxDelayTime("������STA�������¼�",30*1000);
	 for(INT8U m=0;m<5;m++)
	 {
      ack = gSimJzq.EventOp(30*1000,50,acktype,DstDecodeDataFrame,AmtBuf,CmpType);
	  StaSucessCnt(ack,resucnt,refailcnt);
	 }
        ack = QueAckFormAckCnt(refailcnt);
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"���ַ���Ի�ȷ��0x01������0x02 ",1);
    return ack;

}


//���ַ����SEQ��0x03,���ظ�0x04
INT8U  CEventPublic::  TestMoreEventNoAckSeqErr(INT8U acktype,INT8U CmpType)
{
   INT8U ack = DACK_FAILURE;


	INT16U resucnt=0;
	INT16U refailcnt=0;
	
	ack = gSimJzq. Router_Stop();
 	 gSimMeter.ChangeMeterData_645(0x04001501);
	 MessageBoxDelayTime("������STA�������¼�",30*1000);
	 for(INT8U m=0;m<5;m++)
	 {
       ack = TestOneEventNoAckSeqErr_Amt(acktype,CmpType);
	   StaSucessCnt(ack,resucnt,refailcnt);
	 }


        ack = QueAckFormAckCnt(refailcnt);
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"���ַ����SEQ��0x03,���ظ�0x04 ",1);
    return ack;

}

//	���ֻظ�����
INT8U  CEventPublic::  TestMoreEventPartNoAck(INT8U CmpType)
{
   INT8U ack = DACK_FAILURE;
  

	INT16U resucnt=0;
	INT16U refailcnt=0;


	ack = gSimJzq. Router_Stop();
//��������
 	 gSimMeter.ChangeMeterData_645(0x04001501);
	 MessageBoxDelayTime("������STA�������¼�",30*1000);
	 for(INT8U m=0;m<5;m++)
	 {
	  if((m+1)%2==0)
       {
		   ack = TestOneEventNoAckSeqErr_Amt(0x03,CmpType);
	       StaSucessCnt(ack,resucnt,refailcnt);
	   }
	  else
	   {
           ack = TestOneEventNoAckSeqErr_Amt(0x01,CmpType);
	       StaSucessCnt(ack,resucnt,refailcnt);

	   }
	 }

	for(INT8U m=0;m<2;m++)
	 {
           ack = TestOneEventNoAckSeqErr_Amt(0x01,CmpType);
	       StaSucessCnt(ack,resucnt,refailcnt);
	 }

//ż������--------------------------------
	 gSimMeter.ChangeMeterData_645(0x04001501);
	 MessageBoxDelayTime("������STA�������¼�",30*1000);
	 for(INT8U m=0;m<5;m++)
	 {
	  if((m+1)%2==0)
       {
		   ack = TestOneEventNoAckSeqErr_Amt(0x01,CmpType);
	       StaSucessCnt(ack,resucnt,refailcnt);
	   }
	  else
	   {
           ack = TestOneEventNoAckSeqErr_Amt(0x03,CmpType);
	       StaSucessCnt(ack,resucnt,refailcnt);

	   }
	 }

	for(INT8U m=0;m<3;m++)
	 {
           ack = TestOneEventNoAckSeqErr_Amt(0x01,CmpType);
	       StaSucessCnt(ack,resucnt,refailcnt);
	 }
	ack=gSimJzq.ZjqNoRcvData(30*1000,50);
	 StaSucessCnt(ack,resucnt,refailcnt);

         ack = QueAckFormAckCnt(refailcnt);
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"���ֻظ�����",1);
    return ack;

}
