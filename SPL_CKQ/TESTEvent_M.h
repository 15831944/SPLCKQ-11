#pragma once


// CTESTEvent_M
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
class  CEventPublic
{
public:
protected:
	//-------------------------------------------------
	//���������ơ� INT8U CmpEventIsOnSta(INT8U *vSrcAmtAdd,INT8U vSrcSeq,INT8U vSrcCnt,INT8U CmpType);
	//���������ܡ� �ȶ��¼��Ƿ����б���
	//������˵����        
	//��I:	���롿   vSrcCnt�� ��ǰ���͵Ĵ�����CmpType��0 �ȶ������ϱ��б�  1 �ȶ����ϱ��б�
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������

INT8U CmpEventIsOnSta(INT8U *vSrcAmtAdd,INT8U vSrcSeq,INT8U vSrcCnt,INT8U CmpType);
//dan��ַ��������
INT8U   TestOneAddSetPa(void);
//���Ի�ȷ��0x01������0x02
INT8U   TestOneEventAckOKNO(INT8U acktype,INT8U CmpType);

	//-------------------------------------------------
	//���������ơ� INT8U   TestOneEventNoAckSeqErr_Amt(INT8U acktype,INT8U CmpType)
	//���������ܡ� ����SEQ��0x03,���ظ�0x04
	//������˵����        
	//��I:	���롿   acktype��SEQ��0x03,���ظ�0x04�� CmpType�� 0 ʵ�ʣ�1ģ��
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
INT8U   TestOneEventNoAckSeqErr_Amt(INT8U acktype,INT8U CmpType);
//����acktype SEQ��0x03,���ظ�0x04  ; CmpType:0 ʵ�ʱ� 1 ����� 
INT8U   TestOneEventNoAckSeqErr(INT8U acktype,INT8U CmpType);
//���ַ��������
INT8U  TesMoreAddSetPa(void);
//���ַ���Ի�ȷ��0x01������0x02
INT8U   TestMoreEventAckOKNO(INT8U acktype,INT8U CmpType);
//���ַ����SEQ��0x03,���ظ�0x04
INT8U   TestMoreEventNoAckSeqErr(INT8U acktype,INT8U CmpType);
//	���ֻظ�����
INT8U   TestMoreEventPartNoAck(INT8U CmpType);
};

class CTESTEvent_M : public CWnd,public CEventPublic
{
	DECLARE_DYNAMIC(CTESTEvent_M)

public:
	CTESTEvent_M();
	virtual ~CTESTEvent_M();
	void C3762_TEST(HTREEITEM hTree);//����������
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
	INT8U  TestStaNoAck(void);
	INT8U  TestStaStaDataNoChang(void);
};


