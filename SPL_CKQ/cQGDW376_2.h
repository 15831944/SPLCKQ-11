#ifndef _QGDW376_2_H
#define _QGDW376_2_H

#include "User_Mcu_Cfg.h"
#include "User_Ack_Def.h"
#include "User_App_Cfg.h"
//Լ���Ķ���
//#define DMACADD_LEN    6
#define DZB_MAXZJ_CNT    3    
#define D376_2_ZQ_MAXNUM 4 //�м̵�������
#define D376_2_NODATALEN   (12+(2+D376_2_ZQ_MAXNUM)*6)//��������֡��������ݳ���
//#define DTMPZBBUFLEN     20//��ʱ����BUF������100
//������Ķ���
#define DBIT_376_2Msg_MDFLAG  Bit2//ͨ��ģ���ʶ
#define DBIT_376_2Con_DIR     Bit7//Con�еĴ��䷽�� 0
#define DBIT_376_2Con_PRM     Bit6//Con�е�������־λ
//����ֵ�Ķ��� CON
#define DV376_2CON_COM_MODE     3 // D5��D0: 3	����ز�ͨ��	ָ���õ����߿���ز�ͨ��
#define DV376_2CON_PRM_MASTER   1   //D6:PRM =1����ʾ��֡������������վ��PRM =0����ʾ��֡�������ԴӶ�վ��
#define DV376_2CON_PRM_SLAVE    0
#define DV376_2CON_DIR_COMMD    1  //D7 DIR=0����ʾ��֡�������ɼ��������������б��ģ�DIR=1����ʾ��֡��������ͨ��ģ�鷢�������б��ġ�

//--------------��Ϣ��---------------------------------------------------------------------------------------
//D7	D6	D5	D4	D3	    D2            	D1	         D0	           BS   1
//     �м̼���	         |   ��ͻ���   | ͨ��ģ���ʶ	|�����ڵ��ʶ	|      ·�ɱ�ʶ		
//D7	D6	D5	D4	D3	    D2	                 D1	         D0	           BS	1
//        ��������ʶ	 |        �ŵ���ʶ
//D7-------------------------------------------------------------------------------D0		
//         Ԥ��Ӧ���ֽ���	                                                                   BIN	1
//D15	          D14?    D0	                                                                   BS	2
//���ʵ�λ��ʶ	 |ͨ������	
//D7-------------------------------------------------------------------------------D0		
//       �������к�                                                                                 BIN	1	
//------------------------------------------------------------------------------------------------------------------	
#define DV376_2MSG_ROUTERFLAG_ON         1 // ·�ɱ�ʶ��D0=0��ʾͨ��ģ���·�ɻ�����·��ģʽ��D0=1��ʾͨ��ģ�鲻��·�ɻ�������·ģʽ��
#define DV376_2MSG_ROUTERFLAG_OFF        0 // 
#define DV376_2MSG_NODE_ON             1 // �����ڵ��ʶ��ָ�ӽڵ㸽���ڵ��ʶ��0��ʾ�޸��ӽڵ㣬1��ʾ�и��ӽڵ㡣
#define DV376_2MSG_NODE_OFF            0 
#define DV376_2MSG_COMFLAG_MASTER      1 //ͨ��ģ���ʶ��0��ʾ�����ڵ�Ĳ�����1��ʾ�Դӽڵ����
#define DV376_2MSG_COMFLAG_E_SLAVE     0 
#define DV376_2MSG_EVENT_ON            1 //�¼���־��D0Ϊ0ʱ���ϱ��¼���D0Ϊ1ʱ���ϱ��¼���
#define DV376_2MSG_EVENT_OFF           0 // 
#define DV376_2MSG_PHASE_0             0 // 
#define DV376_2MSG_PHASE_1             1 // 
#define DV376_2MSG_PHASE_2             2 // 
#define DV376_2MSG_PHASE_3             3 // 
//����������Ϣ���Ķ��� CON  
typedef struct 
{
	INT8U      s_Con_ComMode: 6;       // D5��D0: 3	����ز�ͨ��	ָ���õ����߿���ز�ͨ��
	INT8U      s_Con_PRM:  1;          //Con�е�������־λ 0��������  1��ͨ��ģ��
	INT8U      s_Con_DIR:  1;          //Con�еĴ��䷽�� 0���Ӷ�վ 1������վ
} sPartQGDW376_2_Con;

