/****************************************Copyright (c)**************************************************
**                                      �ն˲�Ʒ
**             
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: CDTL645.cpp
**��   ��   ��: ���
**����޸�����: 2006��6��7��
**��        ��:645Э�������
**              
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: ���
** ��  ��: v1.0
** �ա���: 2006��6��7��
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�------------------------------------------------------------------------------
**�� ��  ��: ���
**��     ��: 2006��6��7��
** �衡��: 
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#include "stdafx.h"
#include "CDTL645.h"
#include "CDTL2007.h"
#define    Max645ReadLen   200//���������
 //INT32U s_Di;//DI
 //INT8U  s_AmtBuf[6];//���ַ
 //INT8U  s_type;//����ģʽ��0����FE�� 1����4��FE
 INT8U CDTL645:: CodeReadData97Cmd(TH_IN const INT16U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData)
{
	CodeReadData97(pSrcDi,pSrcAmtAddBuf,vDstCmdData.s_pDstCmdBuf,vDstCmdData.s_vDstCmdLen,type);
	return DACK_SUCESS;
}
 void CDTL645:: CodeToAck97Data(struct Stu_Dtl2007 &Dtl2007Buf,const INT8U *vSrcBuf,const INT16U vSrcLen)
{
	CodeReadAckData97((INT16U)Dtl2007Buf.s_Di,Dtl2007Buf.s_AmtBuf,vSrcBuf,vSrcLen,Dtl2007Buf.s_pDstBuf,Dtl2007Buf.s_Len,0);
 }
void CDTL645:: CodeWriteData97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,const INT8U *pSrcBuf,const INT8U pSrcLen,INT8U *pDstBuf,INT8U &pDstLen,INT8U type)
{
 INT8U cs=0;
 INT8U i=0;
 INT8U j;
 INT8U temp;

 INT8U Di0,Di1;
 INT8U *tempbuf=pDstBuf;
 Di0=(INT8U)pSrcDi;
 Di1=(INT8U)(pSrcDi>>8);
 if(type==0)
{
 tempbuf[i++]=0xfe;
}
 cs+=0x68;
 tempbuf[i++]=0x68;
 for(j=0;j<6;j++)
 {
   cs+=pSrcAmtAddBuf[j];
   tempbuf[i++]=pSrcAmtAddBuf[j];
  }

  cs+=0x68;
 tempbuf[i++]=0x68;
  cs+=0x04;
 tempbuf[i++]=0x04;//������
  cs+=0x02+0x04+pSrcLen;
 tempbuf[i++]=0x02+pSrcLen+0x04;//����
 temp=Di0+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
 temp=Di1+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
  cs+=0x00+0x33;
 tempbuf[i++]=0x00+0x33;
   cs+=0x66+0x33;
 tempbuf[i++]=0x66+0x33;
   cs+=0x66+0x33;
 tempbuf[i++]=0x66+0x33;
   cs+=0x66+0x33;
 tempbuf[i++]=0x66+0x33;
 for(j=0;j<pSrcLen;j++)
  { 
    temp=pSrcBuf[j]+0x33;
    cs+=temp;
   tempbuf[i++]=temp;
  }
 tempbuf[i++]=cs;
 tempbuf[i++]=0x16;
 pDstLen=i;
}


	void CDTL645:: CodeReadData97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,INT8U *pDstBuf,INT8U &pDstLen,INT8U type)

{
 INT8U cs=0;
 INT8U i=0;
 INT8U *tempbuf;
 INT8U j;
 INT8U temp;
 INT8U Di0,Di1;
  tempbuf=pDstBuf;
 Di0=(INT8U)pSrcDi;
 Di1=(INT8U)(pSrcDi>>8);
 if(type==0)
{
 tempbuf[i++]=0xfe;
}
 cs+=0x68;
 tempbuf[i++]=0x68;
 for(j=0;j<6;j++)
 {
   cs+=pSrcAmtAddBuf[j];
   tempbuf[i++]=pSrcAmtAddBuf[j];
  }

  cs+=0x68;
 tempbuf[i++]=0x68;
  cs+=0x01;
 tempbuf[i++]=0x01;//������
  cs+=0x02;
 tempbuf[i++]=0x02;//����
 temp=Di0+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
 temp=Di1+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
 tempbuf[i++]=cs;
 tempbuf[i++]=0x16;
 pDstLen=i;

}

INT8U CDTL645::Decode64597(const INT8U *pSrcBuf,const INT16U pSrcLen,const INT8U vSrcDataLen,INT8U *pDstAmtAddBuf,INT16U &pDstDi,INT8U *pDstBuf,INT8U &pDstLen)
{
 
 INT8U cs=0;
 INT8U temp;

 INT32U i=0;
 INT32U j=0;
 INT8U con;
 INT8U ack=ACKNULL;
 INT8U len8;
 pDstDi=0x0000;

 pDstLen=0;
  if(pSrcLen<=Max645ReadLen)
  {
   if(pSrcLen>10)  //��ֹ����645������֡�����ĩ֪�ռ�,����ĩ֪����
   {
      ack=ACKFAMEERR;
     i=0;//���Խ�û�мӡ�i=0;�ǱȽ�Σ�յ�
   while(pSrcBuf[i++]!=0x68) 
   {
    if(i>pSrcLen) break;
   }
   if(i<pSrcLen)
   {
     cs+=0x68;
     if((i+10)<=pSrcLen) 
     {
      for(j=0;j<6;j++)
      {
       cs+=pSrcBuf[i];
       pDstAmtAddBuf[j]=pSrcBuf[i];
       i++;
      }
	  cs+=pSrcBuf[i];
	  if(pSrcBuf[i++]==0x68)
	  { 
	  con=pSrcBuf[i];//CON�������������Ƿ��к���֡.81�޺���֡,A1�к���֡,C1������
	  switch(con)
	  {
	   
	    case 0x81:
	    case 0xa1:
	    case 0x82:
	    case 0xa2:
	    
	        cs+=pSrcBuf[i++];
	        cs+=pSrcBuf[i];
	        if(pSrcBuf[i]>2)
	        {
	        pDstLen=pSrcBuf[i++]-2;//���ݳ��ȵĴ���
	        if(((pDstLen+14)<=pSrcLen)&&(pDstLen<=Max645DataLen)&&(pDstLen>0))//14�ǳ����������Ժ�ĳ���
	        {      
	         cs+=pSrcBuf[i];//DI0
	         temp=pSrcBuf[i++]-0x33;
	        cs+=pSrcBuf[i];//DI1
	        pDstDi=pSrcBuf[i++]-0x33;
	        pDstDi<<=8;
	        pDstDi|=temp;
	         for(j=0;j<pDstLen;j++)
	        {
	          cs+=pSrcBuf[i+j];
	   
	         }
	   
	         if((cs==pSrcBuf[i+j])&&(pSrcBuf[i+j+1]==0x16))
	         {
	             if((((pDstDi)&0x000f)==0x000f)&&((pDstDi)!=EBRCE))//������ĩβ��һ��0XAA�����롣���Լ�һ
		         {
		           if(pDstLen>1)
		           {
		           if(pSrcBuf[i+pDstLen-1]==0xdd)//��AAʱ�ż���Ϊ�˼��ݿ鲻��AA��β��
		            pDstLen=(pDstLen)-1;
		           }
		       
		         } 
	         
	             if(pDstLen>vSrcDataLen)//���ݻ��������Ȳ���������ǰ�벿�����ݣ�
	             {
	                pDstLen=vSrcDataLen;
	             }
		         for(j=0;j<pDstLen;j++)
		        {
		          pDstBuf[j]=pSrcBuf[i+j]-0x33;	
		         }
	    
	         
	        
	           ack=ACKTRUE;
	        
	         }
	        }
	        }
	        break;
	   default:  //ֻҪ֡��ʽ�Ծ�����Ч֡
	      //case 0xc1://�Ƕ�����֡����
	    //case 0xc2://����֡���쳣֡����
	    //case 0xc4://д���ݵ��쳣����,��ʱû�н����Ժ�����ݾ���,������һ�������ش�����
	               cs+=pSrcBuf[i++];//������
	               cs+=pSrcBuf[i];//����
	               len8=pSrcBuf[i];
	               i++;
	               if((i+len8+2)<=pSrcLen)
	               {
                    for(INT8U m=0;m<len8;m++)
                    {
                      cs+=pSrcBuf[i++];
                    }
	                if((cs==pSrcBuf[i])&&(pSrcBuf[i+1]==0x16))
	                {
	                 ack = ACKERR;
	                }
	               }
	                  
	               break;
	      }
	      }
	      }
	     }
	    }
	    else
	     ack=ACKNULL;
	   }
	  if(ack!= ACKTRUE)
	  {
	    pDstLen=0;
	    pDstDi=0x00;
	  } 
   /*   �Ȳ��ж�BCD��
	 if(ack==ACKTRUE)
	 { 
	  	   temp=Di>>12;
	       switch(temp)
	     {
	      case 0x09:
	      case 0x0A:
	      case 0x0B:
	          if(Check_Bcd(pDstBuf,pDstLen)==FALSE)
	            ack645=ACKERR;
	           break;
	      default:
	          break;
	        
	     }
	}
	*/
	  return ack;
 }
