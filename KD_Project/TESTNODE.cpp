// TESTNODE.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTNODE.h"
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


IMPLEMENT_DYNAMIC(CTESTNODE, CWnd)

CTESTNODE::CTESTNODE()
{

}

CTESTNODE::~CTESTNODE()
{
}


BEGIN_MESSAGE_MAP(CTESTNODE, CWnd)
END_MESSAGE_MAP()



// CTESTNODE message handlers

UINT8 NODE_RAMACKLIST[2048][6];//����ӵĴӽڵ��ַ�б�
UINT8 NODE_READDELLIST[2048][6];//�����ɾ��������Ĵӽڵ��ַ�б�
UINT8 FALSH_ACKNODELIST[2048][6];//��FLASH��Ĵӽڵ��ַ�б�
BYTE m_add_nod_num;
//����Ԥ��ÿ�����ӵĽڵ���
CString m_start_nod_addr;
UINT64 m_l64AutoTestAddrCounter;//��ʼ��ַ����ʼҲ��ʵ��д���ַ�������ۼӣ���ǰֵΪһЩ���ַ+1��64bit�ĵ�ַ������ʽ
BYTE m_protocol_type;
BYTE m_nodNumPerframe_Set;
//�趨��ÿ֡�ڵ�����
BYTE gB_nodNumThisFrame;//��ǰ����֡�Ľڵ�����

ST_ADD_DEL_NOD_TEST stADelNodTest;
#define READ_SN_BEGIN 1
#define RESEND_CHANCE_TIMES 2
#define ADD_NODE_NUM_MAX 200

#define FLASH_START_ADDR 0x2000

