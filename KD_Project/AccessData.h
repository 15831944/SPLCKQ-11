#pragma once
class CAccessData
{
public:
	CAccessData(void);
	~CAccessData(void);


public:
	CStringList m_strlistTableShuxing;
	_RecordsetPtr m_pRecordset;
	CString m_strAccessName;
	void GetStrList(CString strData,CString strFind , CString listData[]);
	bool CreatDataBase(CString strIntelligentName); //�������ݿ�
	bool DelectDataBase(CString strIntelligentName); //ɾ�����ݿ�
	bool CreatTable(CString strIntelligentName, CString strTableName , CString * strlist , int nNumb); //������
	bool DelectTable(CString strIntelligentName, CString strTableName);//ɾ����
	bool AddDataToTable(CString strIntelligentName, CString strTableName ,CString listType[],CString listData[],int Numb);//��������
	bool SelectDataFromTable(CString strIntelligentName, CString strTableName,CString strSelectData,CString strWhere,CString strListData[],int &nRow);//��ѯ����
	bool DelectDataFromTable(CString strIntelligentName, CString strTableName,CString strWhere);
	bool UpdataFromTable(CString strIntelligentName, CString strTableName,CString strSet,CString strWhere);//��������
	bool SetCopyTable(CString strIntelligentName, CString strTableName,CString strlastTable);//���Ʊ����ݵ���һ��
};

