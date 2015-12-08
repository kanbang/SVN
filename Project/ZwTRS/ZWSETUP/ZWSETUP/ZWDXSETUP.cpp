
// ZWDXSETUP.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ZWDXSETUP.h"
#include "ZWDXSETUPDlg.h"
#include "TimeManager.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "OperateReg.h"
#include "FileOperate.h"

// CZWDXSETUPApp

BEGIN_MESSAGE_MAP(CZWDXSETUPApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CZWDXSETUPApp ����

CZWDXSETUPApp::CZWDXSETUPApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CZWDXSETUPApp ����

CZWDXSETUPApp theApp;

CString GetLoadCmdStr(CString strInput, CString strLoad)
{
	CString strReturn(strInput);
	strReturn.Replace(_T("\\"), _T("\\\\"));
	strReturn = _T("(") + strLoad + _T('\x20') + _T('\"') + strReturn + _T('\"') + _T(")");
	return strReturn;
}
#include <Windows.h>
#include <TlHelp32.h>

void CloseProcess(char *sProcessName)
{
	bool bIsOpened = false;
	if(sProcessName==NULL)
		return;
	PROCESSENTRY32 pe32;
	//��ʹ������ṹǰ�����������Ĵ�С
	pe32.dwSize = sizeof(pe32);
	//��ϵͳ�����еĽ����ĸ�����
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS,0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return;
	DWORD hMsDevId=0;
	//�������̿��գ�������ʾÿ�����̵���Ϣ
	BOOL bMore = ::Process32First(hProcessSnap,&pe32);
	while (bMore)
	{
		if(stricmp(pe32.szExeFile,sProcessName)==0)
		{
			hMsDevId=pe32.th32ProcessID;
			bIsOpened = true;
			break;
		}
		bMore = ::Process32Next(hProcessSnap,&pe32);
	}
	//��Ҫ���������snapshot����
	::CloseHandle(hProcessSnap);
	if (bIsOpened)
	{
		//��������
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,hMsDevId);
		::TerminateProcess(hProcess,4);
	}
} 
// CZWDXSETUPApp ��ʼ��

BOOL CZWDXSETUPApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	
	//�ҵ���ǰexe�ļ�����λ��
	CFileOperate foperate;
	bool bRet = foperate.GetCADPath();
	if (!bRet)
	{
		AfxMessageBox(_T("û�а�װzwcad2014��е"));
		return FALSE;
	}

	CloseProcess("ZWCAD.exe");

	//��ȡ��ǰcad��vernumber	
	CString strAppPath = foperate.GetAppPath();
	foperate.CopyLspFile();
	foperate.SetOptions();
	foperate.lauchCAD();

	return FALSE;
}
