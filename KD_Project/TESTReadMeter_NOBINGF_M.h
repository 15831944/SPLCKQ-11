#pragma once


// CTESTReadMeter_NOBINGF_M
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "TEST_ReadMeterPublic.h"
class CTESTReadMeter_NOBINGF_M : public CWnd,public CTEST_ReadMeterPublic
{
	DECLARE_DYNAMIC(CTESTReadMeter_NOBINGF_M)

public:
	CTESTReadMeter_NOBINGF_M();
	virtual ~CTESTReadMeter_NOBINGF_M();
	void C3762_TEST(HTREEITEM hTree);//����������
	void ClrComBuf();
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
};