// INT8U CDTL645::AdjustTimeCode(const INT8U *buf,INT8U pSrcMaxLen,INT8U *tempbuf,INT8U &pDstLen,INT8U type)
//{
// INT8U cs=0;
// INT8U i=0;
// INT8U j;
// INT8U temp;
// INT8U ack=FALSE;
// pDstLen=0;
// if(pSrcMaxLen>50) 
//{
//if(type==0)
//{
// tempbuf[i++]=0xfe;
//}
// cs+=0x68;
// tempbuf[i++]=0x68;
// for(j=0;j<6;j++)
// {
//   cs+=0x99;
//   tempbuf[i++]=0x99;
//  }
//
//  cs+=0x68;
// tempbuf[i++]=0x68;
//  cs+=0x08;
// tempbuf[i++]=0x08;//������
//  cs+=0x06;
// tempbuf[i++]=0x06;//����
// 
// for(j=0;j<6;j++)
//  { 
//  if(j==4)
//    temp=(buf[4]&0x1f)+0x33;
//  else
//    temp=buf[j]+0x33;
//    cs+=temp;
//   tempbuf[i++]=temp;
//  }
// tempbuf[i++]=cs;
// tempbuf[i++]=0x16;
// pDstLen=i;
// ack=TRUE;
//}
// return ack;
//}
 INT8U CDTL645:: CheckAmtAdd97(const INT8U *pSrcAdd,const INT8U *pSrcRcvAdd)
{
 INT8U ack=TRUE;
 INT8U temp8;
 INT8U temp28;
 for(INT8U m=0;m<6;m++)
 {
   temp8=pSrcAdd[m]&0x0F;
   temp28=pSrcRcvAdd[m]&0x0F;
  if((temp8!=0x0A)&&(temp8!=temp28)&&(temp28!=0x0A))
   {
     ack=FALSE;
     break;
   }
   temp8=pSrcAdd[m]&0xF0;
    temp28=pSrcRcvAdd[m]&0xF0;
  if((temp8!=0xA0)&&(temp8!=temp28)&&(temp28!=0xA0))
   {
     ack=FALSE;
     break;
   }
 }
 return ack;
}
INT8U CDTL645::CheckFullFrame64597(const INT8U *pSrcBuf,const INT16U pSrcLen)//���֡�ĳ�������
{
  INT8U ack=FALSE;
  INT16U i=0;
  if(pSrcLen>10)  //��ֹ����645������֡�����ĩ֪�ռ�,����ĩ֪����
   {
    
     i=0;//���Խ�û�мӡ�i=0;�ǱȽ�Σ�յ�
   while(pSrcBuf[i]!=0x68) 
   {
     i++;
    if(i>=pSrcLen) break;
   }
   if(i<pSrcLen)
   {
     if((i+12)<=pSrcLen) 
     {
       i+=9;//ָ�򳤶�
      if((i+pSrcBuf[i]+2+1)<=pSrcLen)
        ack=TRUE;
	 }
   }
  }
 return ack;
}

