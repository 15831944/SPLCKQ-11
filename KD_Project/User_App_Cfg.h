#ifndef _USER_APP_H
#define _USER_APP_H
//--����
//--����
//--����
#include "User_Mcu_Cfg.h"
//#define DSYSCFGWORKTYPE_CCO 
#ifdef DSYSCFGWORKTYPE_CCO
//---ϵͳ����-----
const INT8U   SYSCFGWORKTYPE = 1;               //CCO ģʽ
#endif 

#ifdef DSYSCFGWORKTYPE_STA
const INT8U   SYSCFGWORKTYPE = 0;               //STAģʽ
#endif 

//#define ALIGN4BYTE(x)   (if(x%4)  (x) : (((x/4)+1)*4))
#define FLASH_SECTOR_CONTENT 4096
//--����
const INT16U	 FILETRAN_FINISH_WAIT_TIME		= 60;		//��λS ���������ȴ�ʱ�䣺�ն˷��������һ���������ݰ�����Ҫ�ȴ�ģ�����������ʱ�䳤��?
//---------�������----------
const INT16U	 READMETER_MAXDLY_TIME  = 60000; //��λMS
const INT16U	 PLCACK_MAXDLY_TIME  = 60000; //��λMS
const INT16U	 PLCFRAME_DLY_TIME =   5;//������ʱʱ�� ��λMS
const INT16U   FARME376_2_UARTBYTE_DLYTIME = 20 ;//�ֽ���ʱ ��λMS
const INT16U   FRAME376_2_UARTFRAME_DLYTIME=200;//֡��ʱ ��λMS?
const INT16U   FARME645_UARTBYTE_DLYTIME = 20 ;//�ֽ���ʱ ��λMS
const INT16U   FRAME645_UARTFRAME_DLYTIME=5000;//zz ����һ�� =200;//֡��ʱ ��λMS?
const INT8U    FRAME645_RESEND_MAXCNT    = 3;//645�ط���������
const INT16U   CFG_UART_WAITACK_MAXDLYTIME = 20;//MS ͨ�ô������ȴ�ʱ��// zz ����һ�� =20;//֡��ʱ ��λMS?
//--����----
const INT8U   CFG_READMETERPROCESS_MAXNUM = 16;//���֧�ֳ����������������13F1��02F1.
const INT8U   CFG_READMETERPROCESS_MODE   =  0;////����ģʽ  0����ʱ������ǰ�ģ���ʾ DACK_ERR_NODE_FULL�� 1����ʱҪ����ǰ��,��ʾ�ɹ���������ͳ�� 

//--����-------����ڶ���----------
const INT8U PORT_UART = 0x00;	//����
const INT8U PORT_PLC = 0x01;	//plc��
const INT8U PORT_CONSOLE = 0x02;	//����̨��
//-------------��ַ���ȶ���-----------
const INT8U		MAIN_ADD_LEN			= 6;
const INT8U		METER_ADD_LEN			= 6;
const INT8U   MAC_LEN  =  METER_ADD_LEN;
//const INT8U   DMACADD_LEN = MAC_LEN;
//------------ϵͳ��ؽ���--------------------

//------376.2֡����صĶ���----------
//--����
//const INT16U	 FRAME376_2_MAX_LEN		= 1200;		//���֧�ֵ�376.2���ĳ���
//const INT8U 	PARALLEL376_2_MAX_CNT = 13;     //��󲢷�֡����
//const INT8U 	PARALLEL645_MAX_LEN  = 40;     //����֡ 645ÿ֡�ظ�ƽ����󳤶�

//---645Э�鲿��---------------------
//--����
//const INT16U	 FRAME645_MAX_LEN	 = 254;
//const INT16U	 DATA645_MAX_LEN	 = FRAME645_MAX_LEN-16;//254-12(645��ʽ)-4(FE)

