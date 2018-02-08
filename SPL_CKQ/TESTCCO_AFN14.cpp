// TESTCCO_AFN14.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTCCO_AFN14.h"

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
extern CLogFile plog;//������

#include "CDTL645.H"
extern CDTL645  gCDtl645Op;

IMPLEMENT_DYNAMIC(CTESTCCO_AFN14, CWnd)

CTESTCCO_AFN14::CTESTCCO_AFN14()
{

}

CTESTCCO_AFN14::~CTESTCCO_AFN14()
{
}


BEGIN_MESSAGE_MAP(CTESTCCO_AFN14, CWnd)
END_MESSAGE_MAP()
void CTESTCCO_AFN14::C3762_TEST(HTREEITEM hTree)
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
	INT8U ack = FALSE;
	INT16U allSucesscnt = 0;
	INT16U allfailcnt = 0;;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	pMainDlg->m_treeProject.Expand(hTree,TVE_EXPAND);//չ�����ڵ�
	HTREEITEM hNextItem = pMainDlg->m_treeProject.GetNextItem(hTree,TVGN_NEXTVISIBLE);
	CString strName;
		   ack = gSimJzq.SetHostAdd();
		   plog.saveLog_testresult(PARS_FILE,TIME,"���ôӽڵ� ",ack,2);
		  

	while (hNextItem)
	{
		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			switch(atol(strName.Mid(0,2)))
			{
			case 1://	����ַʵ�ʱ����
				  {
					    plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
						ack= TestOneAdd(1);
						StaSucessCnt(ack,allSucesscnt,allfailcnt);
						plog.saveLog_testresultAll(TIME,strName ,ack,1);
						plog.saveLog_strAll(TIME,"�������ԣ�"+strName,2);
				  }
				break;
			case 2://���ַ����
				 {
					    plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
						ack= TestMoreAdd(1);
						StaSucessCnt(ack,allSucesscnt,allfailcnt);
						plog.saveLog_testresultAll(TIME,strName ,ack,1);
						plog.saveLog_strAll(TIME,"�������ԣ�"+strName,2);
				  }
				break;
            case 3://	����ַ�޷���
				  {
					    plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
						ack= AFN14OneMeterNoAck();
						StaSucessCnt(ack,allSucesscnt,allfailcnt);
						plog.saveLog_testresultAll(TIME,strName ,ack,1);
						plog.saveLog_strAll(TIME,"�������ԣ�"+strName,2);
				  }
				break;
			case 4://���ַ�޷�
				 {
					    plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
						ack= AFN14MoreMeterNoAck();
						StaSucessCnt(ack,allSucesscnt,allfailcnt);
						plog.saveLog_testresultAll(TIME,strName ,ack,1);
						plog.saveLog_strAll(TIME,"�������ԣ�"+strName,2);
				  }
				break;
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

INT8U  CTESTCCO_AFN14::AFN14OneMeterNoAck(void)
{
	INT8U ack = FALSE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//INT32U tmp32;
	INT32U ackfg=0;
	//dan��ַ��������
	 ack = TestOneAddSetPa();
	 ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
	sNoAckDiMsg  noackMsg;
	gSimMeter.SetSimMeterRunFg(1);//����ģ�������
//��������
	gSimMeter.ClrALLNoAckDi();

	gSimMeter.SetNoAckDi(gReMeterDi[0]);
	for(INT8U m=0;m<5;m++)
	{
		ack = gSimJzq.AFN14F1ACK0001CmpAmt(0,0,0x02);
		StaSucessCnt(ack,resucnt,refailcnt);
		//ģ���յ�3���ط���
		ack=gSimMeter.QueNoDiAckmsg(gReMeterDi[0],noackMsg);
		ack=gSimMeter.CheckNoDiAckmsg(noackMsg);
		plog.saveLog_NoAckMsg(DATA_FILE,TIME,"�������޷���",noackMsg,1);
		StaSucessCnt(ack,resucnt,refailcnt);
		
	}

				 
	  gSimMeter.ClrALLNoAckDi();
	         if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"����ַ�޻ز���",1);
    return ack;

}
INT8U  CTESTCCO_AFN14::AFN14MoreMeterNoAck(void)
{
	INT8U ack = FALSE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//	INT32U tmp32;
	INT32U ackfg=0;
	ack = TesMoreAddSetPa();
	ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
	sNoAckDiMsg  noackMsg;
	gSimMeter.SetSimMeterRunFg(1);//����ģ�������
//��������
	gSimMeter.ClrALLNoAckDi();

	gSimMeter.SetNoAckDi(gReMeterDi[0]);
	for(INT8U m=0;m<5;m++)
	{
		ack = gSimJzq.AFN14F1ACK0001CmpAmt(m,0,0x02);
		StaSucessCnt(ack,resucnt,refailcnt);
		//ģ���յ�3���ط���
		ack=gSimMeter.QueNoDiAckmsg(gReMeterDi[0],noackMsg);
		ack=gSimMeter.CheckNoDiAckmsg(noackMsg);
		StaSucessCnt(ack,resucnt,refailcnt);
		plog.saveLog_NoAckMsg(DATA_FILE,TIME,"�������޷���",noackMsg,1);
		
	}
	  gSimMeter.ClrALLNoAckDi();
	  ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
    for(INT8U m=0;m<5;m++)
		{
			
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			
	  }		
	gSimMeter.ClrALLNoAckDi();

	
	for(INT8U m=0;m<5;m++)
	{
		gSimMeter.SetNoAckDi(gReMeterDi[0]);
		if(m!=2)
		{
          gSimMeter.ClrALLNoAckDi();
		}
		ack = gSimJzq.AFN14F1ACK0001CmpAmt(m,0,0x02);
		StaSucessCnt(ack,resucnt,refailcnt);
	    if(m!=2)
		{
		//ģ���յ�3���ط���
			ack=gSimMeter.QueNoDiAckmsg(gReMeterDi[0],noackMsg);
			ack=gSimMeter.CheckNoDiAckmsg(noackMsg);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
	}

	 gSimMeter.ClrALLNoAckDi();
    for(INT8U m=2;m<3;m++)
		{
			
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			
	  }		 
	  gSimMeter.ClrALLNoAckDi();

		//����ȫ�����
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
		
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"����޻ز���",1);
    return ack;

}
//------------------------------------------------------------------------------
//(һ)	����ַ���ԣ�ʵ�ʡ�ģ�⣩
INT8U CAFN14ReadMeterFun :: TestOneAdd(INT8U CmpType)
{
    INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	//dan��ַ��������
	 ack = TestOneAddSetPa();
	 StaSucessCnt(ack,resucnt,refailcnt);
  //��1�������������
	ack=TestOneAddReadMeter_OK(CmpType);
	StaSucessCnt(ack,resucnt,refailcnt);
	//��1�������ظ����ԡ�ʧ�ܡ��ɹ�������
    ack= TestOneAddReadMeter_Step1Ack(CmpType);
    StaSucessCnt(ack,resucnt,refailcnt);
	//��1���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ
     ack= TestOneAddReadMeter_Step1ErrAck(0,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack= TestOneAddReadMeter_Step1ErrAck(1,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //��3���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ,
     ack= TestOneAddReadMeter_Step3ErrAck(0, CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack= TestOneAddReadMeter_Step3ErrAck(1, CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //��3���쳣�ظ����� �ظ�����֡
     ack= TestOneAddReadMeter_Step3ErrAckNo( CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //����ַ·�ɲ���
       ack= TestOneAddRouter(CmpType);
	   StaSucessCnt(ack,resucnt,refailcnt);
	    if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
	 return ack;
}

//(һ)	MORE��ַ���ԣ�ʵ�ʡ�ģ�⣩
INT8U CAFN14ReadMeterFun :: TestMoreAdd(INT8U CmpType)
{
    INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	//��ַ��������
	 ack = TesMoreAddSetPa();
	 StaSucessCnt(ack,resucnt,refailcnt);
  //��1�������������
	ack=TesMoreAddReadMeter(CmpType);
	StaSucessCnt(ack,resucnt,refailcnt);
	//��1�������ظ����ԡ�ʧ�ܡ��ɹ�������
    ack= TestMoreAddReadMeter_Step1Ack(CmpType);
    StaSucessCnt(ack,resucnt,refailcnt);
	//��1���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ
     ack= TestMoreAddReadMeter_Step1errAck(0,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  ack= TestMoreAddReadMeter_Step1errAck(1,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //��3���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ,
     ack= TestMoreAddReadMeter_Step3ErrAck( CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //��3���쳣�ظ����� �ظ�����֡
     ack= TestMoreAddReadMeter_Step3ErrAckNo( CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //���ַ·�ɲ���
       ack= TestMoreAddRouter(CmpType);
	   StaSucessCnt(ack,resucnt,refailcnt);
	    if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
	 return ack;
}
//dan��ַ��������
INT8U CAFN14ReadMeterFun ::  TestOneAddSetPa(void)
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

//��1�������������
INT8U CAFN14ReadMeterFun ::  TestOneAddReadMeter_OK(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
   //
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07MoreDi(0,5,1,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
		//if(ack==DACK_SUCESS)
		{
		  ack = gSimJzq.AFN14F1ACK0001(0x01);
		  StaSucessCnt(ack,resucnt,refailcnt);
		}
    	//if(ack==DACK_SUCESS)
		{
	    	ack = gSimJzq.ZjqNoRcvData(30,50);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
		//StaSucessCnt(ack,resucnt,refailcnt);
		 
		  if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
	plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1����������",1);	
    return ack;
}
//��1�������ظ����ԡ�ʧ�ܡ��ɹ�������
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step1Ack(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
  //��2����1�Ļظ�����
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.AFN14F1ACK0001(0x00);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}

	    //if(ack==DACK_SUCESS)
		{
			ack=TestOneAddReadMeter_OK(CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
		//StaSucessCnt(ack,resucnt,refailcnt);

         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1�������ظ�����",1);
    return ack;
}

//AMT��1���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ
INT8U  CAFN14ReadMeterFun :: TestAddReadMeter_Step1ErrAck_Amt(INT32U AmtSeq,INT8U vSrcAckType,INT8U ReCnt,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	INT8U no14cnt=0;
	INT8U tmpseq;
	sNoAckDiMsg   AFNnoack;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;

		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07(AmtSeq,gReMeterDi[0],5,CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
		if((ack==DACK_SUCESS))
		{
			  ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
			  StaSucessCnt(ack,resucnt,refailcnt);
		}
		if((ack==DACK_SUCESS))
		{
			ack = DACK_FAILURE;
		  if((DstDecodeDataFrame.s_head.s_AFN==0x014)&&(DstDecodeDataFrame.s_head.s_FN==F1))
			{
				ack = DACK_SUCESS;
				AFNnoack.s_Di=DstDecodeDataFrame.s_head.s_Msg_Seq;
				AFNnoack.s_RcvCnt=1;
				AFNnoack.s_Time[0]=GetSysTimeClk();
				for(INT8U m=0;m<26;m++)
				{
					ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame_2);
					if(ack==DACK_SUCESS)
					{
						ack=gSimJzq.CmpDecode3762(DstDecodeDataFrame,DstDecodeDataFrame_2);
						if(ack==DACK_SUCESS)
						{
						   if(vSrcAckType==1)
						   {
							   tmpseq=DstDecodeDataFrame_2.s_head.s_Msg_Seq;
							   DstDecodeDataFrame_2.s_head.s_Msg_Seq+=3;
							   gSimJzq. SlaveAckAFN14F1(1,&DstDecodeDataFrame.s_RcvDataBuf[1],gReMeterDi[0],DstDecodeDataFrame,sQGDW376_2HostFrame);
							   DstDecodeDataFrame_2.s_head.s_Msg_Seq=tmpseq;
						   }
                           AFNnoack.s_RcvCnt++;
						   if(AFNnoack.s_RcvCnt<=4)
				          {
							  AFNnoack.s_Time[AFNnoack.s_RcvCnt-1]=GetSysTimeClk();
						   }
						}
						else
						{
							break;
						}

					}
				}
		   }
		}
	

		 if(ack==DACK_SUCESS)
	   {
		 ack= gSimJzq.CmpReSendCntTime(AFNnoack,ReCnt,10*1000,15*1000);
	   }
         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
	plog.saveLog_NoAckMsg(DATA_FILE,TIME,"",AFNnoack,1);
  if(vSrcAckType==0)
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1�Ļظ�����--���ظ�",1);
  else
	plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1���쳣�ظ�����---SEQ��",1);
    return ack;
}

//��1���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step1ErrAck(INT8U vSrcAckType,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	INT8U no14cnt=0;
//	INT8U tmpseq;
//	sNoAckDiMsg   AFNnoack;
//	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
//	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2;
//	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
	      ack=TestAddReadMeter_Step1ErrAck_Amt(0,vSrcAckType,3,CmpType);
		  StaSucessCnt(ack,resucnt,refailcnt);
	
			ack=TestOneAddReadMeter_OK(CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }

    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1���쳣�ظ�����",1);
    return ack;
}

//��3���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ,
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step3ErrAck_Amt(INT32U AmtSeq,INT8U vSrcAckType,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	INT8U no14cnt=0;
	INT8U tmpseq;
	sNoAckDiMsg   AFNnoack;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		
		  ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		if((ack==DACK_SUCESS))
		{
			ack = DACK_FAILURE;
		  if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1))
			{
				 ack = gSimJzq.SlaveAckAFN14F1(0x02,&DstDecodeDataFrame.s_RcvDataBuf[1],gReMeterDi[0],DstDecodeDataFrame,sQGDW376_2HostFrame);
		    }
		}

	    if((ack==DACK_SUCESS))
		{
		 ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		}
		  if((ack==DACK_SUCESS))
		   {
			   ack = DACK_FAILURE;
			if(gSimJzq.CmpAFN14F1Data(&gNodeAddBuf[AmtSeq][0],gReMeterDi[0],sQGDW376_2HostFrame,DstDecodeDataFrame)==DACK_SUCESS)
			{
			    AFNnoack.s_Di=DstDecodeDataFrame.s_head.s_Msg_Seq;
				AFNnoack.s_RcvCnt=1;
				AFNnoack.s_Time[0]=GetSysTimeClk();
				for(INT8U m=0;m<26;m++)
				{
					ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame_2);
					if(ack==DACK_SUCESS)
					{
						ack=gSimJzq.CmpDecode3762(DstDecodeDataFrame,DstDecodeDataFrame_2);
						if(ack==DACK_SUCESS)
						{
						   if(vSrcAckType==1)
						   {
							   tmpseq=DstDecodeDataFrame_2.s_head.s_Msg_Seq;
							   DstDecodeDataFrame_2.s_head.s_Msg_Seq+=3;
							   Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						       gSimJzq.SendHost3762ToCom(sQGDW376_2HostFrame);
							   DstDecodeDataFrame_2.s_head.s_Msg_Seq=tmpseq;
						   }
                           AFNnoack.s_RcvCnt++;
						   if(AFNnoack.s_RcvCnt<=4)
				          {
							  AFNnoack.s_Time[AFNnoack.s_RcvCnt-1]=GetSysTimeClk();
						   }
						}
						else
						{
							if(AFNnoack.s_RcvCnt!=3)
							{
								break;
							}
							else if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1))
							{
							   break;
							}
						}
					}
				  }
				}
			  }
		   
		 if(ack==DACK_SUCESS)
	   {
		  ack= gSimJzq.CmpReSendCntTime(AFNnoack,3,10*1000,15*1000);
	   }
		
         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
	 plog.saveLog_NoAckMsg(DATA_FILE,TIME,"",AFNnoack,1);
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1���쳣�ظ�����",1);
    return ack;
}

//��3���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ,
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step3ErrAck(INT8U vSrcAckType,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	INT8U no14cnt=0;
//	INT8U tmpseq;
	//sNoAckDiMsg   AFNnoack;
//	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
//	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2;
//	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
	
		 ack=TestOneAddReadMeter_Step3ErrAck_Amt(0,vSrcAckType,CmpType);
		  StaSucessCnt(ack,resucnt,refailcnt); 
	   if(ack==DACK_SUCESS)
		{
			ack=TestOneAddReadMeter_OK(CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
		 if(ack==DACK_SUCESS)
	   {
		//  ack= gSimJzq.CmpReSendCntTime(AFNnoack,3,10*1000,15*1000);
	   }
		
         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
//	  plog.saveLog_NoAckMsg(DATA_FILE,TIME,"",AFNnoack,1);
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1���쳣�ظ�����",1);
    return ack;
}
//��3���쳣�ظ����� �ظ�����֡
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step3ErrAckNo_Amt(INT32U Amtseq,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		
		  ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		if((ack==DACK_SUCESS))
		{
			ack = DACK_FAILURE;
		  if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1))
			{
				 ack = gSimJzq.SlaveAckAFN14F1(0x02,&DstDecodeDataFrame.s_RcvDataBuf[1],gReMeterDi[0],DstDecodeDataFrame,sQGDW376_2HostFrame);
		    }
		}

	    if((ack==DACK_SUCESS))
		{
		 ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		}
		  if((ack==DACK_SUCESS))
		   {
			   ack = DACK_FAILURE;
			if(gSimJzq.CmpAFN14F1Data(&gNodeAddBuf[0][0],gReMeterDi[0],sQGDW376_2HostFrame,DstDecodeDataFrame)==DACK_SUCESS)
			{
					ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
					if(ack==DACK_SUCESS)
					{
						ack = DACK_FAILURE;
						 if((DstDecodeDataFrame.s_head.s_AFN==0x06)&&(DstDecodeDataFrame.s_head.s_FN==F2))
						{
						     Cgw13762.Code376_2_SlaveFrame(0x00,F2,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						      gSimJzq.SendHost3762ToCom(sQGDW376_2HostFrame);
							 ack=DACK_SUCESS;
						 }
					}          
			}
		  }
		   
		  if((ack==DACK_SUCESS))
		{
		   ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		   StaSucessCnt(ack,resucnt,refailcnt);
		   if((ack==DACK_SUCESS))
			{
				ack = DACK_FAILURE;
			  if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1))
				{
					 ack = DACK_SUCESS;
				}
			}
		}

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
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��3���쳣�ظ�����--�ط���֡",1);
    return ack;
}
//��3���쳣�ظ����� �ظ�����֡
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step3ErrAckNo(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
//	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
	
		ack=TestOneAddReadMeter_Step3ErrAckNo_Amt(0,CmpType);
		StaSucessCnt(ack,resucnt,refailcnt);
	   if(ack==DACK_SUCESS)
		{
			ack=TestOneAddReadMeter_OK(CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
		
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
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1���쳣�ظ�����",1);
    return ack;
}
//����ַ·�ɲ���
INT8U CAFN14ReadMeterFun :: TestOneAddRouter(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;

	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
	    StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.Router_Stop();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.Router_Resume();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.Router_Stop();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
	    StaSucessCnt(ack,resucnt,refailcnt);
		 ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		if((ack==DACK_SUCESS))
		{
			ack = DACK_FAILURE;
		  if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1))
			{
				 ack=DACK_SUCESS;
		    }
		}
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.Router_Stop();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
	    StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq.AFN14F1AllOP(30*1000,50,0x01,DPCT_2007FG,0x00000100);
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
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
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"����ַ·�ɲ���",1);
    return ack;
}

//���ַ��������
INT8U CAFN14ReadMeterFun ::  TesMoreAddSetPa(void)
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
			 if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		 }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"���ַ�������� ",1);
 return ack;
}
  //���DI����������
INT8U  CAFN14ReadMeterFun :: TesMoreAddReadMeter(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
    ack = gSimJzq. Router_Start();
    StaSucessCnt(ack,resucnt,refailcnt);
	ack=gSimJzq.TestReadMeterMoreAdd07(0,5,0,5,CmpType);
	StaSucessCnt(ack,resucnt,refailcnt);
	ack=gSimJzq.ZjqNoRcvData(30*1000,50);
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
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"����ַ·�ɲ���",1);
    return ack;
}

  
//��1�������ظ�����
INT8U  CAFN14ReadMeterFun :: TestMoreAddReadMeter_Step1Ack(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
  //��2����1�Ļظ�����
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//�յ���1-5�Ĳ�1�����λظ�����ʧ�ܣ��л����,2��
	  for(INT8U n=0;n<2;n++)
      {
		  for(INT8U m=0;m<5;m++)
		{
         ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x00,CmpType);
		 StaSucessCnt(ack,resucnt,refailcnt);
		}
	  }
		
      //��1���յ���1-5�Ĳ�1��ż������2�Σ��سɹ�, �����س���2�Σ���ʧ�ܡ�
	  //��2�������س���2�Σ��سɹ���
		  for(INT8U m=0;m<5;m++)
		{
				if((m%2)==0)
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			}
			else
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x00,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);

			}
	 }
		    for(INT8U m=0;m<5;m++)
		  {
		      if((m%2)==0)
			  {
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			  }
	      }

