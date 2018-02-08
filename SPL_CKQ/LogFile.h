#pragma once

//#include "ImitateMeterDlg.h"
extern CFile cfileData;//�洢�ļ�
extern CFile cfileParse;//

#include "SimJZQ.h"
#include "SimMeter.h"
#include "Tools.h"
class CLogFile
{
public:
	CTools m_tools;
	CLogFile(void);
	~CLogFile(void);

	CString getAFNFnStr(unsigned char AFN, unsigned char fn);
	void dispSaveFixed1376FrameInfor(UINT8 apn,UINT8 fn,INT8U ctrl,INT8U *pRbuf,INT8 IO);
	void saveLog_HexBuf(INT8U logfile,INT8U IO,INT8U *pbuf,WORD length);//��ӡ֡16�����ַ���-�Դ�ʱ��
	void saveLog_str(INT8U logfile,INT8U time,CString str,INT8U LineType=0);//��ӡ�ַ���-��ѡ�Ƿ��ʱ��ʹ��ߵ�����
	void saveLog_err(INT8U logfile,INT8U time,CString str,INT8U ack,INT8U classType=0);//��ӡ������-��ѡ�Ƿ��ʱ��
	void saveInformation_send(sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);//��ӡ376.2����֡����ϸ��Ϣ ��ʱ��
	void saveInformation_rev(TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);//��ӡ376.2��֡����ϸ��Ϣ ��ʱ��
	void saveInformation_645(Stu_Dtl2007 stDtl2007);///��ӡ645֡�ṹ��Ϣ ��ʱ��
	void saveLog_testresult(INT8U logfile,INT8U time,CString str,INT8U ack,INT8U LineType=0);
	//classType ���ּ�����ʾ�ġ�ÿ������4��----
	void saveLog_testresult_AfnFn(INT8U Afn,INT16U Fn,INT8U logfile,INT8U time,CString str,INT8U ack,INT8U classType=0);
	void saveLog_StaCnt(INT16U  sucesscnt,INT16U failcnt,INT8U logfile,INT8U time,CString str,INT8U classType = 0);
	void saveLog_StaBuf8(INT8U  *vSrcBuf,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType=0);
	void  saveLog_StaBuf16(INT16U  *vSrcBuf,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType=0);
	void  saveLog_StaBuf32(INT32U  *vSrcBuf,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType=0);

	void saveLog_testresultAll(INT8U time,CString str,INT8U ack,INT8U classType =0);
	void saveLog_testresultALL_AfnFn(INT8U Afn,INT16U Fn,INT8U time,CString str,INT8U ack,INT8U classType=0);
	void saveLog_strAll(INT8U time,CString str,INT8U LineType);
	void  saveLog_BingF(INT8U logfile,INT8U time,CString str,sBinFa376_2_HostMsg BeifenMSg,INT8U classType=0);
	void  saveLog_NoAckMsg(INT8U logfile,INT8U time,CString str,sNoAckDiMsg  ackMsg,INT8U classType=0);
	void  saveLog_ClkSta(sAckTimeSta *timeclk376,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType=0);
};
 
extern INT8U ChangeAmtBps(INT32U bps);
extern INT32U  QueAmtBps(void);
extern void MessageBoxDelayTime(CString str,INT32U time);//�ӳٶԻ�����  δʵʱ��ʾ������