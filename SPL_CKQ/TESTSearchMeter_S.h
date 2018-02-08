#pragma once


// CTESTSearchMeter_S
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
class  CSearchAmtPublic
{
public:
protected:
	//allTime ����ʱ�� �� cnt �ط�����
INT8U StartSearchMeter(INT16U allTime,INT8U Cnt);
INT8U QueSearchResult(INT16U StartSeq,INT8U Cnt,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT16U &vdstAllCnt);
INT8U CmpStaOnSearchAmt(INT16U cmpSeq,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame);
INT8U CmpStaSearchAmt(INT16U StartSeq,INT16U Cnt,INT16U cmpSeq,INT16U CmpCnt);
INT8U CmpStaMacAmt(INT16U StartSeq,INT16U Cnt,INT16U cmpSeq,INT16U CmpCnt,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
//���Ի�ȷ��0x01������0x02,SEQ��0x03,���ظ�0x04
INT8U TestStaOnNetAckOKNo(INT8U  ackType );
INT8U  NodeSeqHardRst(INT16U vSrcSeq);
//����SEQ��0x03,���ظ�0x04
INT8U  TestStaOnNetAckOKNoNoAckSeqErr_Amt(INT8U acktype,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
//���Ի�ȷ��0x01������0x02,SEQ��0x03,���ظ�0x04
INT8U TestMoreOnStaNetAckType(INT8U vSrcCnt,INT8U  ackType );
INT8U CmpCjqMacAmt(INT16U StartSeq,INT8U Cnt,INT16U cmpSeq,INT8U CmpCnt,INT16U CjqBp,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
INT8U CmpCjqOnSearchAmt(INT16U CjqBp,INT16U cmpSeq,INT8U CmpCnt,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame);
//���Ի�ȷ��0x01������0x02,SEQ��0x03,���ظ�0x04
INT8U TestCjqOnNetAckOKNo(INT8U vSrcCnt,INT8U  ackType );
};
class CTESTSearchMeter_S : public CWnd,public CSearchAmtPublic
{
	DECLARE_DYNAMIC(CTESTSearchMeter_S)

public:
	CTESTSearchMeter_S();
	virtual ~CTESTSearchMeter_S();
	void C3762_TEST(HTREEITEM hTree);//����������
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
};