typedef struct 
{
	//0:1
	INT8U      s_Msg_RouterFlag:  1;         // ·�ɱ�ʶ��D0=0��ʾͨ��ģ���·�ɻ�����·��ģʽ��D0=1��ʾͨ��ģ�鲻��·�ɻ�������·ģʽ?
	INT8U      s_reserved_1:      1;         //����
	INT8U      s_Msg_ComFlag:     1;         //��Ϣ���е�ͨ��ģ��ʶ�B��Buf[0]��D2
	INT8U      s_reserved_2:      5;         //����
	//1:1
	INT8U      s_chanle_num:      4;         //�ŵ���ʶ��ȡֵ0��15��0��ʾ�����ŵ���1��15���α�ʾ��1��15�ŵ���
  INT8U      s_errcode:         4;
	//2:1
	INT8U      s_ackbyte;
	//3:2
	INT16U     s_rateFlag;                   // 	ͨ�����ʣ���ʾͨ�Ų����ʣ�BIN��ʽ��0��ʾĬ��ͨ�����ʡ�
	
} sPartQGDW376_2_HeadDownMsg;//����֡��ͷ֡������֡


typedef struct 
{

	//0:1
	INT8U      s_Msg_RouterFlag:  1;         // ·�ɱ�ʶ��D0=0��ʾͨ��ģ���·�ɻ�����·��ģʽ��D0=1��ʾͨ��ģ�鲻��·�ɻ�������·ģʽ?
	INT8U      s_reserved_1:      1;         //����
	INT8U      s_Msg_ComFlag:     1;         //��Ϣ���е�ͨ��ģ��ʶ�B��Buf[0]��D2
	INT8U      s_reserved_2:      5;         //����
	//1:1
	INT8U      s_chanle_num:      4;         //�ŵ���ʶ��ȡֵ0��15��0��ʾ�����ŵ���1��15���α�ʾ��1��15�ŵ���
  INT8U      s_reserved_3:      4;
	//2:1
	INT8U      s_Msg_phase:       4;         //	ʵ�����߱�ʶ��ʵ��ӽڵ��߼����ŵ����ڵ�Դ���0Ϊ��ȷ����1��3���α�ʾ���Ϊ��1�ࡢ��2�ࡢ��3�ࡣ
  INT8U      s_Meter_flag:      4;         //���ͨ������������Ŀ�Ľڵ���ͨ����������ȡֵ��Χ0��15��0������1Ϊ�����ŵ�Ϊ���๩�磬�߼��ŵ�Ϊ���ŵ���2Ϊ�����ŵ�Ϊ                                                //���๩�磬�߼��ŵ�Ϊ���ŵ���3Ϊ�����ŵ�Ϊ���๩//�磬�߼��ŵ�Ϊ���ŵ���4Ϊ�����ŵ�Ϊ���๩�磬�߼��ŵ�Ϊ���ŵ���
  //3: 1
	INT8U      s_CmdCsq:          4;         //�ź�Ʒ�ʣ���Ϊ15����ȡֵ��Χ0��15��0��ʾ���ź�Ʒ�ʣ�1��ʾ���Ʒ�ʡ�(�ܲ鵽�������֪ͨ)
  INT8U      s_AckCsq:          4;
	//4: 1
	INT8U      s_Msg_Event:       1;         //�¼���־��D0Ϊ0ʱ���ϱ��¼���D0Ϊ1ʱ���ϱ��¼���
	INT8U      s_reserved_4:      7;         //����
	

	
} sPartQGDW376_2_HeadUpMsg;//����֡��ͷ֡������֡

typedef struct 
{
	union
	{
    sPartQGDW376_2_Con  s_conBit;
		INT8U s_conByte;
	} u_con;
	union
	{
	  sPartQGDW376_2_HeadUpMsg    s_UpMsgBit;
	  sPartQGDW376_2_HeadDownMsg  s_DownMsgBit;//5���ֽڳ���SEQ
		INT8U  s_msgbuf[5];
	} u_msg;
	INT8U      s_Msg_Seq;           //��Ϣ���б������к�
	INT8U      s_MainAddBuf[DMACADD_LEN];   //������ַ��Դ��ַ
	INT8U      s_RelayAddbuf[DMAC_RELAY_LEN];//�м̵�ַ,�����ڲ��������еĶ�ڵ㵥֡
  INT8U      s_DestAddBuf[DMACADD_LEN];//Ŀ�õ�ַ
  INT8U      s_AFN;            //Ӧ�ù�����
	INT16U     s_FN;             //���ݵ�Ԫ��ʶ
} sPartQGDW376_2_Head;//֡ͷ