//----�ӽڵ�����¶���----
const INT16U	METERNODE_MAXNUME		= 1024;											//
//--����
const INT8U		METERNODE_ADDADD		= 0;	//�ӽڵ��ַ
const INT8U		METERNODE_ADDLEN		= METER_ADD_LEN;
const INT8U		METERNODE_PCTADD		= METERNODE_ADDADD+METERNODE_ADDLEN;	//Э��
const INT8U		METERNODE_PCTLEN		= 1;
const INT8U		METERNODE_CJQSEQADD		= METERNODE_PCTADD+METERNODE_PCTLEN;	//�ɼ�����seq
const INT8U		METERNODE_CJQSEQLEN		= 2;
const INT8U		METERNODE_DATALEN		= METERNODE_CJQSEQADD+METERNODE_CJQSEQLEN;	//�ӽڵ���flash�еĴ洢����	��ַ(6)+Э��(1)+crcУ��(1)
const INT8U		METERNODE_RESERVED		= 7;	//ÿ���ӽڵ��flashԤ��7�ֽ�,��flash��ַ����4�ֽڶ���
const INT16U	METERNODE_FLASHONELEN	= (METERNODE_DATALEN+METERNODE_RESERVED);	//ÿ���ӽڵ��flash����Ϊ16����flash��ַ����4�ֽڶ���
const INT16U	METERNODE_ONEFLASH_NUM	= (FLASH_SECTOR_CONTENT/METERNODE_FLASHONELEN);		//ÿ�������ɴ�Ĵӽڵ����
const INT8U		METERNODE_FALSHSECT		= ((METERNODE_MAXNUME/METERNODE_ONEFLASH_NUM)+1+1);	//��Ҫ����������
const INT8U		CRCLEN					= 2;

//�ɼ���flash����
const INT16U	CFG_CJQ_MAXNUME			= 1024;		//�ѵ��Ĳɼ�����������
const INT8U		CFG_CJQ_LIST_MAXNUM		= 32;	//�ɼ������ѱ��������

const INT8U		CJQFLASH_ADDADD			= 0;	//�ɼ�����ַ
const INT8U		CJQFLASH_ADDLEN			= METER_ADD_LEN;	//�ɼ�����ַ����
const INT8U		CJQFLASH_DATALEN		= CJQFLASH_ADDADD+CJQFLASH_ADDLEN;	//�ɼ����������ݳ���
const INT8U		CJQFLASH_RESERVED		= 2;
const INT16U	CJQFLASH_FLASHONELEN	= CJQFLASH_DATALEN+CJQFLASH_RESERVED;	//8���ֽ�
const INT16U	CJQFLASH_ONEFLASH_NUM	= (FLASH_SECTOR_CONTENT/CJQFLASH_FLASHONELEN);	//ÿ�������ɴ�Ĵӽڵ����
const INT8U		CJQFLASH_FALSHSECT		= ((CFG_CJQ_MAXNUME/CJQFLASH_ONEFLASH_NUM)+1+1);



//----------�ѱ�ģ��-----------------------------------------------------------
//--����
const INT32U  PA_SEARCHMETER_QUE_INVALTIME = 10;//��λ���ӣ� ��ѯ�ӽڼ�ע��״̬�ļ��ʱ��
const INT16U  PA_SEARCHMETER_ON_ReDly_TIME =300;//��λ MS AFN=06F2�ĵ�ȷ�ϵ��ʱ�䡣
const INT8U   PA_SEARCHMETER_ON_ReDly_NUM = 3;//AFN=06F2����ȷ�ϵ��ط�������
const INT8U   PA_SEARCHMETER_FORCRACKFG = 0;//���в�ѯ�ѱ����е�ǿ��Ӧ���־
//--����
const INT16U	CFG_SEARCHBLACK_MAXNUME    = 1024;	//�ѵ����������������������ڰ������Ĵӽڵ�
const INT16U	CFG_SEARCHMETER_MAXNUME		= 1024;		//�ѱ��������

const INT8U   PA_STA_SEARCH_MAXTIME = 120;//��λ���ӣ��ѱ���ʱ��
//--����
const INT8U   PRODUCTTYPE_METER  = 0; // ��Ʒ�����еĵ��
const INT8U   PRODUCTTYPE_CJQ  = 1;// ��Ʒ�����еĲɼ���

//const INT8U		SEARCHMETER_NODELEN		= 8;	//�ϱ��ӽڵ���Ϣ
//const INT8U		SEARCHMETER_CJQSEQ		= 2;
//const INT8U		SEARCHMETER_CARD_LEN	= SEARCHMETER_NODELEN+SEARCHMETER_CJQSEQ;
//const INT16U	SEARCHMETER_ONEFLASH_NUM= (FLASH_SECTOR_CONTENT/SEARCHMETER_CARD_LEN);	//ÿ�������ɴ�Ĵӽڵ����
//const INT8U		SEARCHMETER_FALSHSECT	= ((CFG_SEARCHMETER_MAXNUME/SEARCHMETER_ONEFLASH_NUM)+1);


