#pragma once


// CTESTCCO_AFN14
#include "Tools.h"
#include "GW13762.h"
class CAFN14ReadMeterFun
{

public:

	INT8U TestOneAdd(INT8U CmpType);
		INT8U TestMoreAdd(INT8U CmpType);

	//-------------------------------------------------
	//���������ơ� INT8U  TestOneAddSetPa(void);
	//���������ܡ�  dan��ַ��������
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
	INT8U  TestOneAddSetPa(void);
	//��1�������������
	INT8U  TestOneAddReadMeter_OK(INT8U CmpType);
	//��1�������ظ�����
	INT8U  TestOneAddReadMeter_Step1Ack(INT8U CmpType);
	//��1���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ
	INT8U  TestOneAddReadMeter_Step1ErrAck(INT8U vSrcAckType,INT8U CmpType);

	//-------------------------------------------------
	//���������ơ� INT8U  TestAddReadMeter_Step1ErrAck_Amt(INT32U AmtSeq,INT8U vSrcAckType,INT8U ReCnt,INT8U CmpType);
	//���������ܡ� AMT��1���쳣�ظ�����  
	//������˵����        
	//��I:	���롿   AmtSeq: �ӽڵ㿪ʼ��ţ�vSrcAckType���ظ����� 0 ���ظ��� 1���ظ���SEQ;   ReCnt �ط�������  CmpType�� 0ʵ�ʱ�  1ģ���
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U  TestAddReadMeter_Step1ErrAck_Amt(INT32U AmtSeq,INT8U vSrcAckType,INT8U ReCnt,INT8U CmpType);
	//��3���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ,
	INT8U  TestOneAddReadMeter_Step3ErrAck_Amt(INT32U AmtSeq,INT8U vSrcAckType,INT8U CmpType);
	//��3���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ,
	INT8U  TestOneAddReadMeter_Step3ErrAck(INT8U vSrcAckType,INT8U CmpType);
	//��3���쳣�ظ����� �ظ�����֡
	INT8U  TestOneAddReadMeter_Step3ErrAckNo_Amt(INT32U Amtseq,INT8U CmpType);
	//��3���쳣�ظ����� �ظ�����֡
	INT8U  TestOneAddReadMeter_Step3ErrAckNo(INT8U CmpType);
	//����ַ·�ɲ���
	INT8U TestOneAddRouter(INT8U CmpType);
	//���ַ��������
	INT8U  TesMoreAddSetPa(void);
	//���DI����������
	INT8U  TesMoreAddReadMeter(INT8U CmpType);

	//��1�������ظ�����
	INT8U  TestMoreAddReadMeter_Step1Ack(INT8U CmpType);
	//��1���쳣�ظ�����  ackType: 0 ���ظ��� 1���ظ���SEQ
	INT8U  TestMoreAddReadMeter_Step1errAck(INT8U Acktype,INT8U CmpType);
	//��3�쳣�ظ�SEQ�����ظ�����
	INT8U  TestMoreAddReadMeter_Step3ErrAck(INT8U CmpType);
	//��3�쳣�ط��ϲ���
	INT8U  TestMoreAddReadMeter_Step3ErrAckNo(INT8U CmpType);
	//MOre��ַ·�ɲ���
    INT8U  TestMoreAddRouter(INT8U CmpType);

};
class CTESTCCO_AFN14 : public CWnd, public CAFN14ReadMeterFun
{
	DECLARE_DYNAMIC(CTESTCCO_AFN14)

public:
	CTESTCCO_AFN14();
	virtual ~CTESTCCO_AFN14();
	void C3762_TEST(HTREEITEM hTree);//����������
	CTools m_tool;
	CGW13762 m_Cgw13762;
	INT8U AFN14OneMeterNoAck(void);
	INT8U AFN14MoreMeterNoAck(void);

protected:
	DECLARE_MESSAGE_MAP()
	
};


