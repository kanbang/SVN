#pragma once
#include "DataBaseInfo.h"
#include "FileFormat.h"
#include <map>
#include <vector>
#include <utility>
using namespace std;
//��������
class CDataSort
{
public:
	CDataSort(void);
	~CDataSort(void);
	//��������
	bool setData(map<CString, pair<CDataBaseInfo*, int> > Data, LPCTSTR str);	

	//���ؽ��
	//map<CString, map<CString, DataVec> > getData();
	map<CString, DataVec> getData();
	//���صڶ�������
	map<CString, vector<CString> > getStrData();
	
	//�ϲ�����������
	int getCombineCount() const;
	//��ʼλ��
	int getStart() const;
private:
	//��databaseinfo�и��ݹؼ��ֻ�ȡ����
	//@param ��һ��������¼databaseinfo�е�����
	//@param �ڶ���������¼ini�ļ��йؼ��ֵ����ݺ�λ��
	//@param ������������¼����
	//@param ���ĸ�������¼����ͼ���
	DataVec getDataByKey(CDataBaseInfo* pDb, DataVec vecKey, int nCount, LPCTSTR strChartNum);
	//��ȡ���������ݽ�������
	//@param ��һ��������¼����ͼ���
	//@param �ڶ���������¼�ؼ�������
	void SortDataByString(LPCTSTR strChartNum);
private:
	//�ļ�����
	CFileFormat m_FormatFile;
	//�ļ�·��
	//CString m_strFile;
	////@param ��һ��������¼����ͼ���
	////@param vector�е�һ��������¼�ؼ���
	////@param vector�еڶ���������¼�ؼ������ݵ�λ��
	map<CString, DataVec> m_Data;
	//@param ��һ��������¼����ͼ��ŵ�ǰ���ַ�
	//@param �ڶ�������map�е�һ��������¼����ͼ���
	//@param �ڶ�������map�еĵڶ���������¼vector����
	//@param vector�е�һ��������¼�ؼ���
	//@param vector�еڶ���������¼�ؼ������ݵ�λ��
	//map<CString, map<CString, DataVec> > m_RetData;
	//��¼���ַ�������������
	//@param ��һ������cstring��¼����ͼ��ŵ�ǰ׺
	//@param �ڶ���������¼ͬһǰ׺���������е�����
	map<CString, vector<CString> > m_StrData;
};

////���Excel��������
//class COutCell
//{
//public:
//	COutCell(void);
//	~COutCell(void);
//	//��ȡ����
//	LPCTSTR getKey1();
//	LPCTSTR getKey2();
//	LPCTSTR getKey3();
//	LPCTSTR getKey4();
//	LPCTSTR getKey5();
//	LPCTSTR getKey6();
//
//	//��������
//	void setKey1(LPCTSTR str);
//	void setKey2(LPCTSTR str);
//	void setKey3(LPCTSTR str);
//	void setKey4(LPCTSTR str);
//	void setKey5(LPCTSTR str);
//	void setKey6(LPCTSTR str);
//
//
//private:
//	//�ؼ���
//	CString m_strKey1;
//	CString m_strKey2;
//	CString m_strKey3;
//	CString m_strKey4;
//	CString m_strKey5;
//	CString m_strKey6;
//};