const INT8U		SEARCHFLASH_STAADDADD		= 0;	//STA��ַ��flash�е���Ե�ַ
const INT8U		SEARCHFLASH_STAADDLEN		= METER_ADD_LEN;	//STA��ַ���� 6
const INT8U		SEARCHFLASH_METERCNTADD		= SEARCHFLASH_STAADDADD+SEARCHFLASH_STAADDLEN;	//STA�µ����������ַ
const INT8U		SEARCHFLASH_METERCNTLEN		= 1;	//STA�µ������������
const INT8U		SEARCHFLASH_STATYPEADD		= SEARCHFLASH_METERCNTADD+SEARCHFLASH_METERCNTLEN;	//STA���ͣ���ַ
const INT8U		SEARCHFLASH_STATYPELEN		= 1;	//STA���ͣ�0���ܱ�1�ɼ��� ����
const INT8U		SEARCHFLASH_METERADDADD		= SEARCHFLASH_STATYPEADD+SEARCHFLASH_STATYPELEN;	//STA�µ���ַ���� 6 ��ַ
const INT8U		SEARCHFLASH_METERADDLEN		= METER_ADD_LEN;	//STA�µ���ַ���� 6  ����
const INT8U		SEARCHFLASH_METERTYPEADD	= SEARCHFLASH_METERADDADD+SEARCHFLASH_METERADDLEN;	//STA�µ��Э������  ��ַ
const INT8U		SEARCHFLASH_METERTYPELEN	= 1;	//STA�µ��Э������	����
const INT8U		SEARCHFLASH_RESERVEDADD		= SEARCHFLASH_METERTYPEADD+SEARCHFLASH_METERTYPELEN;	//�ѱ�flash��������
const INT8U		SEARCHFLASH_RESERVEDLEN		= 1;	//�ѱ�flash��������

const INT8U		SEARCHFLASH_DATALEN			= SEARCHFLASH_RESERVEDADD;	//�ѱ�flash��Ч���ݳ���
const INT8U		SEARCHFLASH_ALLLEN			= SEARCHFLASH_DATALEN+SEARCHFLASH_RESERVEDLEN;	//�ѱ�flash�ܳ���

const INT16U	SEARCHFLASH_ONEFLASH_NUM	= (FLASH_SECTOR_CONTENT/SEARCHFLASH_ALLLEN);	//ÿ�������ɴ�Ĵӽڵ����
const INT8U		SEARCHFLASH_FALSHSECT		= ((CFG_SEARCHMETER_MAXNUME/SEARCHFLASH_ONEFLASH_NUM)+1);
//----------�ѱ�ģ��--end---------------------------------------------------------	


//-------�¼����-------------------------------------
const INT8U   CFG_CCO_EVENT_RECNT = 5;//STA�¼��ط��Ĵ���
const INT32U  CFG_CCO_EVENT_OK_WAITTIME = 30*60*1000;//30����
const INT8U   CFG_CCOEVENT_MAXNUM = 30;//���֧�ֽ�����
const INT8U   CFG_CCOEVENT_MODE = 0;////����ģʽ  0����ʱ������ǰ�ģ���ʾ DACK_ERR_NODE_FULL�� 1����ʱҪ����ǰ��,��ʾ�ɹ���������ͳ�� 
const INT8U   CFG_CCOEVENT_REPORTMAXNUM = 60;//���֧�ֽ�����

const INT8U   CFG_STA_EVENT_RECNT = 5;//STA�¼��ط��Ĵ���
const INT32U   CFG_STA_EVENT_MAX_WATITIME = 60*1000;//������S��STA�¼� �ȴ�PLCȷ�ŵ��¼�
const INT32U   CFG_STA_EVENT_ONE_WATITIME = 20*1000;// 20S STA�¼��ط��Ĵ�������ȴ�PLCȷ�ŵ��¼�


