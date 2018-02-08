#include "StdAfx.h"
#include "LogFile.h"


#include "SPL_CKQ.h"
#include "MainFrm.h"
#include "Tools.h"
CLogFile::CLogFile(void)
{
}


CLogFile::~CLogFile(void)
{
}
char *ReservedStr = "����";
char *AFNStrBuf[AFN_MAX_NUM]=
{
	"ȷ�ϨM����",
	"��ʼ��",
	"����ת��",
	"��ѯ����",
	"��·�ӿڼ��",
	"��������",
	"�����ϱ�",//0x06
	// 7    8       9		10		11	12		13		14
	"����","����","����","����","����","����","����","����","����",

	"·�ɲ�ѯ",
	"·������",
	"·�ɿ���",
	"·������ת��",
	"·�����ݳ���",
	"�ļ�����",//0x15

	"�ڲ�����",//���һ���ַ��� ��ӦAFNF0
};

char *AFN00FnStrBuf[]={"F1��ȷ��","F2������"};
char *AFN01FnStrBuf[]={"F1��Ӳ����ʼ��","F2����������ʼ��","F3����������ʼ��"};
char *AFN02FnStrBuf[]={"F1������ת��"};
char *Apn03FnStrBuf[]={"F1�������ڵ�汾��Ϣ","F2����ȡ����ֵ","F3����ȡ�ӽڵ�������Ϣ","F4����ȡ���ڵ��ַ","F5�����ڵ�״̬�ֺ�ͨ������","F6�����ڵ����״̬","F7����ȡ�ӽڵ������ʱʱ��","F8����ѯ����ͨ�Ų���","F9��ͨ����ʱ��ع㲥ͨ��ʱ��","F10����ȡ����ͨ��ģ������ģʽ��Ϣ","F11������ͨ��ģ��������Ϣ"};
char *AFN04FnStrBuf[]={"F1�����Ͳ���","F2���ӽڵ���","����ģ��F3������ͨ�Ų���"};
char *Apn05FnStrBuf[]={"F1���������ڵ��ַ","F2�������ֹ�ӽڵ��ϱ�","F3�������㲥","F4�����ôӽڵ������ʱʱ��","F5����������ͨ�Ų���"};
char *AFN06FnStrBuf[]={"F1���ϱ��ӽڵ���Ϣ","F2���ϱ���������","F3���ϱ������䶯��Ϣ","F4���ϱ��ӽڵ���Ϣ���豸����","F5���ϱ��ӽڵ��¼�"};
char *AFN10FnStrBuf[]={"F1���ӽڵ�����","F2���ӽڵ���Ϣ","F3��ָ���ӽڵ����һ���м�·����Ϣ","F4��·������״̬","F5��δ�����ɹ��Ĵӽڵ���Ϣ","F6������ע��Ĵӽڵ���Ϣ","F21:�ڵ�������Ϣ","F100:��ѯ�����ģ","F101:��ѯ�ӽڵ�汾��Ϣ","F201:��ѯ�ӽڵ�״̬"};
char *AFN11FnStrBuf[]={"F1����Ӵӽڵ�","F2��ɾ���ӽڵ�","F3�����ôӽڵ�̶��м�·��","F4�����ù���ģʽ","F5������ӽڵ�����ע��","F6����ֹ�ӽڵ�����ע��"};
char *Apn12FnStrBuf[]={"F1��·������","F2��·����ͣ","F3��·�ɻָ�"};
char *AFN13FnStrBuf[]={"F1����شӽڵ�"};
char *AFNF0FnStrBuf[]={"F100:��ȡFLASH����"};

CFile cfileData;//�洢�ļ�
CFile cfileParse;//