//����û��Fe��ʽ
INT8U CDTL645:: CodeReadDataNoFe97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,INT16U vSrcLen,INT8U *pDstBuf,INT8U &pDstLen)

{
 INT8U cs=0;
 INT8U i=0;
 INT8U *tempbuf;
 INT8U j;
 INT8U temp;
 INT8U Di0,Di1;
 INT8U ack=FALSE;
 if(vSrcLen>14)
 {
  tempbuf=pDstBuf;
 Di0=(INT8U)pSrcDi;
 Di1=(INT8U)(pSrcDi>>8);
 cs+=0x68;
 tempbuf[i++]=0x68;
 for(j=0;j<6;j++)
 {
   cs+=pSrcAmtAddBuf[j];
   tempbuf[i++]=pSrcAmtAddBuf[j];
  }

  cs+=0x68;
 tempbuf[i++]=0x68;
  cs+=0x01;
 tempbuf[i++]=0x01;//������
  cs+=0x02;
 tempbuf[i++]=0x02;//����
 temp=Di0+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
 temp=Di1+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
 tempbuf[i++]=cs;
 tempbuf[i++]=0x16;
 ack=TRUE;
 }
 pDstLen=i;
 return ack;
}


//����㲥Уʱ����������+��ʱ�ĵĴ���
// INT8U CDTL645::Decode645AdjustTime(const INT8U *pSrcBuf,const INT16U pSrcLen,const INT16U vSrcDataLen,INT8U *pDstBuf,INT8U &pDstLen)
//{
// 
// INT8U cs=0;
// //INT8U temp;
//
// INT32U i=0;
// INT32U j=0;
// INT8U con;
// INT8U ack=ACKNULL;
// //INT8U len8;
// pDstLen=0;
//  if((pSrcLen<=Max645ReadLen)&&(pSrcLen>10))
//  {
//      ack=ACKFAMEERR;
//     i=0;//���Խ�û�мӡ�i=0;�ǱȽ�Σ�յ�
//   while(pSrcBuf[i++]!=0x68) 
//   {
//    if(i>pSrcLen) break;
//   }
//   if(i<pSrcLen)
//   {
//     cs+=0x68;
//     if((i+10)<=pSrcLen) 
//     {
//      for(j=0;j<6;j++)
//      {
//       cs+=pSrcBuf[i];
//       //pDstAmtAddBuf[j]=pSrcBuf[i];
//       i++;
//      }
//	  cs+=pSrcBuf[i];
//	  if(pSrcBuf[i++]==0x68)
//	  { 
//	   con=pSrcBuf[i];//CON�������������Ƿ��к���֡.81�޺���֡,A1�к���֡,C1������
//	   if(con==0x08)
//	   {
//		    cs+=pSrcBuf[i++];//������
//	        cs+=pSrcBuf[i];//����
//	        pDstLen=pSrcBuf[i];
//			i++;
//			if(pDstLen<=vSrcDataLen)
//			{
//			 for(j=0;j<pDstLen;j++)
//		        {
//		          pDstBuf[j]=pSrcBuf[i+j]-0x33;	
//		        }
//				 ack=ACKTRUE;
//			}
//			else
//			   pDstLen=0;
//	   }
//	 
//	   }
//	    }
//	   }
//	    
//	    }
//	    else
//	     ack=ACKNULL;
//	  
//	  if(ack!= ACKTRUE)
//	  {
//	    pDstLen=0;
//	 } 
// 
//	  return ack;
// }
INT8U CDTL645::CheckOk97(const INT8U *pSrcBuf,const INT8U pSrcLen)
{
 INT8U cs=0;
 //INT8U temp;
 INT32U i=0;
 INT32U j=0;
 INT8U con;
 INT8U ack=ACKERR;
  if(pSrcLen<=Max645ReadLen)
  {
   if(pSrcLen>10)  //��ֹ����645������֡�����ĩ֪�ռ�,����ĩ֪����
   {
    
     i=0;//���Խ�û�мӡ�i=0;�ǱȽ�Σ�յ�
   while(pSrcBuf[i++]!=0x68) 
   {
    if(i>pSrcLen) break;
   }
   if(i<pSrcLen)
   {
     cs+=0x68;
     if((i+10)<=pSrcLen) 
     {
      for(j=0;j<6;j++)
      {
       cs+=pSrcBuf[i];
       //pDstAmtAddBuf[j]=pSrcBuf[i];
       i++;
      }
	  cs+=pSrcBuf[i];
	  if(pSrcBuf[i++]==0x68)
	  { 
	  con=pSrcBuf[i];//CON�������������Ƿ��к���֡.81�޺���֡,A1�к���֡,C1������
	  switch(con)
	  {
	    case 0x84://д���ݵ�����Ӧ��
	    case 0x9d://д���ݵ�����Ӧ��
	    
	        cs+=pSrcBuf[i++];
	        cs+=pSrcBuf[i];
	        if(pSrcBuf[i]==0)
	        {
	          i++;
	          if((cs==pSrcBuf[i])&&(pSrcBuf[i+1]==0x16))
	           ack=ACKTRUE;
	          i++;
	          
	         }
	       
	        break;
	      
	      default:  ack = ACKERR;break;
	      }
	      }
	      }
	     }
	    }
	    else
	     ack=ACKNULL;
	   }
	 
	  return ack;
  
  }

