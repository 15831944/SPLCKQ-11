#pragma once


// CTESTInterChangEability_CCO
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
class CTESTInterChangEability_CCO : public CWnd
{
	DECLARE_DYNAMIC(CTESTInterChangEability_CCO)

public:
	CTESTInterChangEability_CCO();
	virtual ~CTESTInterChangEability_CCO();
	void C3762_TEST(HTREEITEM hTree);//����������
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
};