//��1�ֱ�1-5�Ĳ�1����������2�Σ��سɹ�, ż���س���2�Σ���ʧ�ܡ�
 //��2��ż���س���2�Σ��سɹ���
        ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);

		  for(INT8U m=0;m<5;m++)
		{
				if((m%2)==1)
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			}
			else
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x00,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);

			}
	 }
		    for(INT8U m=0;m<5;m++)
		  {
		       if((m%2)==0)
			   {
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			  }
	      }

		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
   //��1�ֳ���2��,���һ���ʧ�ܡ�
   //��2�����һ�鳭��2��,�سɹ���
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		  for(INT8U m=0;m<5;m++)
		{
			
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);

			   if(m==4)
				 {
					 ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x00,CmpType);
			   }
			   else
				{
					ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			   }
				StaSucessCnt(ack,resucnt,refailcnt);
			
	 }
       for(INT8U m=0;m<2;m++)
		{
          ack = gSimJzq.AFN14F1AllOPCmpAmt(4,gReMeterDi[0],1,0x02,CmpType);
		  StaSucessCnt(ack,resucnt,refailcnt);
	   }
	   ack = gSimJzq.AFN14F1AllOPCmpAmt(5,gReMeterDi[1],1,0x01,CmpType);
	    StaSucessCnt(ack,resucnt,refailcnt);
		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
