
#ifndef _SIMMTER_H
#define _SIMMTER_H
#include "User_Mcu_Cfg.h"
#include "User_App_Cfg.h"

#define DNOACKDICNT   16

typedef struct 
{
 INT32U s_Di;
 INT32U s_Time[FRAME645_RESEND_MAXCNT+1];
 INT8U  s_RcvCnt;
	
} sNoAckDiMsg;//����֡��ͷ֡������֡

typedef struct 
{
 INT32U s_Time[20];
 INT8U  s_RcvCnt;
	
} sAckAmtMsg;//����֡��ͷ֡������֡

typedef struct 
{
  INT8U s_NoAckDiCnt;
  sNoAckDiMsg   s_NoAckMsg[DNOACKDICNT];
} sNoAckAllMsg;

typedef struct 
{
 INT8U s_Sta;//��ǰ�ѱ�״̬����ʽBIN��00H ��ʾ�ѱ������01H ��ʾ�ѱ��С�
 INT8U s_SendCnt;//���α��ķ��ص�ʵ�ʵ��ͨ�ŵ�ַ��������ʽBIN��
 INT8U  s_AllCnt;//ʵ�ʵ����������ʽBIN
 INT16U s_SmtBpStart;
	
} sSearchMeterData;//����֡��ͷ֡������֡

#include "CDTL645.H"
#include "CDTL2007.h"
class CSimMeter: public cDTL2007,public CDTL645
{
public:
	
	CSimMeter(void);
	~CSimMeter(void);
public:
	void SetAmtAddBp(INT16U vSrcBp);
	void SetSearchSta(INT8U vSrcallcnt,INT8U vSrcSendCnt,INT16U vSrcAmtBp,INT8U vSrcSta);
	INT8U  Cmp645DiDataAmt(INT8U *pSrcAddBuf,INT8U pcttype,INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,INT8U Cmptype=1);
	INT8U  Cmp645DiDataAndAck(INT8U pcttype,INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,Stu_Dtl2007  &ackData645Frame,INT8U Cmptype=1);
	INT8U CmpDeCode645DiData(Stu_Dtl2007 ackData645Frame);
	INT8U CheckNoDiAckmsg(sNoAckDiMsg  noackMsg);
//-------------------------------------------------
//���������ơ� QueNoDiAckmsg(INT32U vSrcDi,sNoAckDiMsg  &ackMsg)
//���������ܡ� ��ѯ�޷��ص���Ϣ
//������˵����        
//��I:	���롿  
//��O:	�����    
//������ֵ	��    DACK_SUCESS:
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���  �����ڡ� 2016��6��28��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INT8U QueNoDiAckmsg(INT32U vSrcDi,sNoAckDiMsg  &ackMsg);