//-------------------------------------------------------
//-----------PLCͨ�����------------------
//--����
const INT8U PA_PLC_INVAL_TIME = 20;		//��λ MS ��PLC�������ݼ��ʱ�䣬
const INT8U PA_PLC_DATA_HEAD_LEN = 22;		//��PLC���� ���� ���ݽṹ ͷ ����
//-----------PLCAPPЭ�� ���------------------
//--����
//--����
const INT8U PLCAPPPCT_TIMEOUT = 10;		//�������б��ĳ�ʱʱ�䣬��λ100ms,���ݶ�1s=100*10
const INT8U PLCAPPPCT_MULTIME = 10;		//�������б��Ĳ������ļ��ʱ�䣬��λ10ms,���ݶ�100ms��10*10
//--����
const INT8U PLCAPPPCT_HEADPORT = 0x10;	//plcЭ��ͷ�˿ںŹ̶�Ϊ0x10
const INT8U PLCAPPPCT_HEADCON = 0x00;	//plcЭ��ͷ�����̶ֹ�Ϊ0x00
const INT8U PLCAPPPCT_NUM = 1;			//Э��汾�����ڶ���1
const INT32U	PLCAPPPCT_RESERVED		= 0;		//����λ��д0
const INT32U	PLCAPPPCT_QUEREGPA		= 0;		//��ѯ�ӽڵ�ע���еĴӽڵ�ע�����
const INT32U	PLCAPPPCT_STARTREGPA	= 1;		//�𶯴ӽڵ�ע���еĴӽڵ�ע�����
const INT32U	PLCAPPPCT_FORCEACK		= 0;		//�𶯴ӽڵ�ע���е�ǿ��Ӧ���־
const INT8U		PLCAPPPCT_ACKSTA		= 0;		//�������б���Ӧ��״̬
const INT8U		PLCAPPPCT_PCT_TRANSMIT	= 0;		//͸������
const INT8U		PLCAPPPCT_PCT_97		= 1;		//97
const INT8U		PLCAPPPCT_PCT_07		= 2;		//07
const INT8U		PLCAPPPCT_EVENTOKDOWN	= 1;		//�¼����������У�CCOӦ��ȷ�ϸ�STA
const INT8U		PLCAPPPCT_EVENTENDOWN	= 2;		//�¼����������У�CCO�����¼������ϱ���STA
const INT8U		PLCAPPPCT_EVENTSTOPDOWN	= 3;		//�¼����������У�CCO��ֹ�¼������ϱ���STA
const INT8U		PLCAPPPCT_EVENTFULLDOWN	= 4;		//�¼����������У�CCO����������STA
const INT8U		PLCAPPPCT_EVENTUP		= 1;		//�¼����������У�STA�����ϱ��¼���CCO
const INT8U		PLCAPPPCT_METER			= 0;		//���ܱ�
const INT8U		PLCAPPPCT_COLLECTOR		= 1;		//�ɼ���
const INT8U		PLCAPPPCT_EVENTDIR		= 0;		//�¼����з���λ

//-----CCO���-----------------------------------------
//--����
const INT8U		CCOPAMSGRESERVED		= 16;		//CCO��������flashʱԤ��16�ֽ�
//--����------AFN03-F10----------
const INT8U AFN03F10_MAX_INVAL_TIME = 2;		//AFN03,F10�ϱ��޷��أ��ط��ļ��ʱ��  S
const INT8U AFN03F10_MAX_INVAL_NUN = 1;		//AFN03,F10�ϱ��޷��أ� ����ط�����
//--����
const INT8U AFN03F10_MAX_DATA_LEN = 41;	//AFN03,F10�ϱ����ݵĳ���
const INT8U AFN14F1_MAX_REQ_CNT = 3;
//--����------���ڵ�״̬�ֺ�ͨ������
const INT8U   CCOSTAWORD_RATENUM = 1;//��������n
const	INT8U   CCOSTAWORD_CHANNELTYPE = 2;//���ڵ��ŵ�������0��ʾ΢�������ߣ�1��ʾ���๩�絥�ഫ�䣻2��ʾ���๩�����ഫ�䣻3��ʾ���๩�����ഫ�䡣
const	INT8U   CCOSTAWORD_METERTYPE = 0;//���ڳ���ģʽ��00��ʾͨ��ģ������ֳ���ģʽ��֧�֣�01��ʾͨ��ģ���֧�ּ����������ĳ���ģʽ?
																			    //10 ��ʾͨ��ģ���֧��·�������ĳ���ģʽ��
const	INT8U   CCOSTAWORD_CHANNELNUM = 1;  //�ŵ�����
const	INT16U  CCOSTAWORD_METERRATE = 0;//ͨ�����ʣ���ʾͨ�Ų����ʣ�BIN��ʽ��0��ʾĬ��ͨ�����ʡ�
const	INT8U   CCOSTAWORD_METERRATEUNIT = 0;//���ʵ�λ��
const	INT8U   CCODISTURBSTA = 0;//ע������״̬��0��ʾû�и��ţ�1��ʾ�и��š�Lu_խ��������û��

//--����-----ͨ��----------------
const INT8U		ONLINEFG				= 1;		//�����߱�־�е�����
const INT8U		OFFLINEFG				= 2;		//�����߱�־�е�����


#endif