void CLogFile::dispSaveFixed1376FrameInfor(UINT8 apn,UINT8 fn,INT8U ctrl,INT8U *pRbuf,INT8 IO)
{
	CString str,str1;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	if (IO == OUTPUT)
	{
		str += _T("->>>>-����-��������:");	
	} 
	else
	{
		str += _T("-<<<<-����-��������:");	
	}
	str1.Format(_T("������%.2x,��Ϣ��%.2x %.2x %.2x %.2x %.2x %.2x"),ctrl,pRbuf[0],pRbuf[1],pRbuf[2],pRbuf[3],pRbuf[4],pRbuf[5]);
	str += str1 + getAFNFnStr(apn,fn);
	saveLog_str(DATA_FILE,NOTIME,str);
}

#if 0
void CLogFile::saveLog_HexBuf(INT8U logfile,INT8U IO,INT8U *pbuf,WORD length)//��ӡ����֡��16�����ַ���
{
	char szANSIString[5000];  
	CString str,strfile;
	CString strA;
	SYSTEMTIME st;
	FILE * file;
	char * pFileName = new char[256];
	GetLocalTime(&st);
	str = _T(".\\��־\\DataFile-");
	strfile.Format(_T("%.4d��%.2d��%.2d��"),st.wYear,st.wMonth,st.wDay);
	strA = str + strfile + _T(".txt");
	str.Format(_T("%.2d:%.2d:%.2d.%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	str += ((IO == OUTPUT)?_T("->>>>-����-"):_T("-<<<<-����-")) + m_tools._buf16tostr16(pbuf,length,true) + _T("\r\n")+ _T("\r\n");
	

	USES_CONVERSION;
	pFileName = T2A(strA.GetBuffer(0));
	
	m_tools.AutoMakedir(pFileName);
	
	file=fopen(pFileName,"r");
	if  ( file == NULL )
	{
		file=fopen(pFileName,"a+");
		if (file != NULL)
		{
			fwrite(szANSIString, wcslen(str), 1, file);
			fclose(file);
		}
	}
	else
	{
		fclose(file); 
		file=fopen(pFileName,"a+");
		if (file != NULL)
		{
			fwrite(szANSIString, wcslen(str), 1, file);
			fclose(file);
		}
	}
	delete[] pFileName;
}
#else

void CLogFile::saveLog_HexBuf(INT8U logfile, INT8U IO, INT8U *pbuf, WORD length)//��ӡ����֡��16�����ַ���
{
	char szANSIString[5000];
	CString str, strfile;
	CStringA strA;
	SYSTEMTIME st;
	FILE * file;
	GetLocalTime(&st);
	str = _T(".\\��־\\DataFile-");
	strfile.Format(_T("%.4d��%.2d��%.2d��"), st.wYear, st.wMonth, st.wDay);
	strA = str + strfile + _T(".txt");
	str.Format(_T("%.2d:%.2d:%.2d.%.3d"), st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	str += ((IO == OUTPUT) ? _T("->>>>-����-") : _T("-<<<<-����-")) + m_tools._buf16tostr16(pbuf, length, true) + _T("\r\n") + _T("\r\n");

	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, str, -1, szANSIString, sizeof(szANSIString), NULL, NULL);
	file = fopen(strA, "r");
	if (file == NULL)
	{
		file = fopen(strA, "a+");
		if (file != NULL)
		{
			fwrite(szANSIString, wcslen(str), 1, file);
			fclose(file);
		}
	}
	else
	{
		fclose(file);
		file = fopen(strA, "a+");
		if (file != NULL)
		{
			fwrite(szANSIString, wcslen(str), 1, file);
			fclose(file);
		}
	}
}

#endif

//void CLogFile::saveLog_HexBuf(INT8U logfile,INT8U IO,INT8U *pbuf,WORD length)//��ӡ����֡��16�����ַ���
//{
//	// TODO: Add your command handler code here	
//	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString str,strTemp;
//	CTools m_tool;
//	SYSTEMTIME st;
//	GetLocalTime(&st);
//	str.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
//	str += ((IO == OUTPUT)?_T("->>>>-����-"):_T("-<<<<-����-"));
//
//
//	if (cfileData.m_hFile != CFile::hFileNull)
//	{
//		cfileData.Write(str,str.GetLength());
//	}			
//	//pMainDlg->m_flashData.ReplaceSel(str);//�༭����ʾ		
//	str = m_tool._buf16tostr16(pbuf,length,true);
//	str += _T("\r\n");
//	if (logfile == DATA_FILE)
//	{
//		if (cfileData.m_hFile != CFile::hFileNull)
//		{
//			cfileData.Write(str.GetString(),str.GetLength());
//		} 
//		//pMainDlg->m_flashData.ReplaceSel(str);//�༭����ʾ
//	}
//	else if (logfile == PARS_FILE)
//	{
//		if  (cfileParse.m_hFile != CFile::hFileNull)
//		{
//			cfileParse.Write(str.GetString(),str.GetLength());
//		}
//		//pMainDlg->m_editKeyMsg.ReplaceSel(str);//�༭����ʾ
//	}
//
//	//if(pMainDlg->m_flashData.GetWindowTextLength() > 20480)//��ս���
//	//{
//	//	pMainDlg->m_flashData.SetSel(0,-1);
//	//	pMainDlg->m_flashData.Clear();
//	//}
//	//if(pMainDlg->m_editKeyMsg.GetWindowTextLength() > 20480)//��ս���
//	//{
//	//	pMainDlg->m_editKeyMsg.SetSel(0,-1);
//	//	pMainDlg->m_editKeyMsg.Clear();
//	//}
//	//}
//
//}

void CLogFile::saveLog_str(INT8U logfile,INT8U time,CString str,INT8U LineType)
{
	// TODO: Add your command handler code here	
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString line;
	if (LineType==0)
	{
		line="";
	}
	else if (LineType==1)
	{
		line="----------------------------------------\r\n";
	}
	else if (LineType==2)
	{
		line="======================================================================\r\n";
	}

	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += ("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	if (logfile == DATA_FILE)
	{
		strTemp+=str;
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(line,line.GetLength());
			cfileData.Write(strTemp,strTemp.GetLength());
			//cfileData.Write(line,line.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel("\r\n"+line+strTemp+line);//�༭����ʾ		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+=str;
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(line,line.GetLength());
			cfileParse.Write(strTemp,strTemp.GetLength());
			//cfileParse.Write(line,line.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel("\r\n"+line+strTemp);//�༭����ʾ		
	}

	//if(pMainDlg->m_flashData.GetWindowTextLength() > 40960)//��ս���
	//{
	//	pMainDlg->m_flashData.Clear();
	//}
	//if(pMainDlg->m_editKeyMsg.GetWindowTextLength() > 40960)//��ս���
	//{
	//	pMainDlg->m_editKeyMsg.Clear();
	//}


}
void CLogFile::saveLog_err(INT8U logfile,INT8U time,CString STR,INT8U ack,INT8U classType)
{
	// TODO: Add your command handler code here	
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Format(_T("%02x"),ack);
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+="----";
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += ("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=STR+_T("�����룺")+str;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//�༭����ʾ		

	}
	else if (logfile == PARS_FILE)//DataIfo
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);//�༭����ʾ		
	}

}
void CLogFile::saveInformation_send(sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)//����ӡ֡����ϸ��Ϣ
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	UINT8 a_Fn;//=(UINT8)sQGDW376_2HostFrame.s_head.s_FN;
	INT8U pRbuf[6]={0,0,0,0,0,0};//����Ϣ��
	INT8U S;
	ST_Fn pstFn;
	S=(UINT8)(sQGDW376_2HostFrame.s_head.s_FN);
	(&pstFn)->DT1=S;
	(&pstFn)->DT2=sQGDW376_2HostFrame.s_head.s_FN>>8;
	a_Fn=pMainDlg->getFn(pstFn);//ȡFn�ַ���
	for (int i=0;i<5;i++)
	{
		pRbuf[i]=sQGDW376_2HostFrame.s_head.u_msg.s_msgbuf[i];
	}
	pRbuf[5]=sQGDW376_2HostFrame.s_head.s_Msg_Seq;
	dispSaveFixed1376FrameInfor(sQGDW376_2HostFrame.s_head.s_AFN,a_Fn,sQGDW376_2HostFrame.s_head.u_con.s_conByte,pRbuf,OUTPUT);
}

