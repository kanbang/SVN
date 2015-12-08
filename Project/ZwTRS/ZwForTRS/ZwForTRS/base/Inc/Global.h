// Global.h: interface for the CGlobal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBAL_H__10D86CB2_8BCE_49FE_B56F_E3657D5A006E__INCLUDED_)
#define AFX_GLOBAL_H__10D86CB2_8BCE_49FE_B56F_E3657D5A006E__INCLUDED_

#include <afxtempl.h>
#pragma once

#include "StdAfx.h"

#include "map"
class CGlobal  
{
	CGlobal();
	
public:
	//	BOOL WriteDictionary();
	BOOL SetIniValue(LPCTSTR key,LPCTSTR Name,LPCTSTR value);
	BOOL SetIniValue(LPCTSTR key, LPCTSTR Name, double value);
	int GetIniValueNum(CString key);
	CString GetIniPath();
	CString SubString(CString string,CString Split,int index);
	void WriteIniFile();
	void SetIni(CString path);//����INI·������ȡ����
	virtual ~CGlobal();
	static CGlobal& Get();
	BOOL GetVar(LPCTSTR var, int *nRes);
	BOOL GetVar(LPCTSTR var, ads_real *rRes);
	BOOL GetVar(LPCTSTR var, ads_point *pRes);
	BOOL GetVar(LPCTSTR var, LPTSTR sRes);
	BOOL SetVar(LPCTSTR szVarName, int       nArg);
	BOOL SetVar(LPCTSTR szVarName, ads_real  rArg);
	BOOL SetVar(LPCTSTR szVarName, ads_point pArg);
	BOOL SetVar(LPCTSTR szVarName, LPCTSTR   sArg);

	
	 CString GetAppPath();

	 CString GetCsvFile();
	/////////////////////////////////////////////////////////////////////////////
	//�� �ܣ���ȡע�����ַ�����ֵ
	//�� �룺hKey-ע����HKEY_CLASSES_ROOT��HKEY_CURRENT_CONFIG��HKEY_CURRENT_USER��HKEY_LOCAL_MACHINE��HKEY_USERS
	//lpszSec-·�� lpszDef-Ĭ��ֵ lpszKey-����
	//�� ����lpszValue
	//�� �أ�-1��·��ʧ�� -2������ʧ�� �ɹ������ַ����ĳ���
	int GetRegister(HKEY hKey, LPCTSTR lpszSec, LPCTSTR lpszKey, LPCTSTR lpszDef, LPTSTR lpszValue);
	/////////////////////////////////////////////////////////////////////////////
	//��ע���,��DWORD��ֵ
	DWORD GetRegister(HKEY hKey, LPCTSTR lpszSec, LPCTSTR lpszKey, DWORD DefValue);
	/////////////////////////////////////////////////////////////////////////////
	//�� �ܣ�д��ע���,д�ַ���
	//�� �룺hKey-ע����HKEY_CLASSES_ROOT��HKEY_CURRENT_CONFIG��HKEY_CURRENT_USER��HKEY_LOCAL_MACHINE��HKEY_USERS
	//lpszSec-·�� lpszKey-���� lpszValue-ֵ
	//�� �أ�FALSE-ʧ�� TRUE-�ɹ�
	BOOL SetRegister(HKEY hKey, LPCTSTR lpszSec, LPCTSTR lpszKey, LPCTSTR lpszValue);
	/////////////////////////////////////////////////////////////////////////////
	//�� �ܣ�д��ע���,дDWORD
	BOOL SetRegister(HKEY hKey, LPCTSTR lpszSec, LPCTSTR lpszKey,DWORD Value);
	//�õ�Cyz����
	LPCTSTR GetIniValue(LPCTSTR Key,LPCTSTR name);
	double GetIniValue(LPCTSTR Key,LPCTSTR name,double);
	/////////////////////////////////////////////////////////////////////////////
	//����Cyz����

	int Myatoi(CString inputStr);
	BOOL Myatoi(CString inputStr,int& iresult);	

	BOOL IsFileExist(CString strFileName);	

	void setBlkRefCount(int nCount);

	int getBlkRefCount();

};

#endif
#define gGlobal CGlobal::Get()



