#pragma once
//�����ļ�
#include "OperateReg.h"
class CFileOperate
{
public:
	CFileOperate(void);
	~CFileOperate(void);
	//��ȡ��ǰӦ��λ��
	CString GetAppPath();
	//��ȡcad�İ�װ·��
	bool GetCADPath();
	//��д����·��
	bool SetOptions();
	//�Զ�����
	//@param strFileΪ�ļ�·����
	bool SetAutoLoadZrx(LPCTSTR strFile);
	//����CAD
	bool lauchCAD();
	//����Ŀ¼����ļ�����һ��Ŀ¼
	bool CopyDirTo(LPCTSTR strFrom, LPCTSTR strTo);
	//����zwcad.lsp�ļ���һ���ļ�λ�õ���һ��λ��
	bool CopyLspFile();
	//
	CString GetLoadCmdStr(CString strInput, CString strLoad);

private:
	CString m_strAppPath;
	CString m_strCADPath;
	OperateReg	m_Reg;
};