void CLogFile::saveInformation_rev(TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	UINT8 a_Fn;//=(UINT8)sQGDW376_2HostFrame.s_head.s_FN;
	INT8U pRbuf[6]={0,0,0,0,0,0};
	INT8U S;
	ST_Fn pstFn;
	S=(UINT8)(DstDecodeDataFrame.s_head.s_FN);
	(&pstFn)->DT1=S;
	(&pstFn)->DT2=DstDecodeDataFrame.s_head.s_FN>>8;
	a_Fn=pMainDlg->getFn(pstFn);
	for (int i=0;i<5;i++)
	{
		pRbuf[i]=DstDecodeDataFrame.s_head.u_msg.s_msgbuf[i];
	}
	pRbuf[5]=DstDecodeDataFrame.s_head.s_Msg_Seq;
	dispSaveFixed1376FrameInfor(DstDecodeDataFrame.s_head.s_AFN,a_Fn,DstDecodeDataFrame.s_head.u_con.s_conByte,pRbuf,INPUT_DATA);

}

void CLogFile::saveInformation_645(Stu_Dtl2007 stDtl2007)///��ӡ645֡�ṹ��Ϣ
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str,str1;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	//INT8U  s_Con;//������
	str1.Format(_T("������:%.2x,DI:%.2x %.2x %.2x %.2x,���ַ:%.2x %.2x %.2x %.2x %.2x %.2x"),stDtl2007.s_Con,stDtl2007.s_Di,stDtl2007.s_Di>>8,stDtl2007.s_Di>>16,stDtl2007.s_Di>>24,stDtl2007.s_AmtBuf[0],stDtl2007.s_AmtBuf[1],stDtl2007.s_AmtBuf[2],stDtl2007.s_AmtBuf[3],stDtl2007.s_AmtBuf[4],stDtl2007.s_AmtBuf[5]);
	str += str1+_T("\r\n");
	saveLog_str(DATA_FILE,TIME,str);
}


