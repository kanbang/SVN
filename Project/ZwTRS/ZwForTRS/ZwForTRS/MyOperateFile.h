#pragma once

class MyOperateFile
{
public:
	MyOperateFile(void);
	~MyOperateFile(void);
	//��ȡ��Ŀ¼
	CString GetSubPath(LPCTSTR strPath);
	//������Ŀ¼
	bool FindSubDir(LPCTSTR strPath);
	//��ȡ�ļ���
	CString GetFileNameByPath(LPCTSTR strPath);
	//
	void GetFileNameFromThePath(CString& strPath, CStringArray& strFileNameArr, 
		CString strTypeName, bool bIsFullPath);

};