typedef struct 
{
  sPartQGDW376_2_Head  s_head;
	INT8U      s_RcvDataBuf[D376_MAXRCVBUFLEN];//����������ָ�룬��Σָ�룬��ǰҪ����Ƿ���ֵ��Ҫָ��Ϸ��ռ�
	INT16U     s_RcvDataLen;//�������ݵĸ���
	INT8U      s_SendDataBuf[D376_MAXSENDBUFLEN];//����������ָ�룬��Σָ�룬��ǰҪ����Ƿ���ֵ��Ҫָ��Ϸ��ռ�
	INT16U     s_SendDataLen;//ʵ�ʷ����������ĳ��ȡ�
	INT16U     s_SendDataBufMaxLen;//�����������������ó��ȡ�
} sPartQGDW376_2CreatFrame;//��֡�Ľṹ

typedef struct 
{
  sPartQGDW376_2_Head  s_head;
	INT8U      *s_RcvDataBuf;//����������ָ�룬��Σָ�룬��ǰҪ����Ƿ���ֵ��Ҫָ��Ϸ��ռ�
	INT16U     s_RcvDataLen;//�������ݵĸ���
} sPartQGDW376_2DeCodeFrame;//��֡�Ľṹ

typedef struct 
{
	sPartQGDW376_2DeCodeFrame   s_Frame;
	INT8U Port;
	
}sPartQGDW376_2_Data;

//------��ɵ�376.2����֡����Ҫ�Ǵ������ã�ֻ�������õ���Ϣ������������
typedef struct 
{
  INT8U      s_Msg_Seq;           //��Ϣ���б������к�
	INT8U      s_SendDataBuf[D376_MAXSENDBUFLEN];//����������ָ�룬��Σָ�룬��ǰҪ����Ƿ���ֵ��Ҫָ��Ϸ��ռ�
	INT16U     s_SendDataLen;//ʵ�ʷ����������ĳ��ȡ�
} sQGDW376_2UpFrame;//��֡�Ľṹ

