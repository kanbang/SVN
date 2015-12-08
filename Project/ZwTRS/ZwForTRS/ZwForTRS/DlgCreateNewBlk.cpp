
//-----------------------------------------------------------------------------
//----- DlgCreateNewBlk.cpp : Implementation of CDlgCreateNewBlk
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "DlgCreateNewBlk.h"
#include "Global.h"
#include "BlkInfo.h"
#include "DlgSQLDB.h"
#include "MakeBlkFile.h"
//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CDlgCreateNewBlk, CAcUiDialog)

BEGIN_MESSAGE_MAP(CDlgCreateNewBlk, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CDlgCreateNewBlk::OnCbnSelchangeComboName)
	ON_BN_CLICKED(IDOK, &CDlgCreateNewBlk::OnBnClickedOk)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CDlgCreateNewBlk::CDlgCreateNewBlk (CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CDlgCreateNewBlk::IDD, pParent, hInstance) , m_strBlkName(_T(""))
{
	m_strType = gGlobal.GetIniValue(_T("�¿�"), _T("����"));
	m_strBlkName = gGlobal.GetIniValue(_T("�¿�"), _T("����"));
}

//-----------------------------------------------------------------------------
void CDlgCreateNewBlk::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	DDX_Control(pDX, IDC_COMBO_TYPE, m_ComBType);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strBlkName);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_strType);
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CDlgCreateNewBlk::OnAcadKeepFocus (WPARAM, LPARAM) {
	return (TRUE) ;
}

// -----------------------------------------------------------------------------
BOOL CDlgCreateNewBlk::OnInitDialog(void)
{
	BOOL retCode =CAcUiDialog::OnInitDialog () ;
	CenterWindow(acedGetAcadDwgView());

	m_ComBType.InsertString(-1, _T("�豸"));
	m_ComBType.InsertString(-1, _T("�Ǳ�"));
	m_ComBType.InsertString(-1, _T("����"));
	int nCur = m_ComBType.FindString(-1, m_strType);
	if (nCur == -1)			  
	{
		nCur = 0;
	}
	m_ComBType.SetCurSel(nCur);
	UpdateData(FALSE);

	return (retCode) ;
}

void CDlgCreateNewBlk::OnCbnSelchangeComboName()
{
	int nCursel = m_ComBType.GetCurSel();
	if (nCursel == -1)
	{
		nCursel = 0;
	}
	m_ComBType.SetCurSel(nCursel);
	m_ComBType.GetLBText(m_ComBType.GetCurSel(), m_strType);
}
void CDlgCreateNewBlk::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(m_strBlkName);
	m_ComBType.GetLBText(m_ComBType.GetCurSel(), m_strType);
	if (m_strBlkName.IsEmpty())
	{
		AfxMessageBox(_T("��������Ϊ��"));
		return;
	}
	CString strApp = gGlobal.GetAppPath();
	bool bAddXData = false;
	CString strType;
	if (m_strType.CompareNoCase(_T("�豸")) == 0)
	{
		strType =  _T("�豸\\");
		bAddXData = true;
	}
	else if (m_strType.CompareNoCase(_T("�Ǳ�")) == 0)
	{
		bAddXData = true;
		strType =  _T("�Ǳ�\\");
	}
	else if (m_strType.CompareNoCase(_T("����")) == 0)
	{
		bAddXData = false;
		strType =  _T("����\\");
	}
	m_strFileName = strApp + strType + m_strBlkName + _T(".dwg");
	BOOL bRet = gGlobal.IsFileExist(m_strFileName);
	if (bRet)
	{
		AfxMessageBox(_T("�ÿ����Ѵ��ڣ���������"));
		return;
	}
	BeginEditorCommand();
	CMakeBlkFile mFile;
	mFile.SetFileName(m_strFileName);
	/*if (bAddXData)
	{
		CAcModuleResourceOverride rs;
		CDlgSQLDB dlg;
		if (dlg.DoModal() == IDOK)
		{
			CDataBaseInfo baseInfo = dlg.GetData();
			mFile.SetDBInfo(baseInfo);
			if (mFile.Save())
			{
				gGlobal.SetIniValue(_T("�¿�"), _T("����"), m_strType);
				gGlobal.SetIniValue(_T("�¿�"), _T("����"), m_strBlkName);
				gGlobal.WriteIniFile();
			}
		}
	}
	else 
	{*/
		if (mFile.Save())
		{
			gGlobal.SetIniValue(_T("�¿�"), _T("����"), m_strType);
			gGlobal.SetIniValue(_T("�¿�"), _T("����"), m_strBlkName);
			gGlobal.WriteIniFile();
		}
	//}
	
	CompleteEditorCommand();	
	CAcUiDialog::OnOK();
}