CString CLogFile::getAFNFnStr(unsigned char AFN, unsigned char fn)
{
	CString str,FnStr;
	char *pbuf;
	if(AFN == AFNF0)		pbuf = AFNStrBuf[AFN_MAX_NUM-1];
	else if(AFN <= 0x15)	pbuf = AFNStrBuf[AFN];
	else					pbuf = ReservedStr;

	str.Format(_T("AFN=%.2XH:%s,"),AFN,pbuf);
	if (AFN == AFN00)
	{
		if (fn <= F2)FnStr.Format(_T("%s,"),AFN00FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr); 
	}else if (AFN == AFN01)
	{
		if (fn <= F3)FnStr.Format(_T("%s,"),AFN01FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN02)
	{
		if (fn <= F1)FnStr.Format(_T("%s "),AFN02FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s "),ReservedStr);
	}else if (AFN == AFN03)
	{
		if (fn <= F11)FnStr.Format(_T("%s,"),Apn03FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN04)
	{
		if (fn <= F3)FnStr.Format(_T("%s,"),AFN04FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN05)
	{
		if (fn <= F6)FnStr.Format(_T("%s,"),Apn05FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN06)
	{
		if (fn <= F5)FnStr.Format(_T("%s,"),AFN06FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN10)
	{
		if (fn==21)
		{
			fn=7;
		}
		if (fn==100)
		{
			fn=8;
		}
		if (fn==101)
		{
			fn=9;
		}
		if (fn==102)
		{
			fn=10;
		}
		if (fn <= F201)FnStr.Format(_T("%s,"),AFN10FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN11)
	{
		if (fn <= F6)FnStr.Format(_T("%s "),AFN11FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s "),ReservedStr);
	}else if (AFN == AFN13)
	{
		if (fn <= F1)FnStr.Format(_T("%s "),AFN13FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s "),ReservedStr);
	}
	else if (AFN == AFNF0)
	{
		if (fn <= F100)	FnStr.Format(_T("%s "),AFNF0FnStrBuf[0]); 
		else			FnStr.Format(_T("%s "),ReservedStr);
	}else			 FnStr.Format(_T("%s "),ReservedStr);
	
	return str+FnStr;
	//return "";
}

void CLogFile::saveLog_testresult(INT8U logfile,INT8U time,CString str,INT8U ack,INT8U LineType)
{

  if(ack == DACK_SUCESS)
   {
	    saveLog_str(logfile,TIME,str+_T("�ɹ�"),LineType);
   }
   else
   {
	   saveLog_err(logfile,TIME,str,ack);
   }
}
void CLogFile::saveLog_testresult_AfnFn(INT8U Afn,INT16U Fn,INT8U logfile,INT8U time,CString str,INT8U ack,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	 CString tmpstr;
	 ST_Fn pstFn;
	 UINT8 a_Fn;
	 (&pstFn)->DT1=Fn;
	 (&pstFn)->DT2=Fn>>8;
	 a_Fn=pMainDlg->getFn(pstFn);//ȡFn�ַ���
	 tmpstr += getAFNFnStr(Afn,a_Fn);
	 tmpstr += str;
	 saveLog_testresult(logfile,time,tmpstr,ack,classType);
}

void CLogFile::saveLog_StaCnt(INT16U  sucesscnt,INT16U failcnt,INT8U logfile,INT8U time,CString str,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str1.Format(_T("���ɹ�����_%u,ʧ�ܴ���_%u,"),sucesscnt,failcnt);
	str1=str+str1;
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str1;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//�༭����ʾ		

	}
	else if (logfile == PARS_FILE)//DataIfo
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);//�༭����ʾ		
	}
}

void CLogFile::saveLog_StaBuf8(INT8U  *vSrcBuf,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	INT16U suc_cnt = 0;
	for (INT16U i=0;i<Cnt;i++)
	{
		str1.Format(_T("%d,"),vSrcBuf[i]);
		str+=str1;
		if(vSrcBuf[i] == 1)
		{
			suc_cnt++;
		}
	}
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}	
	strTemp +=str;
	if (logfile == DATA_FILE)
	{
		str = "";
		strTemp+= _T("\r\n");
		strTemp +=_T("������");
		str1.Format(_T("%d"),Cnt);
		strTemp +=str1;
		strTemp +=_T(" �ɹ�����");
		str1.Format(_T("%d"),suc_cnt);
		strTemp +=str1;
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//�༭����ʾ		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);//�༭����ʾ		
	}
}
void CLogFile::saveLog_StaBuf16(INT16U  *vSrcBuf,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	for (INT16U i=0;i<Cnt;i++)
	{
		str1.Format(_T("%u,"),vSrcBuf[i]);
		str+=str1;
	}
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//�༭����ʾ		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);//�༭����ʾ		
	}
}
void CLogFile::saveLog_StaBuf32(INT32U  *vSrcBuf,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	for (INT16U i=0;i<Cnt;i++)
	{
		str1.Format(_T("%u,"),vSrcBuf[i]);
		str+=str1;
	}
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//�༭����ʾ		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);//�༭����ʾ		
	}
}
void CLogFile::saveLog_testresultALL_AfnFn(INT8U Afn,INT16U Fn,INT8U time,CString str,INT8U ack,INT8U classType)
{
	saveLog_testresult_AfnFn(Afn,Fn,DATA_FILE,time,str,ack,classType);
	saveLog_testresult_AfnFn(Afn,Fn,PARS_FILE,time,str,ack,classType);
}
void CLogFile::saveLog_testresultAll(INT8U time,CString str,INT8U ack,INT8U classType)
{
	saveLog_testresult(DATA_FILE,time,str,ack,classType);
	saveLog_testresult(PARS_FILE,time,str,ack,classType);
}
void CLogFile::saveLog_strAll(INT8U time,CString str,INT8U LineType)
{
	saveLog_str(DATA_FILE,time,str,LineType);
	saveLog_str(PARS_FILE,time,str,LineType);
}

void CLogFile::saveLog_BingF(INT8U logfile,INT8U time,CString str,sBinFa376_2_HostMsg BeifenMSg,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1,str2,str3,str4,str_s;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str1.Format(_T("s_Seq:%d,"),BeifenMSg.s_Seq);
	for (INT8U i=0;i<16;i++)
	{
		str_s.Format(_T("ackFg:%d,"),BeifenMSg.ackFg[i]);
		str2+=str_s;
	}
	str3.Format(_T("di645cnt:%d,"),BeifenMSg.di645cnt);
	for (INT8U i=0;i<16;i++)
	{
		str_s.Format(_T("di645Buf:%u,"),BeifenMSg.di645Buf[i]);
		str4+=str_s;
	}
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str+str1+str2+str3+str4;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//�༭����ʾ		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);
	}

}

void CLogFile::saveLog_NoAckMsg(INT8U logfile,INT8U time,CString str,sNoAckDiMsg  ackMsg,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1,str2,str3,str_s;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str1.Format(_T("s_Di:%u,"),ackMsg.s_Di);
	for (INT8U i=0;i<4;i++)
	{
		str_s.Format(_T("s_Time:%u,"),ackMsg.s_Time[i]);
		str2+=str_s;
	}
	str3.Format(_T("s_RcvCnt:%d,"),ackMsg.s_RcvCnt);

	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str+str1+str2+str3;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//�༭����ʾ		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);
	}


}
void CLogFile::saveLog_ClkSta(sAckTimeSta *timeclk376,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1,str2,str3,str4;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str1.Format(_T("SEQ:%d,"),timeclk376->s_Seq);
	str2.Format(_T("�Ƿ񷵻�:%d,"),timeclk376->ackFg);
	str3.Format(_T("���ݸ�ʽ:%d,"),timeclk376->dataack);
	str4.Format(_T("���ʱ��:%u,"),timeclk376->timeclk);

	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str+str1+str2+str3+str4;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//�༭����ʾ		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);
	}

}