	//-------------------------------------------------
//���������ơ� void SetNoAckDi(INT32U vSrcDi);
//���������ܡ� ���ò����ص�DIֵ
//������˵����        
//��I:	���롿   
//��O:	�����    
//������ֵ	��    
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���  �����ڡ� 2016��6��28��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void SetNoAckDi(INT32U vSrcDi);
//-------------------------------------------------
//���������ơ� void ClrALLNoAckDi(INT32U vSrcDi);
//���������ܡ� ��������ص�DIֵ
//������˵����        
//��I:	���롿   
//��O:	�����    
//������ֵ	��    
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���  �����ڡ� 2016��6��28��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void ClrNoAckDi(INT32U vSrcDi);
//-------------------------------------------------
//���������ơ� ClrALLNoAckDi(void);
//���������ܡ� ������в����ص�DIֵ
//������˵����        
//��I:	���롿   
//��O:	�����    
//������ֵ	��    
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���  �����ڡ� 2016��6��28��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void ClrALLNoAckDi(void);
	//-------------------------------------------------
//���������ơ� INT8U QueAckDiIsEn(INT32U vSrcDi);
//���������ܡ� ��ѯ��DI����
//������˵����        
//��I:	���롿   
//��O:	�����    
//������ֵ	��  DACK_SUCESS ��Ҫ����  
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���  �����ڡ� 2016��6��28��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
	INT8U QueAckDiIsEn(INT32U vSrcDi);
	INT8U ChangeMeterData(INT8U pctype,INT32U vSrcDi);
	INT8U  QueMeterData(INT8U pctype,INT32U vSrcDi,sDtl645_Buf  &Meterdata );
	void SendMeterData_64597(Stu_Dtl2007 stDtl2007);
	void SendBufToCom(INT8U *vSrcBuf,INT16U vSrcLen);
	void SendMeterData_645(Stu_Dtl2007 stDtl2007);
	void Send_BADD_645(Stu_Dtl2007 stDtl2007, INT8U * BufRecv , INT8U & BufRecvlen);
	INT8U  QueMeterData_645(INT32U vSrcDi,sDtl645_Buf  &Meterdata );
	INT8U ChangeMeterData_645(INT32U vSrcDi);
	//-------------------------------------------------
//���������ơ�void GetCOMM645ToBuf(INT16U  vSrcLen , INT16U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
//���������ܡ�  �Ӵ��ڵõ�����645֡  
//������˵����        
//��I:	���롿    vSrcLen �����������󳤶ȣ�      nWaitFramTime��֡��ʱ       nWaiteByteTime���ֽ���ʱ  .
//��O:	�����     recvbuf  recvlen��֡����
//������ֵ	��    
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���  �����ڡ� 2016��9��28��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void GetCOMM645ToBuf(INT16U  vSrcLen , INT16U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
//-------------------------------------------------
//���������ơ�  void CheckMeterOP(void)
//���������ܡ�  �Զ���鴮�ڵ�����
//������˵����        
//��I:	���롿   
//��O:	�����    
//������ֵ	��    
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���  �����ڡ� 2016��6��28��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void CheckMeterOP(void);

	//-------------------------------------------------
//���������ơ�  void SetSimMeterRunFg(INT8U type)
//���������ܡ�  
//������˵����        
//��I:	���롿  1:���� 0�������� 
//��O:	�����    
//������ֵ	��    
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���  �����ڡ� 2016��6��28��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void SetSimMeterRunFg(INT8U type);
	void SetAckFg(INT8U type);
	void ClrSimMeterComData(void);
//-------------------------------------------------
//���������ơ�  INT8U  Wait645ack(INT16U famedly,INT16U bytedly,Stu_Dtl2007 &DstDecode2007DataFrame)
//���������ܡ�  ��645����
//������˵����        
//��I:	���롿  famedly��֡��ʱ   bytedly���ֽ���ʱ 
//��O:	�����    DstDecode2007DataFrame �� 645����
//������ֵ	��    DACK_SUCESS 
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���  �����ڡ� 2016��6��28��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INT8U Wait645ack(INT16U famedly,INT16U bytedly,Stu_Dtl2007 &DstDecode2007DataFrame);

//-------------------------------------------------
//���������ơ�  INT8U Cmp645DiData(INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,INT8U Cmptype)
//���������ܡ�  �Ƚ�645֡��ֵ
//������˵����        
//��I:	���롿   vSrcDi��   vSrcBuf:645֡ vSrcLen������
//��O:	�����   
//������ֵ	��    DACK_SUCESS 
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���  �����ڡ� 2016��6��28��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INT8U Cmp645DiData(INT8U pcttype,INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,INT8U Cmptype=1);


	INT8U  QueMeterData_64597(INT32U vSrcDi,sDtl645_Buf  &Meterdata );
	INT8U  ChangeMeterData_645_97(INT16U vSrcDi);
	void ClrReadAmtCnt(void);
	INT32U QueReadAmtCnt(void);
	void  SetAckAmtFg(INT8U Ackfg);
	void  QueReadAmtMsg(sAckAmtMsg  &ReadAmtMsg);
private:
	  INT8U m_RunSta;
	  sAckAmtMsg  m_ReadAmtMsg;
	  sSearchMeterData   m_SearchMeterData;
	  INT16U  m_AmtAddBp;
public:
	INT8U m_NoFg;//�޷��ر�� 0:������ 1:����  
	INT32U  m_ReadAmtCnt;//�����ַͳ��
	INT8U   m_AmtAckFg;//1�� ��  0����    �ظ�������ַ
	
	
};

#endif