//----------------------------------------------------------------------------

         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1�������ظ�����",1);
    return ack;
}

//��1���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ
INT8U  CAFN14ReadMeterFun :: TestMoreAddReadMeter_Step1errAck(INT8U Acktype,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
  //��2����1�Ļظ�����
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//�յ���1-5�Ĳ�1�����λظ�SEQ��һ�£��л����,2��
	 
		  for(INT8U m=0;m<5;m++)
		{
			 ack = TestAddReadMeter_Step1ErrAck_Amt(m,Acktype,3,CmpType);
			 StaSucessCnt(ack,resucnt,refailcnt);
		}
	
		
      //��1���յ���1-5�Ĳ�1��ż������2�Σ��سɹ�, �����س���2�Σ���ʧ�ܡ�
	  //��2�������س���2�Σ��سɹ���
		  for(INT8U m=0;m<5;m++)
		{
				if((m%2)==0)
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			}
			else
			{
				 ack = TestAddReadMeter_Step1ErrAck_Amt(m,Acktype,3,CmpType);
			     StaSucessCnt(ack,resucnt,refailcnt);

			}
	 }
		    for(INT8U m=0;m<5;m++)
		  {
		      if((m%2)==0)
			  {
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			  }
	      }

//��1�ֱ�1-5�Ĳ�1����������2�Σ��سɹ�, ż���س���2�Σ���ʧ�ܡ�
 //��2��ż���س���2�Σ��سɹ���
        ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);

		  for(INT8U m=0;m<5;m++)
		{
				if((m%2)==1)
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			}
			else
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				 ack = TestAddReadMeter_Step1ErrAck_Amt(m,Acktype,3,CmpType);
			     StaSucessCnt(ack,resucnt,refailcnt);
		

			}
	 }
		    for(INT8U m=0;m<5;m++)
		  {
		       if((m%2)==0)
			   {
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			  }
	      }

		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
   //��1�ֳ���2��,���һ���ʧ�ܡ�
   //��2�����һ�鳭��2��,�سɹ���
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		  for(INT8U m=0;m<5;m++)
		{
			
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);

			   if(m==4)
				 {
					 ack = TestAddReadMeter_Step1ErrAck_Amt(m,Acktype,3,CmpType);
			    }
			   else
				{
					ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			   }
				StaSucessCnt(ack,resucnt,refailcnt);
			
	 }
       for(INT8U m=0;m<2;m++)
		{
          ack = gSimJzq.AFN14F1AllOPCmpAmt(4,gReMeterDi[0],1,0x02,CmpType);
		  StaSucessCnt(ack,resucnt,refailcnt);
	   }
	   ack = gSimJzq.AFN14F1AllOPCmpAmt(5,gReMeterDi[1],1,0x01,CmpType);
	    StaSucessCnt(ack,resucnt,refailcnt);
		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
