#ifndef  _CDTL2007_H
#define  _CDTL2007_H



#include "User_Mcu_Cfg.h"
#include "GW13762.h"
#include "CSG13762.h"
#define FRAME645_MAX_LEN  254
#define DATA645_MAX_LEN  ( FRAME645_MAX_LEN-1)
#define PARALLEL376_2_MAX_CNT  13
typedef struct 
{
 INT8U 	s_pDstCmdBuf[FRAME645_MAX_LEN];//����ָ�룿
 INT8U 	s_vDstCmdLen;//
} sDtl2007_Read;	 //645-07���ṹ;

struct Stu_Dtl2007	 //645-07�ṹ
{
 INT8U  s_Con;//������
 INT32U s_Di;//DI
 INT8U  s_AmtBuf[6];//���ַ
 INT8U  s_PwdBuf[8];//��Կ�������ߴ���
 INT8U  s_Len;//���ݳ���
 INT8U 	s_pDstBuf[FRAME645_MAX_LEN];//����ָ�룿
 INT8U  s_type;//Э������
};

typedef struct 
{
 struct Stu_Dtl2007   DTLData;
 INT8U         Port;//�˿ں�
} sDtl645_07OP;

typedef struct 
{
 INT8U  s_DataBuf[FRAME645_MAX_LEN];
 INT16U  s_DataLen;
 INT8U   Port;//�˿ں�
} sDtl645_Buf;

//-----------------------------------------------------------------------------
//�������ơ�       CDTL2007
//���๦�ܡ�       �顢���� 645����07�꣬�顢�����㲥Уʱ��
//����Ա����˵���� ������˵�� 
//--------------------------------------------------------------
class cDTL2007
{