void CDTL645:: CodeReadAckData97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,const INT8U *pSrcBuf,const INT16U pSrcLen,INT8U *pDstBuf,INT8U &pDstLen,INT8U type)
{
	INT8U cs=0;
	INT8U i=0;
	INT8U j;
	INT8U temp;

	INT8U Di0,Di1;
	INT8U *tempbuf=pDstBuf;
 Di0=(INT8U)pSrcDi;
 Di1=(INT8U)(pSrcDi>>8);
	if(type==0)
	{
		tempbuf[i++]=0xfe;
	}
	cs+=0x68;
	tempbuf[i++]=0x68;
	for(j=0;j<6;j++)
	{
		cs+=pSrcAmtAddBuf[j];
		tempbuf[i++]=pSrcAmtAddBuf[j];
	}

	cs+=0x68;
	tempbuf[i++]=0x68;
	cs+=0x04;
	tempbuf[i++]=0x04;//������
	cs+=0x02+0x04+pSrcLen;
	tempbuf[i++]=0x02+pSrcLen+0x04;//����
	temp=Di0+0x33;
	cs+=temp;
	tempbuf[i++]=temp;
	temp=Di1+0x33;
	cs+=temp;
	tempbuf[i++]=temp;
	for(j=0;j<pSrcLen;j++)
	{ 
		temp=pSrcBuf[j]+0x33;
		cs+=temp;
		tempbuf[i++]=temp;
	}
	tempbuf[i++]=cs;
	tempbuf[i++]=0x16;
	pDstLen=i;
}