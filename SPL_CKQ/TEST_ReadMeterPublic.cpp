// TEST_SimpleChaoB.cpp : implementation file
//

#include "stdafx.h"
#include "KD_Project.h"
#include "TEST_ReadMeterPublic.h"
#include "MainFrm.h"

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


void CTEST_ReadMeterPublic:: StaSucessCnt(INT8U ack,INT8U &allSucesscnt,INT8U &failCnt)
{
	if(ack == DACK_SUCESS)
	{
		allSucesscnt++;
	}
	else
	{
       failCnt++;
	}
}
INT8U  CTEST_ReadMeterPublic::TestSetPa(void)
{          
	 INT8U ack;
	 	INT8U allSucesscnt = 0;
	INT8U allfailcnt = 0;;
			//1.	����CCO�����ڵ��ַ
			sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
			sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
			plog.saveLog_strAll(TIME,_T("��ʼ���������ڵ�"),1);
			ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,m_HostNodeAddress,6);
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
			ack =gSimJzq.HostSendRcv376_2NoBuf(AFN03,F4,sQGDW376_2HostFrame,DstDecodeDataFrame);//��ȡ���ڵ�
			if (ack == DACK_SUCESS)
			{
				plog.saveLog_strAll(TIME,_T("�������ڵ������ɹ�"),1);
			}
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
			//2.	ɾ��CCO��ǰ�ӽڵ㡣
             
			ack = gSimJzq.Router_PaRst();
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
			if(ack == DACK_SUCESS)
			{
				plog.saveLog_str(DATA_FILE,NOTIME,_T("�ȴ�20��"),0);
				Sleep(20000);//��ʼ���ɹ������ʱ20����µĴӽڵ������ӳɹ�
			}
				
			//3.	���CCO�Ĵӽڵ㣨��ģ�����ַһ�£���
			plog.saveLog_strAll(TIME,_T("��ʼ�����CCO�ӽڵ�"),1);	
			ack = gSimJzq.SetNodeAdd(0,1);
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
			if(ack == DACK_SUCESS)
			{
			   ack = gSimJzq.CmpNodeAdd(0,1);
			   StaSucessCnt(ack,allSucesscnt,allfailcnt);
			}
			plog.saveLog_strAll(TIME,_T("��ʼ��·����ͣ����"),1);	 
			ack = gSimJzq.Router_Stop();
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
		
			ack = gSimJzq.QueAllNetSta(0,1,5*60);//��������������ڴ����
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
	       if(allfailcnt==0)
			    ack = DACK_SUCESS;
		   else
			   ack = DACK_FAILURE;

			plog.saveLog_testresultAll(TIME,_T("�������ý���� "),ack,1);
	
			return ack;
}
//	���ת�����ԣ�ʵ�ʱ���ģ���
INT8U  CTEST_ReadMeterPublic::TestReadMeterCnt(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType)
{
	INT8U ack;
	INT32U resucnt=0;
	INT32U failcnt=0;
	sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sAckTimeSta  ackclkSta;
	for(INT32U m=0;m<vSrcCnt;m++)
	{
		 ack = gSimJzq.ReadMeterAndCmpMterAckClk(vSrcAfntype,&gNodeAddBuf[0][0],gReMeterDi[0],sQGDW376_2HostFrame,DstDecodeDataFrame,ackclkSta,vSrcMeterType);
	
		 if(ack==DACK_SUCESS)
		 {
               resucnt++;
		 }
		 else
		 {
			 failcnt++;
		 }
	}

	if(failcnt == 0)
	{
        ack = DACK_SUCESS;
	}
	else
	{
		 ack = DACK_FAILURE;
	}
	plog.saveLog_StaCnt(resucnt,failcnt,DATA_FILE,TIME,_T("���ת������"),1);
	return ack;
}

