#ifndef _SIMJZQ_H
#define _SIMJZQ_H
#include "User_Mcu_Cfg.h"



#include "gPublicObjct.h"
#include "CDTL2007.h"
#include "CDTL645.H"
#include "SimMeter.h"
#include "Tools.h"
typedef struct 
{
 INT8U s_Seq;
 INT8U ackFg[16+1];
 INT8U di645cnt;
 INT32U di645Buf[16+1];
	
} sBinFa376_2_HostMsg;

typedef struct 
{
 INT8U s_Seq;
 INT8U ackFg;//�Ƿ񷵻� 1������
 INT8U dataack;//���ݸ�ʽ
 INT32U timeclk;
	
} sAckTimeSta;
class CSimJzq :public cDTL2007,public CDTL645
{
public:
	
// 	 CSimJzq(void);
// 	~CSimJzq(void);
public:
	CTools m_tools;
	INT8U * QueNodeBufAdd(INT16U vNodeBp);
	//�ӽڵ�Ӳ����λ
	INT8U NodeHardRst(INT8U *vSrcMacAdd);
	INT8U SearthMeterOpAFN06F4(INT32U famedly,INT16U bytedly,INT8U AckType,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	INT8U SearthMeterOpAFN06F2(INT32U famedly,INT16U bytedly,INT8U AckType,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	INT8U SetHostAdd(void);
	void ClrZjqComData(void);
	void SetMainAdd(INT8U * uMainAddress);
			  //-------------------------------------------------
	//���������ơ� INT8U CmpReSendCntTime(sNoAckDiMsg   AFNnoack,INT8U Cnt,INT32U MinTime,INT32U MaxTime);
	//���������ܡ�  �Ƚ��ش�����ʱ���Ƿ�ϸ�
	//������˵����     sNoAckDiMsg   AFNnoack��Cnt��������INT32U MinTime,INT32U MaxTime
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
	INT8U CmpReSendCntTime(sNoAckDiMsg   AFNnoack,INT8U Cnt,INT32U MinTime,INT32U MaxTime);
	INT8U  CmpDecode3762( sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_1,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2);
	INT8U  ZjqNoRcvData( INT32U nWaitFramTime , INT16U nWaiteByteTime);
	INT8U   QueAllNetSta(INT8U amtSeq,INT8U vSrcCnt,INT32U WaitTimeS);
		  //-------------------------------------------------
	//���������ơ� INT8U QueNetSta(INT8U *vSrcAmtBuf,INT32U WaitTimeS);
	//���������ܡ�  ��ѯ����״̬
	//������˵����        vSrcAmtBuf�����ַ  WaitTimeS�����ȴ�ʱ�䵥λ S
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
	INT8U QueNetSta(INT8U *vSrcAmtBuf,INT32U WaitTimeS);

	INT8U  AFN14F1ACK0001CmpAmt(INT32U amtseq,INT8U DiBp,INT8U AckType);
	INT8U  AFN14F1ACK0001(INT8U AckType);
	//-------------------------------------------------
	//���������ơ�TestReadMeterMoreAdd07(INT8U vSrcDiBp,INT8U DiCnt,INT8U AmtSeq,INT32U AmtCnt,INT32U TestCnt,INT8U CmpType=1)
	//���������ܡ� ���ַ����DI����
	//������˵����        
	//��I:	���롿    vSrcDiBp: Diλ�ƣ�DiCnt: Di������INT8U AmtSeqStart�� ���ַ���, AmtCnt����Ÿ��� INT32U TestCnt�����Դ�����  INT8U CmpType 0��ʵ�ʱ� 1ģ���
	//��O:	�����     
	//������ֵ	��    DACK_SUCESS;
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��9��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
    INT8U TestReadMeterMoreAdd07(INT8U vSrcDiBp,INT8U DiCnt,INT8U AmtSeq,INT32U AmtCnt,INT32U TestCnt,INT8U CmpType=1);
	
		//-------------------------------------------------
	//���������ơ� INT8U Test14ReadMeterOneAdd07MoreDi(INT8U vSrcDiBp,INT8U DiCnt,INT8U AmtSeq,INT32U TestCnt,INT8U CmpType=0);
	//���������ܡ� ����ַ����DI���ԣ��������
	//������˵����        
	//��I:	���롿   vSrcDiBp: Diλ�ƣ�DiCnt: Di������INT8U AmtSeqStart�� ���ַ���,  INT32U TestCnt�����Դ�����  INT8U CmpType 0��ʵ�ʱ� 1ģ���
	//��O:	�����     
	//������ֵ	��    DACK_SUCESS;
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��9��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
    INT8U Test14ReadMeterOneAdd07MoreDi(INT8U vSrcDiBp,INT8U DiCnt,INT8U AmtSeq,INT32U TestCnt,INT8U CmpType=0);

	//-------------------------------------------------
	//���������ơ�Test14ReadMeterOneAdd07(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U CmpType=1)
	//���������ܡ� ����ַ����DI����,���
	//������˵����        
	//��I:	���롿  INT8U AmtSeqStart�� ���ַ���,INT32U Di �� ����DI�� INT32U TestCnt�����Դ����� INT8U CmpType 0��ʵ�ʱ� 1ģ���
	//��O:	�����     
	//������ֵ	��    DACK_SUCESS;
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��9��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U Test14ReadMeterOneAdd07(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U CmpType=1);
	
	//-------------------------------------------------
	//���������ơ�INT8U  AFN14F1AllOPCmpAmt(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U AckType,INT8U CmpType);
	//���������ܡ� ����ַ����DI����,���
	//������˵����        
	//��I:	���롿 INT8U AmtSeqStart�� ���ַ���;INT32U Di �� ����DI; INT32U TestCnt�����Դ���; AckType: 0 ʧ�ܣ�1���ɹ���2������4���ظ�SEQ���� 
	//             INT8U CmpType 0��ʵ�ʱ� 1ģ���
	//��O:	�����     
	//������ֵ	��    DACK_SUCESS;
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��9��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U  AFN14F1AllOPCmpAmt(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U AckType,INT8U CmpType);


	INT8U  AFN14F1AllOPCmpAmtCon06F2(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U AckType,INT8U Afn06F2AckFg,INT8U CmpType);
		//-------------------------------------------------
	//���������ơ�AFN14F1AllOPAckAmt(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U *vDstAmtBuf,INT8U CmpType=1);
	//���������ܡ� ����ַ����DI����,���
	//������˵����        
	//��I:	���롿  nWaitFramTime��֡��ʱ, nWaiteByteTime���ֽ���ʱ  AckType: 0 ʧ�ܣ�1���ɹ���2������4���ظ�SEQ���� 
	//             vSrcPct: Э�����ͣ�vDstAmtBuf�����ر�ַ  INT8U CmpType 0��ʵ�ʱ� 1ģ���
	//��O:	�����     
	//������ֵ	��    DACK_SUCESS;
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��9��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U  AFN14F1AllOPAckAmt(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U *vDstAmtBuf,INT8U CmpType=1);
			//-------------------------------------------------
	//���������ơ� AFN14F1AllOPCon06F2(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U Afn06F2AckFg,INT8U CmpType=1);
	//���������ܡ� ����ַ����DI����,���
	//������˵����        
	//��I:	���롿  nWaitFramTime��֡��ʱ, nWaiteByteTime���ֽ���ʱ  AckType: 0 ʧ�ܣ�1���ɹ���2������4���ظ�SEQ���� 
	//             vSrcPct: Э�����ͣ�Afn06F2AckFg: 0: �����أ�1������ ��2 SEQ���쳣��vDstAmtBuf�����ر�ַ  INT8U CmpType 0��ʵ�ʱ� 1ģ���
	//��O:	�����     
	//������ֵ	��    DACK_SUCESS;
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��9��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U AFN14F1AllOPCon06F2(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U Afn06F2AckFg,INT8U CmpType=1);
		//-------------------------------------------------
	//���������ơ�INT8U AFN14F1AllOPAckAmtCon06F2(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U Afn06F2AckFg,INT8U *vDstAmtBuf,INT8U CmpType);
	//���������ܡ� ����ַ����DI����,���
	//������˵����        
	//��I:	���롿  nWaitFramTime��֡��ʱ, nWaiteByteTime���ֽ���ʱ  AckType: 0 ʧ�ܣ�1���ɹ���2������4���ظ�SEQ���� 
	//             vSrcPct: Э�����ͣ�vSrcDi�� ��DI��Afn06F2AckFg  : 06F2�ظ� 1�أ�0���أ�vDstAmtBuf�����ر�ַ  INT8U CmpType 0��ʵ�ʱ� 1ģ���
	//��O:	�����     
	//������ֵ	��    DACK_SUCESS;
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��9��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U AFN14F1AllOPAckAmtCon06F2(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U Afn06F2AckFg,INT8U *vDstAmtBuf,INT8U CmpType=1);

	INT8U  AFN14F1AllOP(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U CmpType=1);
	INT8U  CmpAFN14F1Data(INT8U *pSrcAddBuf,INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,INT8U CmpType=1);
	INT8U  SlaveAckAFN14F1(INT8U AckType,INT8U *pSrcAddBuf,INT32U Di,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	INT8U  SlaveSend376_2Buf(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	INT8U  SlaveSend376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	INT8U  CmpAckTimeClk(INT8U vSrcTimeAllCnt,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,INT8U ack,sAckTimeSta *timeclk376);
			//-------------------------------------------------
	//���������ơ�INT8U  CmpBinFenRcvMeter(INT8U *amtbuf,INT8U vSrcPctType,INT8U vSrc645Cnt,INT8U CmpDataFg,INT32U FameDly,INT32U ByteDly,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//���������ܡ�  �������Թ��� 
	//������˵����        
	//��I:	���롿    vSrcType�� 1��97��2 07��     amtbuf�����ַ    vSrc645Cnt��645֡�ĸ���.,INT32U vSrcAckFg �������з��ؽ����CmpDataFg�� �Ƿ�Ƚ�������ȷ .0ֻ��DI��1�����ݣ�ģ�����д˹��� INT32U FameDly֡��ʱ,INT32U ByteDly �ֽ���ʱ
	//��O:	�����     sBinFa376_2_HostMsg  &BinDownmsg,   INT32U &vDstFg  �ɹ���־
	//������ֵ	��    DACK_SUCESS;
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��9��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INT8U  CmpBinFenRcvMeter(INT8U *amtbuf,INT8U vSrcPctType,INT8U vSrc645Cnt,INT8U CmpDataFg,INT32U FameDly,INT32U ByteDly,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	INT8U  CmpDiIsOnDiBuf(INT32U Di,INT8U vSrcCnt,INT32U *DiBuf,INT8U &BpFg);
		//-------------------------------------------------
	//���������ơ�INT8U BinFenReadMeter(INT8U vSrcType,TH_IN  INT8U *amtbuf,INT8U vSrc645Cnt,INT32U vSrcAckFg,INT8U CmpDataFg,sBinFa376_2_HostMsg  &BinDownmsg,INT32U &vDstFg)
	//���������ܡ�  �������Թ��� 
	//������˵����        
	//��I:	���롿    vSrcType�� 1��97��2 07��     amtbuf�����ַ    vSrc645Cnt��645֡�ĸ���.,INT32U vSrcAckFg �������з��ؽ����CmpDataFg�� �Ƿ�Ƚ�������ȷ .0ֻ��DI��1�����ݣ�ģ�����д˹���
	//��O:	�����     sBinFa376_2_HostMsg  &BinDownmsg,   INT32U &vDstFg  �ɹ���־
	//������ֵ	��    DACK_SUCESS;
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��9��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INT8U BinFenReadMeter(INT8U vSrcType,TH_IN  INT8U *amtbuf,INT8U vSrc645Cnt,INT32U vSrcAckFg,INT8U CmpDataFg,sBinFa376_2_HostMsg  &BinDownmsg,INT32U &vDstFg);
	INT8U  QueMore645Fame(INT8U vSrcType,INT16U vSrcLen,INT8U *vSrcAmtBuf,INT8U cnt,INT8U *vDstBuf,INT16U &vDstLen,sBinFa376_2_HostMsg &ackHostMsg);
	void SendBufToCom(INT8U *vSrcBuf,INT16U vSrcLen);
	void BF_SendBufToCom(INT8U *vSrcBuf,INT16U vSrcLen);
	void SendHost3762ToCom(sPartQGDW376_2CreatFrame sQGDW376_2HostFrame);
	//-------------------------------------------------
	//���������ơ�void GetCOMM376_2ToBuf(INT16U  vSrcLen , INT16U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
	//���������ܡ�  �Ӵ��ڵõ�����376.2֡  
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

	  void GetCOMM376_2ToBuf(INT16U  getLen , INT32U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
	  void GetCOMMLENToBuf(INT16U  getLen , INT32U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
	  INT8U HostSendRcv376_2Buf_NoAck(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen);
	  INT8U HostSendRcv376_2NoBuf_NoAck(INT8U vSrcAFN,INT16U vSrcFn);
	  INT8U  HostSendRcv376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
	  INT8U  HostSendRcv376_2Buf(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
	  INT8U  HostSendRcv376_2MsgAddrBuf(INT8U vSrcCn,INT8U * vSrcMsgAddr,INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame, INT32U timeout = 10000,INT8U vSrcAckCmp = 0);
	  INT8U  HostSendRcv376_2BufNode(TH_IN const INT8U *pSrcAddBuf ,INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
	  INT8U  HostSend376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame );
	  INT8U  HostSend376_2Buf(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	  INT8U  HostRcv376_2( INT32U nWaitFramTime , INT16U nWaiteByteTime ,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	  INT8U  HostSendRcv376_2F0F8(TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	  INT8U  HostSendRcv376_2F0F8MsgAddrBuf(INT8U vSrcCn,INT8U * vSrcMsgAddr, TH_IN const INT8U *pSrcAddBuf, TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	  //-------------------------------------------------
	//���������ơ�  void Check376OP(void)
	//���������ܡ�  �Զ����376.2���ڵ�����
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
	
	  void Check376OP(void);


	//���������ơ� Wait3762Ack(INT16U nWaitFramTime , INT16U nWaiteByteTime,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//���������ܡ�  �ȴ�376.2�ķ���
	//������˵����        
	//��I:	���롿   famedly��֡��ʱ   bytedly���ֽ���ʱ DstDecodeDataFrame: ���ص�֡��Ϣ
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
	  INT8U  Wait3762Ack(INT32U nWaitFramTime , INT16U nWaiteByteTime,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);

	 //-------------------------------------------------
	//���������ơ�   INT8U  Wait3762AckCmpSeq(INT16U nWaitFramTime , INT16U nWaiteByteTime,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
	//���������ܡ�  �ȴ�376.2�ķ��أ����ж�֡����Ƿ�ȷ��
	//������˵����        
	//��I:	���롿   famedly��֡��ʱ   bytedly���ֽ���ʱ vSrcDi���·���645DI sQGDW376_2HostFrame�� �·���֡��Ϣ�� DstDecodeDataFrame: ���ص�֡��Ϣ
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
	  INT8U  Wait3762AckCmpSeq(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);

	  //-------------------------------------------------
	//���������ơ�   INT8U  Wait3762AckCmpAFNFN(INT16U nWaitFramTime , INT16U nWaiteByteTime,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
	//���������ܡ�  �ȴ�376.2�ķ��أ����ж�֡����Ƿ�ȷ,���жϣ�AFN��FN
	//������˵����        
	//��I:	���롿   famedly��֡��ʱ   bytedly���ֽ���ʱ vSrcDi���·���645DI sQGDW376_2HostFrame�� �·���֡��Ϣ�� DstDecodeDataFrame: ���ص�֡��Ϣ
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
	  INT8U  Wait3762AckCmpAFNFN(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	  INT8U  Wait3762AckCmpAFN(INT32U nWaitFramTime, INT16U nWaiteByteTime, sPartQGDW376_2CreatFrame sQGDW376_2HostFrame, TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	 //-------------------------------------------------
	//���������ơ�  INT8U Router_Stop(void)
	//���������ܡ�  ֹͣ·��
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
	  INT8U Router_Stop(void);
	  	  //-------------------------------------------------
	//���������ơ�  Router_Start(void)
	//���������ܡ�  ����·��
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
	  INT8U Router_Start(void);
	  	  //-------------------------------------------------
	//���������ơ�  INT8U Router_Resume(void)
	//���������ܡ�  �ָ�·��
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
	  INT8U Router_Resume(void);
	  	  //-------------------------------------------------
	//���������ơ�  Router_PaRst(void)
	//���������ܡ�  ��������λ
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
	  INT8U Router_PaRst(void);
	  	  //-------------------------------------------------
	//���������ơ�  void Router_DataRst(void)
	//���������ܡ�  ��������λ
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
	  INT8U Router_DataRst(void);
	  	  //-------------------------------------------------
	//���������ơ�  void RouterHardRst(void)
	//���������ܡ�  Ӳ����λ
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
	  INT8U RouterHardRst(void);

	 //-------------------------------------------------
	//���������ơ�  INT8U SetNodeAdd(INT16U vSrcBp,INT16U vSrcCnt);
	//���������ܡ�  ����ȫ��BUF�еĴӽڵ� ��vSrcBp��ʼ��vSrcCnt���ӽڵ�
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
	  INT8U SetNodeAdd(INT16U vSrcBp,INT16U vSrcCnt);
	  	 //-------------------------------------------------
	//���������ơ�  INT8U CmpNodeAdd(INT16U vSrcBp,INT16U vSrcCnt);
	//���������ܡ�  �Ƚ�ȫ��BUF�еĴӽڵ� ��vSrcBp��ʼ��vSrcCnt���ӽڵ�
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
	  INT8U CmpNodeAdd(INT16U vSrcBp,INT16U vSrcCnt);
	 //-------------------------------------------------
	//���������ơ�  INT8U QueNodeCnt(INT16U &vDstCnt);
	//���������ܡ�  ��ѯ�ӽڵ�����
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
	  INT8U QueNodeCnt(INT16U &vDstCnt);
	//-------------------------------------------------
	//���������ơ�  INT8U ReadMeterAFN02F1(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//���������ܡ�  AFN02F1�������ݣ����Ͳ�����376.2֡
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
	  INT8U ReadMeterAFN02F1(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
	  INT8U ReadMeterAFN02F1AckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U vSrcAckCmp=0);
	  	//-------------------------------------------------
	//���������ơ�   CodeReadMeterAFN02F1Cmd(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	//���������ܡ�  ��֡AFN02F1�������ݣ�û�з���
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
	  INT8U CodeReadMeterAFN02F1Cmd(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	  	//-------------------------------------------------
	//���������ơ�  INT8U ReadMeterAFN13F1(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//���������ܡ�  AFN13F1�������ݣ����Ͳ�����376.2֡
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
	  INT8U ReadMeterAFN13F1(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
	   INT8U ReadMeterAFN13F1AckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U vSrcAckCmp = 0);
	    	//-------------------------------------------------
	//���������ơ�   CodeReadMeterAFN02F1Cmd(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	//���������ܡ�  ��֡AFN13F1�������ݣ�û�з���
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
	  INT8U CodeReadMeterAFN13F1Cmd(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);

	  	  //-------------------------------------------------
	//���������ơ�  INT8U ReadMeterAFN02F1AndCmpMter(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//���������ܡ�  AFN02F1�������ݣ����Ͳ�����376.2֡�����ȽϺ�ģ��������һ�¡�
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

	  INT8U ReadMeterAFN02F1AndCmpMter(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=1);
	  INT8U ReadMeterAFN02F1AndCmpMterAckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U CmpType=1);
	  //-------------------------------------------------
	//���������ơ�  INT8U ReadMeterAFN13F1AndCmpMter(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//���������ܡ�  AFN13F1�������ݣ����Ͳ�����376.2֡�����ȽϺ�ģ��������һ�¡�
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
	   INT8U ReadMeterAFN13F1AndCmpMter(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=1);
	   INT8U ReadMeterAFN13F1AndCmpMterAckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U CmpType=1);
	//-------------------------------------------------
	//���������ơ� WaitReadMeterAFN02F1AckAndCmp((INT16U famedly,INT16U bytedly,TH_IN  INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
	//���������ܡ�  �ȴ�02F1�ķ��أ����ж�645��DI���ж����ݵ���ȷ�ԡ�Ӧ��֤����ʱ��ֵ���ܱ䡣
	//������˵����        
	//��I:	���롿   famedly��֡��ʱ   bytedly���ֽ���ʱ vSrcDi���·���645DI sQGDW376_2HostFrame�� �·���֡��Ϣ�� DstDecodeDataFrame: ���ص�֡��Ϣ
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
	   INT8U WaitReadMeterAFN02F1AckAndCmp(INT32U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=0);

	   //-------------------------------------------------
	//���������ơ� WaitReadMeterAFN13F1AckAndCmp((INT16U famedly,INT16U bytedly,TH_IN  INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
	//���������ܡ�  �ȴ�13F1�ķ��أ����ж�645��DI���ж����ݵ���ȷ�ԡ�Ӧ��֤����ʱ��ֵ���ܱ䡣
	//������˵����        
	//��I:	���롿   famedly��֡��ʱ   bytedly���ֽ���ʱ vSrcDi���·���645DI sQGDW376_2HostFrame�� �·���֡��Ϣ�� DstDecodeDataFrame: ���ص�֡��Ϣ
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
	   INT8U WaitReadMeterAFN13F1AckAndCmp(INT32U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=0);
    //-------------------------------------------------
	//���������ơ�  CodeReadMeter3762Cmd(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)
	//���������ܡ�  ��֡�������ݣ�û�з���
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
       INT8U CodeReadMeter3762Cmd(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);

	    //-------------------------------------------------
	//���������ơ�   ReadMeterAndCmpMter(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//���������ܡ�  �������ݣ����Ͳ�����376.2֡�����ȽϺ�ģ��������һ�¡�
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
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
	   INT8U  ReadMeterAndCmpMter(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=0);
	   INT8U  ReadMeterAndCmpMterAckClk(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U CmpType=0);


	   	    //-------------------------------------------------
	//���������ơ�   Read3762Meter(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//���������ܡ�  �������ݣ����Ͳ�����376.2֡.
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
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
	   INT8U  Read3762Meter(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	   INT8U  Read3762MeterAckClk(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta);


	   
   //-------------------------------------------------
	//���������ơ� INT8U  WaitReadMeterAckAndCmp(INT8U vSrcType,INT16U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//���������ܡ�  �ȴ�����ķ��أ����ж�645��DI���ж����ݵ���ȷ�ԡ�Ӧ��֤����ʱ��ֵ���ܱ䡣
	//������˵����        
	//��I:	���롿  vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,  famedly��֡��ʱ   bytedly���ֽ���ʱ vSrcDi���·���645DI sQGDW376_2HostFrame�� �·���֡��Ϣ�� DstDecodeDataFrame: ���ص�֡��Ϣ
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

	   INT8U  WaitReadMeterAckAndCmp(INT8U vSrcType,INT32U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=0);
	   	 //-------------------------------------------------
//���������ơ�CodeReadData9707Cmd(INT8U pcttype, TH_IN const INT32U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData)��
//���������ܡ�     //���������
//������˵����        
//��I:	���롿    pcttype  :0:  97 ,1: 07
//              	   INT32U s_Di;//DI
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
	   INT8U   CodeReadData9707Cmd(INT8U pcttype,TH_IN const INT32U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData);


	   INT8U  EventOp(INT32U famedly,INT16U bytedly,INT8U AckType,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U *vDstAmtBuf,INT8U CmpType);
#ifdef _STD_CSG  //������׼
		INT8U HostSendRcv376_2NoBuf_NoAck(INT8U vSrcAFN,INT32U vSrcFn);
		INT8U HostSendRcv376_2Buf_NoAck(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen);
		INT8U HostSendRcv376_2MsgAddrBuf(INT8U vSrcCn,INT8U * vSrcMsgAddr,INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
		INT8U HostSendRcv376_2Buf(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
		INT8U HostSendRcv376_2NoBuf(INT8U vSrcAFN,INT32U vSrcFn,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
		INT8U HostSendRcv376_2BufNode(TH_IN const INT8U *pSrcAddBuf, INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
		
		INT8U HostSendRcv376_2F0F8(TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
		INT8U HostSend376_2Buf(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQGDW376_2HostFrame);
		INT8U HostSend376_2NoBuf(INT8U vSrcAFN,INT32U vSrcFn,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame);
		INT8U HostRcv376_2( INT32U nWaitFramTime , INT16U nWaiteByteTime ,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
		void SendHost3762ToCom(sPartQCSG376_2CreatFrame sQCSG376_2HostFrame);
		INT8U   Wait3762Ack(INT32U nWaitFramTime , INT16U nWaiteByteTime,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
		INT8U   Wait3762AckCmpSeq(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQCSG376_2CreatFrame sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
		INT8U   Wait3762AckCmpAFNFN(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQCSG376_2CreatFrame sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
		INT8U CodeReadMeter3762Cmd(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame);
		INT8U CmpAckTimeClk(INT8U vSrcTimeAllCnt,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame,INT8U ack,sAckTimeSta *timeclk376);
		INT8U SlaveSend376_2Buf(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame);
		INT8U SlaveSend376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame);
		INT8U CmpDecode3762( sPartQCSG376_2DeCodeFrame DstDecodeDataFrame_1,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame_2);

#endif
};

#endif
