#ifndef _USER_ACK_H
#define _USER_ACK_H
//�������Ͷ���
#define		DACK_SUCESS					0x00	//�ɹ�
#define DACK_EER_OVERTIME 				0xA0//ͨ�ų�ʱ
#define DACK_EER_INVALID 					0x01//��Ч���ݵ�Ԫ
#define	DACK_EER_LENERR						0x02//���ȴ���
#define	DACK_ERR_CS								0x03//У�����
#define	DACK_EER_NO_AFNFN					0x04//��Ϣ�಻����    DACK_EER_NO_AFNFN
#define	DACK_ERR_FORMAT						0x05//��ʽ����
#define	DACK_EER_METERREPEAT			0x06//����ظ�
#define	DACK_EER_METERNOFIND			0x07//��Ų�����
#define	DACK_EER_METERNOACK				0x08//���Ӧ�ò���Ӧ��
#define	DACK_EER_CCO_BUSY					0x09//���ڵ�æ					DACK_EER_CCO_BUSY
#define	DACK_EER_CCOCANNOTDO			0x0A//���ڵ㲻֧�ִ�����
#define	DACK_EER_STANOACK					0x0B//�ӽڵ���Ӧ��
#define	DACK_EER_STAOUTNET				0x0C//�ӽڵ㲻����
//������չ
#define	DACK_OVER376_2NUM					109//������󲢷���
#define	DACK_OVER645NUM						110//645���ĸ�������
#define	DACK_INREADING						111//�˱����ڳ�����

#define		DACK_FAILURE								19		//ʧ��
#define		DACK_ERR_NULL								20		//��֡����������13
#define		DACK_2_ERR_FAME							21		//֡���󣬳��ȣ��ٰ�֡
#define		DACK_ERR_BUF								22		//BUF����
#define		DACK_ERR_FULL								23		//BUF��
#define		DACK_ERR_MSG								24		//��Ϣ��һ��
#define		DACK_ERR_PRO								25		//����Ҫע��
#define		DACK_ERR_DELPRO							26		//����Ҫע��
#define		DACK_ERR_NODE_FULL					27		//�������
#define		DACK_ERR_NODE_NOFIND				28		//û���ҵ����
#define		DACK_ERR_NODE_ERR						29		//����쳣ĩ֪ԭ�򣬲�Ӧ�ó���Щ����
#define		DACK_ERR_RAM_ERR						30		//����쳣ĩ֪ԭ�򣬲�Ӧ�ó���Щ����
#define		DACK_EER_MNODE_FOMFATNOBCD	31		//��ӽڵ��BCD
#define		DACK_EER_MNODE_FOMFATBROAD	32		//��ӽڵ��ǹ㲥
#define		DACK_EER_MNODE_NOFIND				33		//��ӽڵ�û���ҵ�
#define		DACK_EER_MNODE_REPEAT				34		//��ӽڵ������
#define		DACK_EER_PCT								35		//Э�����
#define		DACK_EER_IN_LEN							36		//��������ĳ��Ȳ���
#define		DACK_EER_FLASH					  	37		//FALSH����
//#define		DACK_EER_CCO_BUSY	 					38		//CCOæ
#define		DACK_EER_HEADPORT						39		//PLC���ձ��ĵĶ˿ںŴ���
#define		DACK_EER_ID									40		//PLC���ձ��ĵ�ID����
#define		DACK_EER_HEADPCT				41		//PLC���ձ��ĵı���ͷ���Ȼ�Э��汾�Ŵ���
#define		DACK_EER_ACKSTA							42		//PLC���ձ��ĵĳ������б���Ӧ��״̬����
#define		DACK_EER_EVENTFUNC					43		//�¼��Ĺ��������
#define		DACK_EER_DIR								44		//���䷽�����
#define		DACK_EER_START							45		//��λ����
#define		DACK_EER_REGPA							46		//�ӽڵ�ע���������
#define		DACK_EER_DEVICETYPE					47		//��Ʒ���ʹ���
#define	    DACK_EER_CCOADD_REPEAT				48		//���ڵ��ַ�ظ�����
#endif

