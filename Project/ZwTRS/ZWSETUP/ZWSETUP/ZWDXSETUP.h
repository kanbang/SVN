
// ZWDXSETUP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZWDXSETUPApp:
// �йش����ʵ�֣������ ZWDXSETUP.cpp
//

class CZWDXSETUPApp : public CWinAppEx
{
public:
	CZWDXSETUPApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZWDXSETUPApp theApp;