 public:
	 // :vDstAmtBuf���ַ, vDstFcnt:FE����  vDstFctFg:Э������ 0 645-97��1  645-07�� 3���㲥Уʱ���� :����TRUE����645Э��
     INT8U  CheckFull645Pct_All(const INT8U *pSrcBuf,const INT16U pSrcLen,INT8U &vDstFctFg);//���֡����С����
	 void CodeToAckData(struct Stu_Dtl2007 &Dtl2007Buf,const INT8U *vSrcBuf,const INT16U vSrcLen);
	 //-------------------------------------------------
//���������ơ�CodeReadDataCmd(TH_IN const INT32U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData)��
//���������ܡ�     //���������
//������˵����        
//��I:	���롿        INT32U s_Di;//DI
//                    INT8U  s_AmtBuf[6];//���ַ
//                    INT8U  s_type;//����ģʽ��0����FE�� 1����4��FE                
//��O:	�����       sDtl2007_Read &vDstCmdData
//������ֵ	��     ��ȷ��DACK_SUCESS   ����DACK_FAILURE   
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ���   �����ڡ� 2016��8��01��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  INT8U CodeReadDataCmd(TH_IN const INT32U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData);
//-------------------------------------------------
//���������ơ�INT8U Decode2007(TH_IN const INT8U *pSrcBuf,TH_IN const INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame);
//���������ܡ�      �������е�2007Э�� ֱ�ӽ���������645-07�ṹ����   
//������˵����        
//��I:	���롿        *pSrcBuf :  ��Ҫ����������   ,  pSrcLen ����Ҫ�����곤��                   
//��O:	�����       DstDecode2007DataFrame ����ȷ��Э��������ṹ��   
//������ֵ	��     ��ȷ��DACK_SUCESS   ����DACK_FAILURE   
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ����   �����ڡ� 2016��6��29��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INT8U Decode2007(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame);
 
//-------------------------------------------------
//���������ơ�void CodeToWatchData(TH_IN const struct Stu_Dtl2007 Dtl2007Buf,TH_IN INT8U type,TH_OUT INT8U *pDstBuf,TH_OUT INT8U &pDstLen)
//���������ܡ�     645 �ṹ ��������������� д���ݣ�����������ʽ��    
//������˵����        
//��I:	���롿     Dtl2007Buf :  645����07���ݽṹ     type=0 ��	  type=0 0x68ǰ��0xfe ,����û��                
//��O:	�����       *pDstBuf �� �������� ��  pDstLen �����곤�� 
//������ֵ	��     ��ȷ��DACK_SUCESS   ����DACK_FAILURE   
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ����   �����ڡ� 2016��6��29��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CodeToWatchData(TH_IN const struct Stu_Dtl2007 Dtl2007Buf,TH_IN INT8U type,TH_OUT INT8U *pDstBuf,TH_OUT INT16U &pDstLen);

//-------------------------------------------------
//���������ơ�void CodeToWatchPData(TH_IN const struct Stu_Dtl2007 Dtl2007Buf,TH_OUT INT8U *pDstBuf,TH_OUT INT8U &pDstLen);
//���������ܡ�     645 �ṹ ��������������� д���ݣ�ESAM������ʽ��    
//������˵����        
//��I:	���롿     Dtl2007Buf :  645����07���ݽṹ     type=0 ��	  type=0 0x68ǰ��0xfe ,����û��                
//��O:	�����       *pDstBuf �� �������� ��  pDstLen �����곤�� 
//������ֵ	��     ��ȷ��DACK_SUCESS   ����DACK_FAILURE   
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ����   �����ڡ� 2016��6��29��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CodeToWatchPData(TH_IN const struct Stu_Dtl2007 Dtl2007Buf,TH_OUT INT8U *pDstBuf,TH_OUT INT16U &vDstLen);

//-------------------------------------------------
//���������ơ�void  CodeReadAmtAdd(TH_IN INT8U vSrcLen,TH_IN INT8U type,TH_OUT INT8U *pDstBuf,TH_OUT INT8U &vDstLen)
//���������ܡ�  ��������ַ   
//������˵����        
//��I:	���롿      type=0 0x68ǰ��0xfe ,����û��               
//��O:	�����       *pDstBuf �� �������� ��  pDstLen �����곤�� 
//������ֵ	��     ��ȷ��DACK_SUCESS   ����DACK_FAILURE   
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ����   �����ڡ� 2016��6��29��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void  CodeReadAmtAdd(TH_IN INT8U type,TH_OUT INT8U *pDstBuf,TH_OUT INT16U &vDstLen);

//-------------------------------------------------
//���������ơ�INT8U DecodeReadAmtAdd(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame)
//���������ܡ�       ��������ַ  
//������˵����        
//��I:	���롿     *vSrcBuf �������������  �� vSrcLen ��������곤��	   type=0 0x68ǰ��0xfe ,����û��               
//��O:	�����       *pDstBuf �� �������� ��  pDstLen �����곤�� 
//������ֵ	��     ��ȷ��DACK_SUCESS   ����DACK_FAILURE   
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ����   �����ڡ� 2016��6��29��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INT8U DecodeReadAmtAdd(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame);

//-------------------------------------------------
//���������ơ�INT8U CheckFull645All(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame,TH_OUT INT8U &vDstFcnt,TH_OUT INT8U &vDstFctFg)
//���������ܡ�     ����Ƿ�Ϊ645Э�飬�Լ�����
//������˵����        
//��I:	���롿     *vSrcBuf ������������   �� vSrcLen �������곤��                 
//��O:	�����   pDstLen�� ����645֡���ܳ���
//������ֵ	��     ��ȷ��DACK_SUCESS   ����DACK_FAILURE   
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ����   �����ڡ� 2016��6��29��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INT8U Check645Full(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT INT16U &vDstLen);	

//-------------------------------------------------
//���������ơ�INT8U Check645Num(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT INT16U &vNum,TH_OUT INT8U *plenBuf);
//���������ܡ�    ��Ⲣ�� 645֡�ĸ��� ����
//������˵����        
//��I:	���롿     *vSrcBuf ������������   �� vSrcLen �������곤��                 
//��O:	�����  vNum ֡�ĸ��� ,plenBuf֡�� ����
//������ֵ	��     ��ȷ��DACK_SUCESS   ����DACK_FAILURE   
//��ȫ�ֱ�����       
//������˵����           
//��������	��  ����   �����ڡ� 2016��8��16��
//����  ������ ԭʼ�汾
//-------------------------------------------------
//���޸���	��     �����ڡ�
//����  ������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INT8U Check645Num(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT INT8U &vNum,TH_OUT INT16U *plenBuf);

};



#endif