//----------------------------------------------------------------------------

         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1���쳣�ظ�����",1);
    return ack;
}

//��3�쳣�ظ�SEQ�����ظ�����
INT8U  CAFN14ReadMeterFun :: TestMoreAddReadMeter_Step3ErrAck(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
  //��2����3�Ļظ�����
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//�յ�����������SEQ����
	     for(INT8U m=0;m<5;m++)
		{
         ack = TestOneAddReadMeter_Step3ErrAck_Amt(0,0,CmpType);
		 StaSucessCnt(ack,resucnt,refailcnt);
		}
        //�յ���������������
		  for(INT8U m=0;m<5;m++)
		{
         ack = TestOneAddReadMeter_Step3ErrAck_Amt(0,1,CmpType);
		 StaSucessCnt(ack,resucnt,refailcnt);
		}
		  //�յ���1-5��һ�Σ�������SEQ����һ�λ���ȷ���ݣ�һ�λس���ɹ�
		    for(INT8U m=0;m<5;m++)
		{
          ack = TestOneAddReadMeter_Step3ErrAck_Amt(m,0,CmpType);
		 StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
	    ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
  //�յ���1-5��һ�Σ��������أ�һ�λ���ȷ���ݣ�һ�λس���ɹ�
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
         for(INT8U m=0;m<5;m++)
		{
			 ack = TestOneAddReadMeter_Step3ErrAck_Amt(m,1,CmpType);
		 StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		 }
		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);


		//1-5��������
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
         for(INT8U m=0;m<5;m++)
		{
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		 }
		  ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
//----------------------------------------------------------------------------

         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��3�쳣�ظ�SEQ�����ظ�����",1);
    return ack;
}