class cQGDW376_2
{
public:
//-----------------------------------------------------------------------------
//name : sPartQGDW376_2_Head  Init376_2UpFrame(INT8U MsgComFg,INT8U *vDestAddBuf,INT8U vSrcAfn,INT16U vSrcFn);
//Function:����֡��ʽ
// ��������:
//   Input��
//        MsgComFg-----------------��Ϣ���е�ͨ��ģ��ʶ
//        vSrcAfn------------------AFN
//        vSrcFn-------------------Fn
//   output:
//        &vDestAddBuf:  Ŀ�ĵ�ַ
//Return:
//        sPartQGDW376_2_Head �ṹ��
//ȫ�ֱ���: ��
//�� ��  ��: ���
//��     ��: 2006��6��16��
//��   ����: ԭʼ�汾
//-------------------------------------------------------------------------------------------------------
//�޸���:
//�ա���:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	sPartQGDW376_2_Head Init376_2UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn);
	
//-----------------------------------------------------------------------------
//sPartQGDW376_2_Head Creat376_2UpFrameFormDownFrame(sPartQGDW376_2_Head  downframe);
//Function:�齨����֡��ʽ
// ��������:
//   Input��
//        downframe-----------------����֡
//   output:
//        
//Return:
//        sPartQGDW376_2_Head �ṹ��
//ȫ�ֱ���: ��
//�� ��  ��: ���
//��     ��: 2006��6��16��
//��   ����: ԭʼ�汾
//-------------------------------------------------------------------------------------------------------
//�޸���:
//�ա���:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	sPartQGDW376_2_Head Creat376_2UpFrameFormDownFrame(TH_IN const sPartQGDW376_2_Head  downframe);
	
//----------------------------------------------------------------------------------
//name :  INT8U cQGDW376_2::Creat376_2Cs(const INT8U *vSrcBuf,INT16U vSrcLen)
//Function:����CS
// ��������:
//    Input��
//        vSrcBuf: Cs֡��ַ
//   �����vSrcLen������
//    Return:
//        �ã�ֵ��
//ȫ�ֱ���: ��
//�� ��  ��: ���
//��     ��: 2006��6��16��
//��   ����: ԭʼ�汾
//-------------------------------------------------------------------------------------------------------
//�޸���:
//�ա���:
//��   ����:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INT8U Creat376_2Cs(TH_IN const INT8U *vSrcBuf,TH_IN INT16U vSrcLen);

//-----------------------------------------------------------------------------
//name : INT8U  Check_376_2_Full(const INT8U *pSrcBuf,INT16U vSrcLen,INT16U &vDstLen))
//Function:���pSrcBuf֡�Ƿ���������376.2��֡,���ж�CS�Ƿ���ȷ
// ��������:
//   Input��
//        pSrcBuf-----------------�յ���֡����
//        vSrcLen-----------------�յ���֡����  
//   output:
//        &vDstLen:  376.2֡�Ľ�����ַ��
//Return:
//        ack: DACK_ERR_NULL��DACK_SUCESS
//ȫ�ֱ���: ��
//�� ��  ��: ���
//��     ��: 2006��6��16��
//��   ����: ԭʼ�汾
//-------------------------------------------------------------------------------------------------------
//�޸���:
//�ա���:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  INT8U Check_376_2_Full(TH_IN const INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT  INT16U &vDstLen);

//----------------------------------------------------------------------------------
//name :  INT8U cQGDW376_2::Code376_2(sPartQGDW376_2_Up SrcCodeDataFrame)
//Function:�����б��ĵ����ݻ����б��ĵ��������֡  
// ��������:
//    InOutput��
//        SrcCodeDataFrame: �����壬

//Return:
//        ack: DACK_ERR_BUF��DACK_SUCESS
//ȫ�ֱ���: ��
//�� ��  ��: ���
//��     ��: 2006��6��16��
//��   ����: ԭʼ�汾
//-------------------------------------------------------------------------------------------------------
//�޸���:
//�ա���:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    INT8U  Code376_2_Frame(TH_INOUT  sPartQGDW376_2CreatFrame &SrcCodeDataFrame);



//----------------------------------------------------------------------------------
//name :  INT8U Code376_2_UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,INT8U *pSrcRcvBuf,INT16U vSrcRcvLen,TH_OUT  sQGDW376_2UpFrame &sQGDW376_2UpFrame)
//Function:�����б��ĵ����ݻ����б��ĵ��������֡  
// ��������:
//   Input��
//        MsgComFg-----------------��Ϣ���е�ͨ��ģ��ʶ
//        pSrcAddBuf------------Ŀ���ַ
//        vSrcAfn------------------AFN
//        vSrcFn-------------------Fn
//        pSrcRcvBuf -------------�յ�������Դ
//        vSrcRcvLen -------------�յ������ݳ���
//   output:
//        &sQGDW376_2UpFrame:  

//Return:
//        ack: DACK_ERR_BUF��DACK_SUCESS
//ȫ�ֱ���: ��
//�� ��  ��: ���
//��     ��: 2006��6��16��
//��   ����: ԭʼ�汾
//-------------------------------------------------------------------------------------------------------
//�޸���:
//�ա���:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    INT8U  Code376_2_UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,TH_IN INT8U *pSrcRcvBuf,TH_IN INT16U vSrcRcvLen,TH_OUT  sQGDW376_2UpFrame &sQGDW376_2UpFrame);
		
//----------------------------------------------------------------------------------------------------------
//name : INT8U Decode376_2Frame(const INT8U *pSrcBuf,const INT16U vSrcLen,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
//Function:��һ֡���Ľ��н���
// ��������:
//    Input��
//        pSrcBuf-----------------�յ���֡����
//        vSrcLen-----------------�յ���֡����    
//    Output:
//        DstDecodeDataFrame--------���ؽṹ��
//Return:
//        ack: DACK_ERR_NULL,DACK_ERR_CS,DACK_SUCESS
//ȫ�ֱ���: ��
//�� ��  ��: ���
//��     ��: 2006��6��16��
//��   ����: ԭʼ�汾
//-------------------------------------------------------------------------------------------------------
//�޸���:
//�ա���:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   INT8U  Decode376_2Frame(TH_IN  INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT  sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
};
#endif