INT8U ChangeAmtBps(INT32U bps)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	DCB dcb;
	CString strBaud;
	//GetCommState(pMainDlg->m_hCom645,&dcb);
	//dcb.BaudRate=bps;  //��������
	//if(SetCommState(pMainDlg->m_hCom645,&dcb))
	//{
	//	return 1;
	//}
	return 0;
}
INT32U  QueAmtBps(void)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	DCB dcb;
	//GetCommState(pMainDlg->m_hCom645,&dcb);
	return dcb.BaudRate;  //��������
}

// ������Ϣ�����Զ��رգ���Ҫָ�����ǣ�Windows 2000��user32.dllû�е������������   
//#ifdef UNICODE  
//#define MessageBoxTimeout MessageBoxTimeoutW  
//#else  
//#define MessageBoxTimeout MessageBoxTimeoutA  
//#endif  
extern "C"  
{
	int WINAPI MessageBoxTimeoutA(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);  
	int WINAPI MessageBoxTimeoutW(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);  
}; 
void MessageBoxDelayTime(CString str,INT32U time)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString string;
	string.Format(_T("%d"), time); //��������װ���ַ�����
    //MessageBoxTimeoutA(pMainDlg->GetSafeHwnd(), _T(str+"\r\n"+string+"����Զ��رգ�"), _T("��ʱ�Ի���"),  MB_ICONINFORMATION, GetSystemDefaultLangID(),1000*time);  

}
