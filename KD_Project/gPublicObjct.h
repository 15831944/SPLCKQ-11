#ifndef _gPUBLICOBJCT_H
#define _gPUBLICOBJCT_H

#include "User_Mcu_Cfg.h"

#define  RECV13762MAXDATA 2048

//#define  RECV13762MAXDATA 2500

#define  RECV64507MAXDATA 1024

#define  D_MaxNodeCnt   1024
extern INT8U  gNodeAddBuf[D_MaxNodeCnt][7];
extern INT16U gMaxNodeCnt;
extern INT8U m_HostNodeAddress[6];//���ڵ��ַ

extern int g_ConnectCCO;

#define DReadMeterMaxCnt 16
extern INT32U gReMeterDi[DReadMeterMaxCnt];

//97ģ���
#define DReadMeter97MaxCnt 9
 extern INT16U CDTL64597_DI[DReadMeter97MaxCnt];

 //����������
 #define DBinFangDiMaxCnt 16  
 extern INT32U gBinFangDi[DBinFangDiMaxCnt];

 #define DBinFang97DiMaxCnt 16
 extern INT16U gBinFang97Di[DBinFang97DiMaxCnt];
#endif