//	����DI���ԣ�ʵ�ʱ���ģ���
INT8U  CTEST_ReadMeterPublic::TestReadMeterErrDi(INT32U vSrcCnt,INT8U vSrcAfntype)
{
	INT8U ack;
	INT32U resucnt=0;
	INT32U failcnt=0;
	sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sAckTimeSta  ackclkSta;
	for(INT32U m=0;m<vSrcCnt;m++)
	{
		 ack = gSimJzq.Read3762MeterAckClk(vSrcAfntype,&gNodeAddBuf[0][0],0x99998877,sQGDW376_2HostFrame,DstDecodeDataFrame,ackclkSta);
	
		 if(ack==DACK_SUCESS)
		 {
               resucnt++;
		 }
		 else
		 {
			 failcnt++;
		 }
	}

	if(failcnt == 0)
	{
        ack = DACK_SUCESS;
	}
	else
	{
		 ack = DACK_FAILURE;
	}
	plog.saveLog_StaCnt(resucnt,failcnt,DATA_FILE,TIME,_T("���ת������"),1);
	return ack;
}
//������֡���ԣ��м��޽��գ���ʵ�ʱ���ģ���
INT8U CTEST_ReadMeterPublic::TestMoreReadMeterNoRcv(INT8U Type)
{
		INT16U noack=0;
		INT16U  errack=0;
		INT16U  okack=0;
		INT8U ack;
		INT8U reack = DACK_SUCESS;
		//INT8U tmpack;
		INT16U dataerrack=0;				     
		gSimMeter.ClrSimMeterComData();
		sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		Stu_Dtl2007 DstDecode2007DataFrame;
		INT8U seqbuf[100];
		INT8U sucfgbuf[100];
		BufIs0(sucfgbuf,100);
		INT8U readcnt =17;
		for(INT8U m=0; m<readcnt;m++)
		{
			gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame);
			gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
			seqbuf[m] = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
		}
		for(INT16U m=0; m<readcnt;m++)
		{
			ack = gSimJzq.Wait3762Ack(10000,100,DstDecodeDataFrame);
			if((ack == DACK_SUCESS))
			{                    
				if((DstDecodeDataFrame.s_head.s_AFN == sQGDW376_2HostFrame.s_head.s_AFN) && (DstDecodeDataFrame.s_head.s_FN == sQGDW376_2HostFrame.s_head.s_FN))
				{ 
					ack = Decode2007(DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,DstDecode2007DataFrame);
					if(ack == DACK_SUCESS)
					{
						for(INT16U n=0;n < readcnt; n++)
						{
							if(seqbuf[n]==DstDecodeDataFrame.s_head.s_Msg_Seq)
							{
								if((DstDecode2007DataFrame.s_Di ==gReMeterDi[0]))
								{
									sucfgbuf[n]=0x01;	  
								}
								else
								{
									sucfgbuf[n]=0x03;
								}
								break;
							}
						}
					}
				}
				else  if( (DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN == F2))
				{
					for(INT16U n=0;n < readcnt; n++)
					{
						if(seqbuf[n] == DstDecodeDataFrame.s_head.s_Msg_Seq)
						{
							sucfgbuf[n]=0x02;
							break;
						}
					}
				}					 
			}
		}
						
	//�ȽϽ�� 
		for(INT16U n=0;n < readcnt; n++)
		{
			if(sucfgbuf[n] == 0x01)
			{
				okack++;
			}
			else if(sucfgbuf[n] == 0x02)
			{
				errack++;
			}
			else if(sucfgbuf[n] == 0x03)
			{
				dataerrack++;
			}
			else
			{
				noack++;
			}
		}
		plog.saveLog_StaBuf8(sucfgbuf,readcnt,DATA_FILE,TIME,_T("��֡���ԣ������м��޽���"));
		if((okack+errack == readcnt) && (okack >= 13))
		{

			plog.saveLog_testresult(DATA_FILE,TIME,_T("��֡���ԣ������м��޽���"),DACK_SUCESS,1);

		}
		else
		{
			plog.saveLog_testresult(DATA_FILE,TIME,_T("��֡���ԣ������м��޽���"),DACK_FAILURE,1);
			reack = DACK_FAILURE;
		}
		gSimMeter.ClrSimMeterComData();
		return reack;
}
//��֡���ԣ��м�Ҫ���գ���ʵ�ʱ���ģ���
INT8U CTEST_ReadMeterPublic::TestMoreReadMeterRcv(INT8U Type)
{

		INT16U noack=0;
		INT16U  errack=0;
		INT16U  okack=0;
		INT8U ack;
		INT8U reack = DACK_SUCESS;
		//INT8U tmpack;
		INT16U dataerrack;
		gSimMeter.ClrSimMeterComData();
		sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		Stu_Dtl2007 DstDecode2007DataFrame;
		INT8U seqbuf[100+2];
		INT8U sucfgbuf[100+2];
		BufIs0(sucfgbuf,100);
		INT8U readcnt =100;
		INT8U m=0;
		for( m=0; m<readcnt;m++)
		{
			gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame);
			gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen);
			seqbuf[m] = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
			ack = gSimJzq.Wait3762Ack(0,100,DstDecodeDataFrame);
			if(ack == DACK_SUCESS)
			{
				if((DstDecodeDataFrame.s_head.s_AFN == sQGDW376_2HostFrame.s_head.s_AFN) && (DstDecodeDataFrame.s_head.s_FN == sQGDW376_2HostFrame.s_head.s_FN))
				{ 
					ack = Decode2007(DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,DstDecode2007DataFrame);

					if(ack == DACK_SUCESS)
					{
						for(INT16U n=0;n <= m; n++)
						{
							if(seqbuf[n]==DstDecodeDataFrame.s_head.s_Msg_Seq)
							{
								if((DstDecode2007DataFrame.s_Di ==gReMeterDi[0]))
								{
									sucfgbuf[n]=0x01;

								}
								else
								{
									sucfgbuf[n]=0x03;
								}
								break;
							}
						}

					}
				}
				else  if( (DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN == F2))
				{
					for(INT16U n=0;n <= m; n++)
					{
						if(seqbuf[n] == DstDecodeDataFrame.s_head.s_Msg_Seq)
						{
							sucfgbuf[n]=0x02;
							break;
						}
					}
				}

			}
		}
					//------------------------
		for( m=0; m<readcnt;m++)
		{
			if( sucfgbuf[m]==0)
			{
				ack = gSimJzq.Wait3762Ack(10000,100,DstDecodeDataFrame);
				if((ack == DACK_SUCESS))
				{
					if((DstDecodeDataFrame.s_head.s_AFN == sQGDW376_2HostFrame.s_head.s_AFN) && (DstDecodeDataFrame.s_head.s_FN == sQGDW376_2HostFrame.s_head.s_FN))
					{ 
						ack = Decode2007(DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,DstDecode2007DataFrame);

						if(ack == DACK_SUCESS)
						{
							for(INT16U n=0;n < readcnt; n++)
							{
								if(seqbuf[n]==DstDecodeDataFrame.s_head.s_Msg_Seq)
								{
									if((DstDecode2007DataFrame.s_Di ==gReMeterDi[0]))
									{
										sucfgbuf[n]=0x01;

									}
									else
									{
										sucfgbuf[n]=0x03;
									}
									break;
								}
							}

						}
					}
					else  if( (DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN == F2))
					{
						for(INT16U n=0;n < readcnt; n++)
						{
							if(seqbuf[n] == DstDecodeDataFrame.s_head.s_Msg_Seq)
							{
								sucfgbuf[n]=0x02;
								break;
							}
						}
					}
				}

			}
		}
    //�ȽϽ�� 
		for(INT16U n=0;n < readcnt; n++)
		{
			if(sucfgbuf[n] == 0x01)
			{
				okack++;
			}
			else if(sucfgbuf[n] == 0x02)
			{
                errack++;
			}
			else if(sucfgbuf[n] == 0x03)
			{
                dataerrack++;
			}
			else
			{
				noack++;
			}


		}
		plog.saveLog_StaBuf8(sucfgbuf,readcnt,DATA_FILE,TIME,"��֡���ԣ������м��н���");
		if((okack+errack == readcnt) && (okack >= 50))
		{

			plog.saveLog_testresult(DATA_FILE,TIME,"��֡���ԣ������м��н���",DACK_SUCESS,1);

		}
		else
		{
			plog.saveLog_testresult(DATA_FILE,TIME,"��֡���ԣ������м��н���",DACK_FAILURE,1);
			reack = DACK_FAILURE;
		}
		gSimMeter.ClrSimMeterComData();
		return reack;

}
INT8U  CTEST_ReadMeterPublic::TestReadMeterLongFame(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType)
{
	INT8U ack;
	INT32U resucnt=0;
	INT32U failcnt=0;
	sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sAckTimeSta  ackclkSta;
	for(INT32U m=0;m<vSrcCnt;m++)
	{
		 ack = gSimJzq.ReadMeterAndCmpMterAckClk(vSrcAfntype,&gNodeAddBuf[0][0],0x19010001,sQGDW376_2HostFrame,DstDecodeDataFrame,ackclkSta,vSrcMeterType);
	
		 if(ack==DACK_SUCESS)
		 {
               resucnt++;
		 }
		 else
		 {
			 failcnt++;
		 }
	}

	if(failcnt == 0)
	{
        ack = DACK_SUCESS;
	}
	else
	{
		 ack = DACK_FAILURE;
	}
	plog.saveLog_StaCnt(resucnt,failcnt,DATA_FILE,TIME,"���ת������",1);
	return ack;
}
//	����δ�ɹ�����ʵ�ʱ���ģ���
INT8U  CTEST_ReadMeterPublic::TestSeqNONet(INT32U vSrcCnt,INT8U Type)
{

	
		INT8U resucnt=0;
		INT8U ack;
		sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		INT32U succnt=0;
		INT32U failcnt=0;
		resucnt = 0; 
		//�鿴�·���SEQ��ظ���SEQһ�£��Ҵ������Ϊ0x0c���ӽڵ㲻��������
		for(INT32U m = 0; m<vSrcCnt; m++)
		{
		    ack = gSimJzq.Read3762Meter(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame,DstDecodeDataFrame);
			if((ack == DACK_SUCESS)&&(DstDecodeDataFrame.s_head.s_AFN==0x00)&&(DstDecodeDataFrame.s_head.s_FN==F2)&&(DstDecodeDataFrame.s_RcvDataLen==1)&&(DstDecodeDataFrame.s_RcvDataBuf[0]==0x0C))
			{
			    succnt++;
			}
			else
			{
			    failcnt++;
			}
		}
		plog.saveLog_StaCnt(resucnt,failcnt,DATA_FILE,TIME,"�Ӳ���-����������",1);
		if(failcnt==0)
		{
			  ack = DACK_SUCESS;
		}
		else
		{
			 ack = DACK_FAILURE;
			
		}
				
		return 	ack;
}
INT8U  CTEST_ReadMeterPublic::TestSeqNOAck645Di(INT8U Type)
{

	 gSimMeter.SetSimMeterRunFg(0);
	 gSimMeter.ClrSimMeterComData();
		INT8U resucnt=0;
		INT8U ack;
		sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		INT16U succnt=0;
		INT16U failcnt=0;
		resucnt = 0; 
		//�鿴�·���SEQ��ظ���SEQһ�£��Ҵ������Ϊ0x00������޷��أ���
		for(INT8U m = 0; m<1; m++)
		{
		    ack = gSimJzq.Read3762Meter(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame,DstDecodeDataFrame);
			if((ack == DACK_SUCESS)&&(DstDecodeDataFrame.s_head.s_AFN==0x00)&&(DstDecodeDataFrame.s_head.s_FN==F2)&&(DstDecodeDataFrame.s_RcvDataLen==1)&&(DstDecodeDataFrame.s_RcvDataBuf[0]==0x00))
			{
			    succnt++;
			}
			else
			{
			    failcnt++;
			}
		}
		plog.saveLog_StaCnt(resucnt,failcnt,PARS_FILE,TIME,"�Ӳ���--�������ݷ���",1);
		if(failcnt==0)
		{
			if( Type == 0)
			   plog.saveLog_testresult_AfnFn(0x02,F1,PARS_FILE,TIME,"",DACK_SUCESS,1);
			else
			    plog.saveLog_testresult_AfnFn(0x13,F1,PARS_FILE,TIME,"",DACK_SUCESS,1); 
		}
		else
		{
			if( Type == 0)
		    	plog.saveLog_testresult_AfnFn(0x02,F1,PARS_FILE,TIME,"",DACK_FAILURE,1);
			else
			   plog.saveLog_testresult_AfnFn(0x13,F1,PARS_FILE,TIME,"",DACK_FAILURE,1);
		}
				
		gSimMeter.ClrSimMeterComData();
		gSimMeter.SetSimMeterRunFg(1);
		return 	ack;
}
//�ظ�DI��һ�����ݣ�ģ���
INT8U  CTEST_ReadMeterPublic::TestSeqAck645ErrDi(INT32U vSrcCnt,INT8U Type)
{
		INT32U succnt=0;
		INT32U failcnt=0;
		INT8U ack;
		INT8U reack = DACK_SUCESS;
		gSimMeter.SetSimMeterRunFg(0);
		gSimMeter.ClrSimMeterComData();
		sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		Stu_Dtl2007 DstDecode2007DataFrame;
		for(INT32U m = 0; m<vSrcCnt; m++)
		{
			ack = gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame);
			if(ack == DACK_SUCESS)
			{
				gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
				ack = gSimMeter. Wait645ack(6000,100,DstDecode2007DataFrame);
				if(ack == DACK_SUCESS)
				{
					 ack= DACK_EER_645DATA;
					if(DstDecode2007DataFrame.s_Di ==gReMeterDi[0] )
					{
						DstDecode2007DataFrame.s_Di =gReMeterDi[1];
						gSimMeter. SendMeterData_645(DstDecode2007DataFrame);
						if( Type == 0)
						{
							ack = gSimJzq.WaitReadMeterAFN02F1AckAndCmp(10000,100,gReMeterDi[1],sQGDW376_2HostFrame,DstDecodeDataFrame);
						}
						else
						{
							ack = gSimJzq.WaitReadMeterAFN13F1AckAndCmp(10000,100,gReMeterDi[1],sQGDW376_2HostFrame,DstDecodeDataFrame);
						}
					}
				}
	  		}
		}
		plog.saveLog_StaCnt(succnt,failcnt,PARS_FILE,TIME,"�ظ�DI��һ������",1);
		if(failcnt==0)
		{
			  ack = DACK_SUCESS;
		}
		else
		{
			 ack = DACK_FAILURE;
			
		}
		
		plog.saveLog_testresult(PARS_FILE,TIME,"�ظ�DI��һ������ ",ack,1);
		
		gSimMeter.ClrSimMeterComData();
		gSimMeter.SetSimMeterRunFg(1);

   return 		ack;
}
//	���ֻظ����ԡ���ģ���
INT8U CTEST_ReadMeterPublic::TestPartAckNo(INT8U Type)
{
	         INT8U resucnt=0;
	           INT8U  refailcnt=0;
			   INT8U ack;
			   INT8U reack = DACK_SUCESS;
			   INT8U tmpack;
				        gSimMeter.SetSimMeterRunFg(0);
					    gSimMeter.ClrSimMeterComData();
				      sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
					  sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
					  Stu_Dtl2007 DstDecode2007DataFrame;
					
					  for(INT8U m=0; m<8;m++)
				    {
						 gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[m], sQGDW376_2HostFrame);
						gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
					}
					    for(INT8U m=0; m<8;m++)
				       {
					      ack = gSimMeter. Wait645ack(6000,100,DstDecode2007DataFrame);
						   if((ack == DACK_SUCESS)&&(DstDecode2007DataFrame.s_Di ==gReMeterDi[m] ))
						   {
							 if((m<3)||(m>4))
                              {
								  gSimMeter. SendMeterData_645(DstDecode2007DataFrame);
							  }
						   }
						}
                       
						for(INT8U m=0; m<8;m++)
				       {
						 ack = gSimJzq.Wait3762Ack(10000,100,DstDecodeDataFrame);
						 if((ack == DACK_SUCESS))
						 {
                           if((m<3)||(m>4))
						   {
							  if(( DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN == F2))
							  {
								  resucnt++;
							  }
							  else
							  {
								  refailcnt++;
							  }
						    }
						   else
						   {
							   tmpack = DACK_FAILURE;
							    if((Type==0)&&( DstDecodeDataFrame.s_head.s_AFN ==0x02)&&(DstDecodeDataFrame.s_head.s_FN == F1))
								{ 
								     tmpack = DACK_SUCESS;
								}
								else  if((Type==1)&&( DstDecodeDataFrame.s_head.s_AFN ==0x13)&&(DstDecodeDataFrame.s_head.s_FN == F1))
								{
								   tmpack = DACK_SUCESS;
								}
			                  if( tmpack == DACK_SUCESS)
							  {
								  ack = Decode2007(DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,DstDecode2007DataFrame);
								  if((ack == DACK_SUCESS)&&(DstDecode2007DataFrame.s_Di ==gReMeterDi[m]))
								 {
									 resucnt++;
								  }
								  else
								  {
									refailcnt++;
									}
							  }
							  
						   }
						 }
					   }

						if((resucnt==6)&&(refailcnt==2))
					 {
						
					     //plog.saveLog_testresult(PARS_FILE,TIME,"���ֳɹ�����֡����",DACK_SUCESS,1);
						
					 }
					else
					{
					    // plog.saveLog_testresult(PARS_FILE,TIME,"���ֳɹ�����֡����",DACK_FAILURE,1);
						  reack = DACK_FAILURE;
					}
				     gSimMeter.ClrSimMeterComData();
					 gSimMeter.SetSimMeterRunFg(1);
		return reack;
}
//�ط����������ʱ�����
//  Type  0: 02, 1:   13:
INT8U CTEST_ReadMeterPublic::TestIntevalTime(INT8U Type)
{
			   INT8U resucnt=0;
	           INT8U  refailcnt=0;
			   INT8U ack;
			   INT8U reack = DACK_SUCESS;
				        gSimMeter.SetSimMeterRunFg(0);
					    gSimMeter.ClrSimMeterComData();
				      sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
					  sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
					  Stu_Dtl2007 DstDecode2007DataFrame;
					  INT32U timeclk376Rcvbuf[100+2];
					  INT32U timeclk645Rcvbuf[100+2];
					  INT32U tmpstartclk;
					  INT8U readcnt=100;
						for(INT8U m=0; m<readcnt;m++)
						{
							timeclk376Rcvbuf[m]=0xFFFFFFFF;
							timeclk645Rcvbuf[m]=0xFFFFFFFF;
							 tmpstartclk = GetSysTimeClk();

                            gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame);
					
							gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
							ack = gSimMeter. Wait645ack(6000,100,DstDecode2007DataFrame);
							if((ack == DACK_SUCESS)&&(DstDecode2007DataFrame.s_Di ==gReMeterDi[0] ))
							{
								timeclk645Rcvbuf[m]=GetSysTimeInterval(tmpstartclk);
								gSimMeter. SendMeterData_645(DstDecode2007DataFrame);
								ack = gSimJzq.Wait3762Ack(10000,100,DstDecodeDataFrame);
								if((ack == DACK_SUCESS))
								{
									if((Type==0)&&( DstDecodeDataFrame.s_head.s_AFN ==0x02)&&(DstDecodeDataFrame.s_head.s_FN == F1))
									 {
										 timeclk376Rcvbuf[m]=GetSysTimeInterval(tmpstartclk);
									 }
									else if((Type==1)&&( DstDecodeDataFrame.s_head.s_AFN ==0x13)&&(DstDecodeDataFrame.s_head.s_FN == F1))
									 {
										 timeclk376Rcvbuf[m]=GetSysTimeInterval(tmpstartclk);
									 }
								}
							}
						}
                      //�жϺϸ�
					    for(INT8U m=0; m<readcnt;m++)
						{
							if((timeclk376Rcvbuf[m] < 500) && (timeclk645Rcvbuf[m] < 100))
							{
								resucnt++;
							}
							else
							{
								refailcnt++;
							}
					    }
					//��ӡ���ʱ�䣺

                         plog.saveLog_StaBuf32(timeclk376Rcvbuf,readcnt,PARS_FILE,TIME,"���ʱ����ԣ��з���--3762ʱ��");
						 plog.saveLog_StaBuf32(timeclk645Rcvbuf,readcnt,PARS_FILE,TIME,"���ʱ����ԣ��з���--645ʱ��");
                     // -------------------
						if(refailcnt>0) 
					 {
						
					     plog.saveLog_testresult(PARS_FILE,TIME,"----�Ӳ���-�� ���ʱ�����-�������ݷ���",DACK_SUCESS,1);
					 }
					else
					{
    
					     plog.saveLog_testresult(PARS_FILE,TIME,"----�Ӳ���-�����ʱ�����-�������ݷ���",DACK_FAILURE,1);
						 reack = DACK_FAILURE;
					}

                //-------------���������ݷ�������-----------------------------
						readcnt=3;
                         for(INT8U m=0; m<readcnt;m++)
						{
							timeclk376Rcvbuf[m]=0xFFFFFFFF;
							timeclk645Rcvbuf[m]=0xFFFFFFFF;
							 tmpstartclk = GetSysTimeClk();
							 gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame);
							gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
							ack = gSimMeter. Wait645ack(6000,100,DstDecode2007DataFrame);
							if((ack == DACK_SUCESS)&&(DstDecode2007DataFrame.s_Di ==gReMeterDi[0] ))
							{
								timeclk645Rcvbuf[m]=GetSysTimeInterval(tmpstartclk);
							    //gSimMeter. SendMeterData_645(DstDecode2007DataFrame);
								ack = gSimJzq.Wait3762Ack(20*1000,100,DstDecodeDataFrame);
								if((ack == DACK_SUCESS)&&( DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN == F2))
								{
									timeclk376Rcvbuf[m]=GetSysTimeInterval(tmpstartclk);
								}
							}
						}
                      //�жϺϸ�
					    for(INT8U m=0; m<readcnt;m++)
						{
							if((timeclk376Rcvbuf[m] >90*1000) &&(timeclk376Rcvbuf[m] < 150*1000) && (timeclk645Rcvbuf[m] < 100))
							{
								resucnt++;
							}
							else
							{
								refailcnt++;
							}
					    }
					//��ӡ���ʱ�䣺

                        plog.saveLog_StaBuf32(timeclk376Rcvbuf,readcnt,PARS_FILE,TIME,"���ʱ����� �޷���--3762ʱ��");
						 plog.saveLog_StaBuf32(timeclk645Rcvbuf,readcnt,PARS_FILE,TIME,"���ʱ����� �޷���--645ʱ��");
						
                     // -------------------
						if(refailcnt>0) 
					 {
						
					     plog.saveLog_testresult(PARS_FILE,TIME,"�Ӳ���-�� ���ʱ�����-�������ݷ���",DACK_SUCESS,1);
					 }
					else
					{
     
					      plog.saveLog_testresult(PARS_FILE,TIME,"�Ӳ���-�����ʱ�����-�������ݷ���",DACK_FAILURE,1);
						  reack = DACK_FAILURE;
					}



				    gSimMeter.ClrSimMeterComData();
					 gSimMeter.SetSimMeterRunFg(1);
					 return reack;
}




