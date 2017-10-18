#ifndef __LibExtern
#define __LibExtern

//#include "..\UserDefine\Define.h"
//#include "..\UserTarget\CClock.h" //�õ�TIME�ṹ.



typedef unsigned char  byte;                    //�޷���8λ����
typedef unsigned char b_flag;                   //�����ǰ��bit ����

typedef unsigned char  u_char;                    /* �޷���8λ���ͱ���                        */
typedef signed   char  s_char;                    /* �з���8λ���ͱ���                        */
//typedef unsigned short u_int;                     /* �޷���16λ���ͱ���                       */
typedef signed   short s_int;                     /* �з���16λ���ͱ���                       */
//typedef unsigned int   u_long;                    /* �޷���32λ���ͱ���                       */
typedef signed   int   s_long;                    /* �з���32λ���ͱ���                       */
typedef float    single_float;                    /* �����ȸ�������32λ���ȣ�                 */
typedef double   double_float;                    /* ˫���ȸ�������64λ���ȣ�                 */


extern u_long Hex_Change_BCD(u_long HexValue);
extern u_long Int_Change_BCD(u_int HexValue);
extern u_long BCD_Change_Hex(u_long BCDValue);
//extern u_int BCD_Change_Hex(u_int BCDValue);
//extern u_char Half_Char_Change_BCD(u_char HexValue);
extern u_int Char_Change_BCD(u_char HexValue);
extern u_long Adjust_BCD_Code(u_long HexValue);
extern void BCDValue_Add(u_long &BCDValue_Sum, u_long BCDValue_Data);
extern void BCDValue_Subb(u_long &BCDValue_Sub, u_long BCDValue_Data);
extern void SBCDValue_Subb(u_long &BCDValue_Sub, u_long BCDValue_Data);

extern bool CheckBCD(u_long Value);
extern bool CheckBCD(u_int Value);
extern bool CheckBCD(u_char Value);
extern u_int CalculateCRC(u_char *InputData, u_int DataLen); ///CRC16У��

#endif