void CTESTNODE::C3762_TEST(HTREEITEM hTree)
{
	CImitateMeterDlg * pMainDlg = (CImitateMeterDlg *)theApp.m_pMainWnd;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
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
	WORD i,j,wNumOf1K_flash,loopMax;//1kflash���ݵ���Ŀ
	UINT64 k;
	bool btestResult  = false;
	CString str;
	INT8U tmpbuf[12];
	INT16U st_seq = 1;
	Hex16ToBuf2(st_seq,tmpbuf);
	tmpbuf[2] = 1;

	CTime startTime,endTime;

	startTime = CTime::GetCurrentTime();

	memset(&pMainDlg->stRecvNodInfor,0,sizeof(ST_RECV_NOD_INFOR));

	ack = gSimJzq.Router_PaRst();


	//���ӽڵ������ʼ�� 
	m_l64AutoTestAddrCounter = AUTO_TEST_START_NOD_ADDR;//��ַ�ۼ�������ʼֵ1
	m_protocol_type = DLT645_2007;//2
	m_nodNumPerframe_Set = ADD_NODE_NUM_MAX;//�趨��ÿ֡�ڵ�����200
	//����ɾ���ڵ�ṹ���ʼ��
	stADelNodTest.del_node_num = DEL_SALVE_NODE_NUM_IN_ADT;//100
	i = ((ADD_SALVE_NODE_NUM_IN_ADT - DEL_SALVE_NODE_NUM_IN_ADT)>>1);//���м�ɾ��
	stADelNodTest.before_del_pos = (BYTE)i;//50
	stADelNodTest.after_del_pos = i + DEL_SALVE_NODE_NUM_IN_ADT + 1;//151
	stADelNodTest.nodCounter    = AUTO_TEST_START_NOD_ADDR;//1
	while (hNextItem)
	{
		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			switch(atol(strName.Mid(0,2)))
			{
			   case 1://��ɾ��  ����1024  ��1024
				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
				for (;stADelNodTest.nodCounter - 1 < MAX_NOD_NUM;)
				{
					plog.saveLog_strAll(TIME,"��ʼ�����ӽڵ�",1);
					str.Format("��%d���ڵ�����ϣ���ӽڵ�\r\n",stADelNodTest.nodCounter -1);
					pMainDlg->m_flashData.ReplaceSel(str);
					///////////////////////////���ӽڵ�////////////////////////////////
					ack=addNode(atol(strName.Mid(0,2)));//����һ���ڵ㣬addNode������ �����������������ͣ�ÿ�����͵�ʱ����г�ʱ�ȴ���������������ȴ�
					plog.saveLog_testresultAll(TIME,"���" ,ack,0);
					plog.saveLog_strAll(NOTIME,"",1);
				}
				if(m_l64AutoTestAddrCounter >= MAX_NOD_NUM)
				{
					plog.saveLog_strAll(TIME,"��ʼ����ȡ�ڵ�����",1);
					str.Format("��ȡ%d���ڵ��--�ڵ���Ϣ\r\n",stADelNodTest.nodCounter -1);
					pMainDlg->m_flashData.ReplaceSel(str);
					plog.saveLog_str(DATA_FILE,TIME,str);
					j = 0;
					ack =gSimJzq.HostSendRcv376_2NoBuf(0x10,F1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);//��ȡ�ӽڵ�����
					INT16U cnt= Buf2ToHex16(&DstDecodeDataFrame.s_RcvDataBuf[0]);
					plog.saveLog_testresultAll(TIME,"���" ,ack,0);
					plog.saveLog_strAll(NOTIME,"",1);
			
					//////////////////////////��ȡ�ڵ���Ϣ�������ж�//////////////////////////////////////////
					pMainDlg->stRecvNodInfor.wSlaveNodRdSN = READ_SN_BEGIN;//ÿ�ζ��Ǵ����0��ʼ��ȡ�ӽڵ���Ϣ
					pMainDlg->stRecvNodInfor.wSumCurrentNodNum = 0;//��ǰ�ڵ����ۼ�ֵ��λ
					pMainDlg->stRecvNodInfor.wAddrPos = 0;//ÿ�����¶�ȡ��Ϣ��ʱ�򣬽ڵ��ַд��Ļ�����ָ����Ҫ��λ
					pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum = pMainDlg->stRecvNodInfor.wTotlaNodNum;//ȫ������Ҫ��

					j = 0;
					plog.saveLog_strAll(TIME,"��ʼ�����ڵ���Ϣ",1);
					for (; (pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum); )
					{
						if(pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum <= MAX_READ_NUM) //����˴���Ҫ��ȡ�Ľڵ�����
						{
							pMainDlg->stRecvNodInfor.byRdNodNumNow =(BYTE) pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum;
						}
						else
						{
							pMainDlg->stRecvNodInfor.byRdNodNumNow = MAX_READ_NUM;				
						}
						//sendData2Module(AFN10,F2,LAUNCH);//��ȡ�ڵ���Ϣ ÿ������255	
						WORD wdata;//��ʼ���
						BYTE bydata;//��ȡ����
						INT8U buf10f2[3];
						wdata = pMainDlg->stRecvNodInfor.wSlaveNodRdSN;
						bydata = pMainDlg->stRecvNodInfor.byRdNodNumNow;
						buf10f2[0] = (BYTE)wdata;
						buf10f2[1] = (BYTE)(wdata>>8);
						buf10f2[2]= bydata;

						ack =gSimJzq.HostSendRcv376_2Buf(0x10,F2,buf10f2,3,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
						if (ack == DACK_SUCESS)
						{
							j = 0;
							pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum -= pMainDlg->stRecvNodInfor.byRdNodNumNow;//����ʣ����Ҫ��ȡ�Ľڵ���
							pMainDlg->stRecvNodInfor.wSlaveNodRdSN += pMainDlg->stRecvNodInfor.byRdNodNumNow;//���¶�ȡ�ڵ����
						}
					}
					plog.saveLog_testresultAll(TIME,"���" ,ack,0);
					plog.saveLog_strAll(NOTIME,"",1);
					//pMainDlg->m_flashData.ReplaceSel(_T("���нڵ���Ϣ�ȶԽ���\r\n"));//�༭����ʾ
					//����ȫ����ȡ���֮����е��ж�

				}

				///////////////////////////��ȡFLASH���ݲ����бȶ�/////////////////////////////////////////////////

				plog.saveLog_strAll(TIME,"��ʼ����flash�Ͻڵ���Ϣ",1);
				if(atol(strName.Mid(0,2))== 1)
				{
					k = m_l64AutoTestAddrCounter - 1;//ʵ��д���˶��ٸ��ڵ㣨��ַ��д���������Ƕ�Ӧ��)
					wNumOf1K_flash = (WORD)((k % NOD_NUM_OF_1KFLASH == 0)?(k >> 6):((k>>6)+1));
				}else
				{
					wNumOf1K_flash = 24;//�̶���ȡ24K���ݣ���Ϊ��Ƭ���洢���ƿ������������FLASH���治��˳���//(WORD)((k % NOD_NUM_OF_1KFLASH == 0)?(k >> 6):((k>>6)+1));
				}
				pMainDlg->m_u32ReadFlashAddr = FLASH_START_ADDR;
				pMainDlg->stFlashInfor.wAddrPos = 0;
				k = 0;
				for (j=0; j<wNumOf1K_flash;)
				{						
					DWORD nsize;
					WORD wReadSize;
					UINT8 buf0f100[6];
					int num_0f100=0;
					//m_u32ReadFlashAddr = 0x12345678;
					memcpy(&buf0f100[num_0f100],&pMainDlg->m_u32ReadFlashAddr,4);
					for (i=0;i<4;i++)
					{
						num_0f100+=1;
					}
					wReadSize = FLASH_READ_LENGTH;
					memcpy(&buf0f100[num_0f100],&wReadSize,2);
					for (i=0;i<2;i++)
					{
						num_0f100+=1;;
					}
					//д�������־
					str.Format(_T("��ʼ��ַ��0x%.8X,��ȡ����:%d"),pMainDlg->m_u32ReadFlashAddr,wReadSize);
					plog.saveLog_str(DATA_FILE,TIME,str);
					ack =gSimJzq.HostSendRcv376_2Buf(0xF0,F100,buf0f100,num_0f100,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
					if (ack==DACK_SUCESS)
					{
						pMainDlg->m_u32ReadFlashAddr += FLASH_READ_LENGTH;//ÿ�ε�ַƫ��1024�ֽ�
						plog.saveLog_str(DATA_FILE,TIME,"��ȡ�ɹ���ַƫ��1024�ֽ�");
						k = 0;
					}
					else
					{
						k++;
							if((k < RESEND_CHANCE_TIMES))	
							{
								//pMainDlg->m_flashData.ReplaceSel(_T("��������ȡFLASHʧ��\r\n"));//�༭����ʾ
								plog.saveLog_str(DATA_FILE,TIME,"��������ȡFLASHʧ��");
								continue;//j++ ��Ҫ�ŵ���󣬷�������ѭ�����������J++
							} 
					}
					j++;
				}
				plog.saveLog_strAll(TIME,"��������flash�Ͻڵ���Ϣ",1);
				//����ȫ����ȡ���֮����е��ж�
				//if (!pMainDlg->stFlashInfor.wAddrPos)
				//{
				//	pMainDlg->m_flashData.ReplaceSel(_T("��⵽����ӽڵ��FLASH�ڵ��д��ָ��Ϊ0"));//�༭����ʾ
				//	//AfxMessageBox("��⵽����ӽڵ��FLASH�ڵ��д��ָ��Ϊ0");
				//
				//}else if (pMainDlg->stFlashInfor.wAddrPos + 1 != stADelNodTest.nodCounter)
				//{
				//	pMainDlg->m_flashData.ReplaceSel(_T("��⵽��FLASH����:ģ�鷵�ص�FLASH�ϵ���Ч�ӽڵ��������ܺ�ʵ�ʷ����Ľڵ�������һ��"));//�༭����ʾ
				//	//AfxMessageBox("��⵽��FLASH����:ģ�鷵�ص�FLASH�ϵ���Ч�ӽڵ��������ܺ�ʵ�ʷ����Ľڵ�������һ��");
				//}else if (atol(strName.Mid(0,2))== 1)
				//{
				//	if (pMainDlg->stFlashInfor.U64FlashAddrs[pMainDlg->stFlashInfor.wAddrPos-1] !=  stADelNodTest.nodCounter - 1)
				//	{
				//		pMainDlg->m_flashData.ReplaceSel(_T("��⵽�����һ��FLASH�ڵ�ĵ�ַ����д������һ����ַ"));
				//		//AfxMessageBox("��⵽�����һ��FLASH�ڵ�ĵ�ַ����д������һ����ַ");
				//	}
				//}
					///////////////////////////////�������̿���/////////////////////////////////////

					str = _T("���-");
					str += _T("-��ȡ �ӽڵ������ɣ�\r\n-----------------------�������һ��------------------------\r\n���ģ��!!!�����ϵ�!!//�ȴ�ģ���������к󣬽��и�λ���ٽ��к����������");
				//plog.saveLog_str(DATA_FILE,TIME,"�������ԣ�"+strName);
				plog.saveLog_testresultAll(TIME,strName+"�����",ack,2);
			break;

			//if (m_hThreadsend==NULL)//������;ֹͣ����
			//{
			//	break;
			//}
			case 2://��ɾ��  ��200 ɾ100  ֱ����1024���ڵ� ���ȶ�flash��ַ�洢
				plog.saveLog_strAll(TIME,"��ʼ���ԣ�"+strName,2);
				for (;stADelNodTest.nodCounter - 1 < MAX_NOD_NUM;)
				{
					if(m_hThreadsend==NULL)//������;ֹͣ����
					{
						break;
					}
					plog.saveLog_strAll(TIME,"��ʼ�����ӽڵ�",1);
					str.Format("��%d���ڵ�����ϣ���ӽڵ㣬�׵�ַΪ%d\r\n",stADelNodTest.nodCounter - 1,m_l64AutoTestAddrCounter);
					plog.saveLog_str(DATA_FILE,TIME,str);
					///////////////////////////���ӽڵ�////////////////////////////////
					ack=addNode(atol(strName.Mid(0,2)));//����һ���ڵ㣬addNode������ �����������������ͣ�ÿ�����͵�ʱ����г�ʱ�ȴ���������������ȴ�
					if (ack== DACK_SUCESS)
					{
						plog.saveLog_strAll(TIME,"������ɹ�",0);
						plog.saveLog_strAll(NOTIME,"",1);
					}
					else
					{
						
						plog.saveLog_strAll(TIME,"�����ʧ�ܡ�����ֹͣ���ԭ��",0);
						plog.saveLog_strAll(TIME,"",1);
						m_hThreadsend==NULL;
						break;
					}

						plog.saveLog_strAll(TIME,"��ʼ��ɾ���ڵ�",1);
						if (stADelNodTest.nodCounter < MAX_NOD_NUM)//���124���ڵ㲻��ɾ��
						{
							if(m_hThreadsend==NULL)//������;ֹͣ����
							{
								break;
							}
							//sendData2Module(AFN11,F2,LAUNCH);//ɾ���ڵ���
							//IsErrAppear();
							BYTE j;
							int num_11f2=0;
							UINT8 buf11f2[4096];
							CString str1,str2,str3;
							buf11f2[num_11f2++] = stADelNodTest.del_node_num;
							//д�������־
							Sleep(1000);
							LONG64 addr64,u64Data;
							addr64 = ((m_l64AutoTestAddrCounter - 1)/ADD_SALVE_NODE_NUM_IN_ADT -1)*ADD_SALVE_NODE_NUM_IN_ADT + stADelNodTest.before_del_pos+1;
							str.Format(_T("��֡ɾ���ӽڵ�������%d��ɾ���Ľڵ��ʼ��ַΪ��%d--��ַ�б�Ϊ��"),stADelNodTest.del_node_num,addr64);
							for (i = 0; i < stADelNodTest.del_node_num; i++)
							{					
								//д�������־
								str1.Format(_T("%I64d,"),addr64);
								str+= str1;

								u64Data = addr64;
								for (j=0; j<6; j++)//set 6 byte addr
								{
									//���ֽ����ݷ���ǰ�� 
									buf11f2[num_11f2++] = (((u64Data%100)/10)<<4)+(u64Data%10);
									u64Data /= 100;
								}
								addr64++;//��ַ�ۼ�					
							}
							stADelNodTest.nodCounter -= stADelNodTest.del_node_num;	
							plog.saveLog_str(DATA_FILE,TIME,str);
							plog.saveLog_str(DATA_FILE,NOTIME,"");
							ack =gSimJzq.HostSendRcv376_2Buf(0x11,F2,buf11f2,num_11f2,sQGDW376_2HostFrame,DstDecodeDataFrame,1);//ɾ���ӽڵ���Ϣ
							plog.saveLog_testresultAll(TIME,"���" ,ack,0);
							plog.saveLog_strAll(NOTIME,"",1);
							//else
							//{
							//	plog.saveLog_strAll(TIME,"ɾ������ʧ��,ֹͣ���Լ��ԭ��",1);
							//	m_hThreadsend==NULL;
							//	break;
							//}//!!!!Ϊʲôȷ��֡����ʧ��
						}else 
						{
							plog.saveLog_strAll(TIME,"���124���ڵ㲻����ɾ������",0);
							plog.saveLog_strAll(NOTIME,"",1);
						}
		//}//-----

					plog.saveLog_strAll(TIME,"��ʼ��ȡ�ڵ���������",1);
					j = 0;
					ack =gSimJzq.HostSendRcv376_2NoBuf(0x10,F1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);//��ȡ�ӽڵ�����
					INT16U cnt= Buf2ToHex16(&DstDecodeDataFrame.s_RcvDataBuf[0]);
					if(ack == DACK_SUCESS)
					{	
						str.Format("������%u", cnt);
						pMainDlg->stRecvNodInfor.wTotlaNodNum = cnt;
						plog.saveLog_strAll(TIME,"������ɹ����ڵ���Ϊ"+str,0);
						plog.saveLog_strAll(NOTIME,"",1);
					}

					//////////////////////////��ȡ�ڵ���Ϣ�������ж�//////////////////////////////////////////
					pMainDlg->stRecvNodInfor.wSlaveNodRdSN = READ_SN_BEGIN;//ÿ�ζ��Ǵ����0��ʼ��ȡ�ӽڵ���Ϣ
					pMainDlg->stRecvNodInfor.wSumCurrentNodNum = 0;//��ǰ�ڵ����ۼ�ֵ��λ
					pMainDlg->stRecvNodInfor.wAddrPos = 0;//ÿ�����¶�ȡ��Ϣ��ʱ�򣬽ڵ��ַд��Ļ�����ָ����Ҫ��λ
					pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum = pMainDlg->stRecvNodInfor.wTotlaNodNum;//ȫ������Ҫ��

					j = 0;
					plog.saveLog_strAll(TIME,"��ʼ�����ڵ���Ϣ",1);
					for (; (pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum); )
					{
						if(m_hThreadsend==NULL)//������;ֹͣ����
						{
							break;
						}
						if(pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum <= MAX_READ_NUM) //����˴���Ҫ��ȡ�Ľڵ�����
						{
							pMainDlg->stRecvNodInfor.byRdNodNumNow =(BYTE) pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum;
						}
						else
						{
							pMainDlg->stRecvNodInfor.byRdNodNumNow = MAX_READ_NUM;				
						}
						//sendData2Module(AFN10,F2,LAUNCH);//��ȡ�ڵ���Ϣ ÿ������255	
						WORD wdata;//��ʼ���
						BYTE bydata;//��ȡ����
						INT8U buf10f2[3];
						wdata = pMainDlg->stRecvNodInfor.wSlaveNodRdSN;
						bydata = pMainDlg->stRecvNodInfor.byRdNodNumNow;
						buf10f2[0] = (BYTE)wdata;
						buf10f2[1] = (BYTE)(wdata>>8);
						buf10f2[2]= bydata;
						ack =gSimJzq.HostSendRcv376_2Buf(0x10,F2,buf10f2,3,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
						if (ack == DACK_SUCESS)
						{
							j = 0;
							INT16U cnt= Buf2ToHex16(&DstDecodeDataFrame.s_RcvDataBuf[0]);
							//plog.saveLog_HexBuf(DATA_FILE,TIME,DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen);
							//Sleep(20000);
							pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum -= pMainDlg->stRecvNodInfor.byRdNodNumNow;//����ʣ����Ҫ��ȡ�Ľڵ���
							pMainDlg->stRecvNodInfor.wSlaveNodRdSN += pMainDlg->stRecvNodInfor.byRdNodNumNow;//���¶�ȡ�ڵ����
						}
					}
					plog.saveLog_testresultAll(TIME,"���" ,ack,0);
					plog.saveLog_strAll(NOTIME,"",1);


				///////////////////////////��ȡFLASH���ݲ����бȶ�/////////////////////////////////////////////////

				plog.saveLog_strAll(TIME,"��ʼ:��FLASH�ϵ����нڵ�Ľڵ���Ϣ",1);
				k = m_l64AutoTestAddrCounter - 1;//ʵ��д���˶��ٸ��ڵ㣨��ַ��д���������Ƕ�Ӧ��)
				wNumOf1K_flash = (WORD)((k % NOD_NUM_OF_1KFLASH == 0)?(k >> 6):((k>>6)+1));
				//wNumOf1K_flash = 24;//�̶���ȡ24K���ݣ���Ϊ��Ƭ���洢���ƿ������������FLASH���治��˳���//(WORD)((k % NOD_NUM_OF_1KFLASH == 0)?(k >> 6):((k>>6)+1));
				pMainDlg->m_u32ReadFlashAddr = FLASH_START_ADDR;
				pMainDlg->stFlashInfor.wAddrPos = 0;
				k = 0;
				int list=0;
				
				for (j=0; j<wNumOf1K_flash;)
				{	
					int SIX=6;
					if(m_hThreadsend==NULL)//������;ֹͣ����
					{
						break;
					}
					DWORD nsize;
					WORD wReadSize;
					INT8U buf0f100[6];
					int num_0f100=0;
					memcpy(&buf0f100[num_0f100],&pMainDlg->m_u32ReadFlashAddr,4);
					for (i=0;i<4;i++)
					{
						num_0f100+=1;
					}
					wReadSize = FLASH_READ_LENGTH;
					memcpy(&buf0f100[num_0f100],&wReadSize,2);
					for (i=0;i<2;i++)
					{
						num_0f100+=1;;
					}
					//д�������־
					str.Format(_T("��ʼ��ַ��0x%.8X,��ȡ���ȣ�%d,��ȡ����:64"),pMainDlg->m_u32ReadFlashAddr,wReadSize);
					plog.saveLog_str(DATA_FILE,TIME,str);
					ack =gSimJzq.HostSendRcv376_2Buf(0xF0,F100,buf0f100,num_0f100,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
					if (ack==DACK_SUCESS)
					{
						for (int h=0;h<64;h++)
						{
							for(int p=0;p<6;p++)
							{
								FALSH_ACKNODELIST[list][p]=DstDecodeDataFrame.s_RcvDataBuf[p+SIX];
							}
							list++;
							SIX+=16;
						}
						pMainDlg->m_u32ReadFlashAddr += FLASH_READ_LENGTH;//ÿ�ε�ַƫ��1024�ֽ�
						plog.saveLog_str(DATA_FILE,TIME,"��ȡ64���ɹ�����ַƫ��1024�ֽ�");
						//plog.saveLog_HexBuf(DATA_FILE,TIME,DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen);
						plog.saveLog_str(DATA_FILE,NOTIME,"");

						k = 0;
					}
					else
					{
						k++;
						if((k < RESEND_CHANCE_TIMES))	
						{
							//pMainDlg->m_flashData.ReplaceSel(_T("��������ȡFLASHʧ��\r\n"));//�༭����ʾ
							plog.saveLog_str(DATA_FILE,TIME,"��ȡFLASHʧ��,ֹͣ����");
							m_hThreadsend==NULL;
							if(m_hThreadsend==NULL)//������;ֹͣ����
							{
								break;
							}
							continue;//j++ ��Ҫ�ŵ���󣬷�������ѭ�����������J++
						} 
					}
					j++;
				}

				plog.saveLog_strAll(TIME,"������ɹ�����ȡFLASH��Ϣ����",0);
				if (NODE_RAMACKLIST[list][0]==FALSH_ACKNODELIST[list][0])
				{
					plog.saveLog_strAll(TIME,"��ַ�ȶԳɹ�",0);
					plog.saveLog_strAll(NOTIME,"",1);
				}
				else
				{
					plog.saveLog_strAll(TIME,"��ַ�ȶ�ʧ������ԭ�򣡲���ֹͣ",0);
					plog.saveLog_strAll(NOTIME,"",1);
					break;
				}
           }

				///////////////////////////////����/////////////////////////////////////

				str = _T("���--ɾ��");
				str += _T("-��ȡ �ӽڵ������ɣ�\r\n-----------------------�������һ��------------------------\r\n");			
				plog.saveLog_testresultAll(TIME,strName+"���Խ����������",ack,0);
				plog.saveLog_strAll(NOTIME,"",2);
				break;
			default:
				break;
				}
		}
		hNextItem = pMainDlg->m_treeProject.GetNextItem(hNextItem,TVGN_NEXTVISIBLE);	
	}

}

int L=0;

INT8U CTESTNODE::addNode(int tpe) 
{
	CImitateMeterDlg * pMainDlg = (CImitateMeterDlg *)theApp.m_pMainWnd;
	// TODO: Add your command handler code here
	BYTE total_nod_num = 0,i;//��Ҫ���͵��ܽڵ���
	UINT64 addr_counter_be4Send;//ÿ�η���ǰ����ʼ��ַ��¼����ֹ���մ������ݴ����ʱ���ط���
	WORD NodNum;
	INT8U ack;
	//if (tpe==1)//autoTest == AUTO_TEST)
	//{
	//	m_add_nod_num = ADD_NODE_NUM_MAX;//ÿ��������ӵĽڵ���
	//} 
	//else
	//{
	//	m_l64AutoTestAddrCounter = _ttoi64(m_start_nod_addr);//0
	//}
	m_add_nod_num = ADD_NODE_NUM_MAX;//ÿ��������ӵĽڵ���
	i=0;

	//
	if (tpe==1)
	{
		if (m_l64AutoTestAddrCounter - 1 + m_add_nod_num <= MAX_NOD_NUM)total_nod_num = m_add_nod_num;
		else														    total_nod_num = (BYTE) (MAX_NOD_NUM - (m_l64AutoTestAddrCounter-1));
	} 
	else
	{
		if (stADelNodTest.nodCounter - 1 + m_add_nod_num <= MAX_NOD_NUM)total_nod_num = m_add_nod_num;
		else														    total_nod_num = (BYTE) (MAX_NOD_NUM - (stADelNodTest.nodCounter-1));

	}

	for (;total_nod_num>0;)
	{		
		if (total_nod_num >= m_nodNumPerframe_Set)
		{			
			gB_nodNumThisFrame = m_nodNumPerframe_Set;total_nod_num -= m_nodNumPerframe_Set;
		}else
		{
			gB_nodNumThisFrame = total_nod_num;
			total_nod_num  = 0;
		}
		addr_counter_be4Send = m_l64AutoTestAddrCounter;
		NodNum = stADelNodTest.nodCounter;
		BYTE j;
		CString str1,str2;
		UINT8 buf[4096];
     	//д�������־
		str1.Format(_T("��֡��Ӵӽڵ�����:%d"),gB_nodNumThisFrame);
		int s=0;
		buf[s]=gB_nodNumThisFrame;
		s++;
		//д�������־
		str1+= _T("д��ĵ�ַΪ��Э�����ͣ�");
		LONG64 addr64;
		//��Ӵӽڵ��ַ 
		for (i = 0; i < gB_nodNumThisFrame; i++)
		{
			addr64 = m_l64AutoTestAddrCounter;
			//д�������־
			str2.Format(_T("%I64d,"),m_l64AutoTestAddrCounter);
			str1+=str2;

			//д�������־
			str2.Format(_T("%d  "),m_protocol_type);
			str1+=str2;
			for (j=0; j<6; j++)//set 6 byte addr
			{
				//���ֽ����ݷ���ǰ�� 
				buf[s++] = (((addr64%100)/10)<<4)+(addr64%10);
				NODE_RAMACKLIST[L][j] = (((addr64%100)/10)<<4)+(addr64%10);
				//stFrame.CS += BufRecv[stFrame.L++];
				addr64 /= 100;
			}
			L++;
			buf[s++] = m_protocol_type;//Э������
			//BufToBuf(&buf[1+n*7],addr64+m_protocol_type,7);
			m_l64AutoTestAddrCounter++;//��ַ�ۼ�
			stADelNodTest.nodCounter++;
			//stFrame.CS += BufRecv[stFrame.L++];
		}
		plog.saveLog_str(DATA_FILE,TIME,str1);
		plog.saveLog_str(DATA_FILE,NOTIME,"");

		ack = gSimJzq.HostSendRcv376_2Buf_NoAck(0x11,F1,buf,s);//��ӽڵ�

		if(ack == DACK_SUCESS)
		{
			return ack;
		}
		if(m_l64AutoTestAddrCounter > MAX_NOD_ADDR) break;//����6�ֽ�BCD��ĵ�ַ��Χ		
	}
	//	
	return ack;
}
