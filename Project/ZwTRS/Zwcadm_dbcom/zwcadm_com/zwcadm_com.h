// zwcadm_com.h : zwcadm_com DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "zwcadm_com_i.h"


// Czwcadm_comApp
// �йش���ʵ�ֵ���Ϣ������� zwcadm_com.cpp
//

class Czwcadm_comApp : public CWinApp
{
public:
	Czwcadm_comApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