//��3�쳣�ط��ϲ���
INT8U  CAFN14ReadMeterFun :: TestMoreAddReadMeter_Step3ErrAckNo(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//�յ���1-5�Ĳ�1�����λظ����ϣ���������ɹ�

	     for(INT8U m=0;m<5;m++)
		{
         ack = TestOneAddReadMeter_Step3ErrAckNo_Amt(m,CmpType);
		 	StaSucessCnt(ack,resucnt,refailcnt);
		  ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		 StaSucessCnt(ack,resucnt,refailcnt);
		}
		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
//----------------------------------------------------------------------------
         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"��1�������ظ�����",1);
    return ack;
}
//More��ַ·�ɲ���
INT8U CAFN14ReadMeterFun :: TestMoreAddRouter(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//	   sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	   //����·�ɣ�ǰ1-3�鳭��
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		for(INT8U m=0;m<3;m++)
		{
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		    ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
		//��ͣ·��
			ack=gSimJzq.Router_Stop();
         ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
		//����·�ɣ�ǰ1-3�鳭��
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		for(INT8U m=0;m<3;m++)
		{
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		    ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
		//��ͣ·��
		ack=gSimJzq.Router_Stop();
        ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);

      //�ָ�·�ɣ�4-5�鳭��
		ack=gSimJzq.Router_Resume();
		StaSucessCnt(ack,resucnt,refailcnt);

		for(INT8U m=3;m<5;m++)
		{
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		    ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
       //����ȫ�����
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);


		//�ָ�·�ɣ��ޱ�����
		ack=gSimJzq.Router_Resume();
		StaSucessCnt(ack,resucnt,refailcnt);

		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);

		//����·�ɣ�ǰ1-5�鳭��
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		for(INT8U m=0;m<5;m++)
		{
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		    ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
		//����ȫ�����
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
		
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"����ַ·�ɲ���",1);
    return ack;
}

