#pragma once
#include "IniFile.h"
#include <map>
#include <vector>
#include <utility>
using namespace std;

typedef vector<pair<CString,int> > DataVec;

//�ļ�����
class CFileFormat
{
public:
	CFileFormat(void);
	~CFileFormat(void);
	//ȡ����
	int getStart() const;
	int getCombine() const;
	/*int getKey1() const;
	int getKey2() const;
	int getKey3() const;
	int getKey4() const;
	int getKey5() const;
	int getKey6() const;

	LPCTSTR getKey1();
	LPCTSTR getKey2();
	LPCTSTR getKey3();
	LPCTSTR getKey4();
	LPCTSTR getKey5();
	LPCTSTR getKey6();*/
	LPCTSTR getData();
	//��ȡ�ؼ��ֵ����ֺ�λ��
	DataVec GetKeyData();
	////��������
	//void setStart(int );
	//void setCombine(int );
	//void setKey1(int );
	//void setKey2(int );
	//void setKey3(int );
	//void setKey4(int );
	//void setKey5(int );
	//void setKey6(int );
	//			 
	//void setKey1(LPCTSTR );
	//void setKey2(LPCTSTR );
	//void setKey3(LPCTSTR );
	//void setKey4(LPCTSTR );
	//void setKey5(LPCTSTR );
	//void setKey6(LPCTSTR );

	//���ļ��ж�ȡ����
	//@param strFileNameΪ�ļ�·��
	//��strfilename�ж�ȡ����
	bool Read(LPCTSTR strFileName);

	//��������
	//@param strInputΪ������ַ��������ַ����á�����������ʹ���ַ����а���int��string
	//@param nOutΪ������int����
	//@param strOutΪ����������
	bool GetDataFromString(CString strInput/*, int& nOut, CString& strOut*/);
private:
	//��һ�б�Ȼ�����
	//�ܹ�����
	//���������ݲ���
	int m_nCombine;//�ϲ�����
	int m_nStart;//��ʼλ��
	int m_nKey1;//�ؼ���1��λ��
	//CString m_strKey1;//�ؼ���1������
	//int m_nKey2;//�ؼ���2��λ��
	//CString m_strKey2;//�ؼ���2������
	//int m_nKey3;
	//CString m_strKey3;
	//int m_nKey4;
	//CString m_strKey4;
	//int m_nKey5;
	//CString m_strKey5;
	//int m_nKey6;
	//CString m_strKey6;
	CIniFile m_IniFile;
	CString m_strData;//��������
	//@param pair�еĵ�һ��������¼�ؼ���
	//@param pair�еĵڶ���������¼�ؼ��ֵ�λ��
	DataVec m_Data;
	//@param ��һ��������¼�ؼ�������
	//map<CString, CString> m_DataMap;
};


