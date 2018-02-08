#pragma once


// CTESTSearchMeter_M
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
#include "TESTSearchMeter_S.h"
class CTESTSearchMeter_M : public CWnd,public CSearchAmtPublic
{
	DECLARE_DYNAMIC(CTESTSearchMeter_M)

public:
	CTESTSearchMeter_M();
	virtual ~CTESTSearchMeter_M();
	void C3762_TEST(HTREEITEM hTree);//����������
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
	INT8U TestInCmd(void);
	//	���ɼ����������������ѱ�ģ�⡿
    INT8U TestCjqNoNetList(INT8U vSrcCnt );
	//	�ɼ�������Ӧ��������ѯ��ֹͣ�ѱ����ģ�⡿
     INT8U TestCjqNoAck(void );
	 //	ȫSTA���ѱ���ԡ�ģ�⡿
      INT8U  TestSearchAllSta(INT16U vSrcCnt,INT8U ackType);
	  	 //	ȫ�ɼ������ѱ���ԡ�ģ�⡿
     INT8U  TestSearchAllCjq(INT16U vSrcCnt);
	 //	���ģʽ���ѱ���ԡ�ģ�⡿
	 INT8U  TestSearchStaCjq(INT16U vSrcCnt);
	 //ȫSTA��MAC��ַӰ����ԡ�ģ�⡿
	 INT8U  TestMACAllSta(INT16U vSrcCnt);
	 INT8U CmpMacIsOk(INT16U AmtBp,INT16U MacBp,INT32U WaitTimeS);
	 //ȫ�ɼ�����MAC��ַӰ����ԡ�ģ�⡿vSrcCntָ�ɼ���������ÿ��32ֻ
     INT8U TestMACAllCjq(INT16U vSrcCnt);
	 //1���ģʽ��MAC��ַӰ����ԡ�ģ�⡿
     INT8U TestMACStaCjq(INT16U vSrcCnt);
	 //MAC��ַ�ظ�Ӱ����ԡ�ģ�⡿
     INT8U TestMACRePeat(void);
};


