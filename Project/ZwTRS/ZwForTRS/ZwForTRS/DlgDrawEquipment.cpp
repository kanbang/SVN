//-----------------------------------------------------------------------------
//----- DlgDrawEquipment.cpp : Implementation of CDlgDrawEquipment
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "DlgDrawEquipment.h"
#include "Global.h"
#include "BlkInfo.h"
#include "DlgSQLDB.h"
#include "OperateReg.h"
#include "ArxDbgUtils.h"
#include "MyDrawEntity.h"
#include "MyEditEntity.h"
#include "MakeBlkFile.h"
//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CDlgDrawEquipment, CAcUiDialog)

BEGIN_MESSAGE_MAP(CDlgDrawEquipment, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(IDCANCEL, &CDlgDrawEquipment::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDlgDrawEquipment::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_DATA, &CDlgDrawEquipment::OnBnClickedButtonData)
	ON_BN_CLICKED(IDC_RADIO_HENGXIANG, &CDlgDrawEquipment::OnBnClickedRadioHengxiang)
	ON_BN_CLICKED(IDC_RADIO_ZONGXIANG, &CDlgDrawEquipment::OnBnClickedRadioZongxiang)
	ON_BN_CLICKED(IDC_CHECK_FIX, &CDlgDrawEquipment::OnBnClickedCheckFix)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CDlgDrawEquipment::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_RADIO_DOWN, &CDlgDrawEquipment::OnBnClickedRadioDown)
	ON_BN_CLICKED(IDC_RADIO_RIGHT, &CDlgDrawEquipment::OnBnClickedRadioRight)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY, &CDlgDrawEquipment::OnBnClickedCheckDisplay)
	ON_BN_CLICKED(IDC_RADIO_UP, &CDlgDrawEquipment::OnBnClickedRadioUp)
	ON_BN_CLICKED(IDC_RADIO_LEFT, &CDlgDrawEquipment::OnBnClickedRadioLeft)
	ON_CBN_SELCHANGE(IDC_COMBO_WEIHAO, &CDlgDrawEquipment::OnCbnSelchangeComboWeihao)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CDlgDrawEquipment::OnRBClick)
	ON_COMMAND(ID_32771, &CDlgDrawEquipment::OnAddBlock)
	ON_COMMAND(ID_32772, &CDlgDrawEquipment::OnDelBlock)
END_MESSAGE_MAP()


bool addBlockToPath(CString strPath)
{
	TCHAR val[512];
	CString strValue;
	int nRet = acedGetString(0, _T("\n������Ҫ�½��Ŀ���"), val);
	if (nRet != RTNORM)
	{
		return false;
	}
	strValue = val;
	CString strFileName = strPath + strValue + _T(".dwg");
	BOOL bRet = gGlobal.IsFileExist(strFileName);
	if (bRet)
	{
		AfxMessageBox(_T("�ÿ����Ѵ��ڣ���������"));
		return false;
	}
	CMakeBlkFile mFile;
	mFile.SetFileName(strFileName);
	if (!mFile.Save())
	{
		return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
CDlgDrawEquipment::CDlgDrawEquipment (CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CDlgDrawEquipment::IDD, pParent, hInstance) , m_bZongxiang(FALSE)
, m_bFixed(FALSE)
, m_pDb(NULL)
, m_strFName(_T(""))
, m_strStandard(_T(""))
, m_strPipe(_T(""))
, m_strCount(_T(""))
, m_strDefine(_T(""))
, m_nPosition(0)
, m_strWeihao(_T(""))
{
	m_bIsModified = false;
	m_InsertPt.set(0, 0, 0);
	m_strWeihao = gGlobal.GetIniValue(_T("�����豸"), _T("λ��"));
	m_strBlkName = gGlobal.GetIniValue(_T("�����豸"), _T("����"));
	m_strPipe = gGlobal.GetIniValue(_T("�����豸"), _T("�ܵ���"));
	m_strCount = gGlobal.GetIniValue(_T("�����豸"), _T("λ��"));
	m_bZongxiang = (BOOL)gGlobal.GetIniValue(_T("�����豸"), _T("����"), 0);
	m_bFixed = (BOOL)gGlobal.GetIniValue(_T("�����豸"), _T("�̶�"), 0);
	m_strDefine = gGlobal.GetIniValue(_T("�����豸"), _T("�Զ���"));
	m_nPosition = (int)gGlobal.GetIniValue(_T("�����豸"), _T("����λ��"), 0);
	m_bIsDisplay = (BOOL)gGlobal.GetIniValue(_T("�����豸"), _T("��ʾ"), 0);
	m_strIniFile = gGlobal.GetAppPath() + _T("�豸\\") + m_strBlkName + _T(".txt");
	m_blkFile.SetFileName(m_strIniFile);
	bool bRet = m_blkFile.Read();
	if (bRet)
	{
		CDataCell pCell = m_blkFile.GetData();
		m_baseInfo = m_blkFile.SetDataCell(pCell);
		m_strFName = m_baseInfo.GetFName();
		m_strStandard = m_baseInfo.GetBeizhu();
		SetRegInfo();
	}
	else
	{
		m_strFName = _T("");
		m_strStandard = _T("");
		m_baseInfo.SetFName(_T(""));
		m_baseInfo.SetFNumber(_T(""));
		m_baseInfo.SetBeizhu(_T(""));
		m_baseInfo.SetCailiao(_T(""));
		COperateReg Reg;
		CString strRootKey = _T("Software\\ZWSOFT\\ZWSQL");
		Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("NAME"), _T(""));
		Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("MARK"), _T(""));
		Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("STANDARD"), _T(""));
		Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("MATERIAL"), _T(""));
	}
	ClearDatabase();
}

CDlgDrawEquipment::~CDlgDrawEquipment()
{
	ClearDatabase();
}
//-----------------------------------------------------------------------------
void CDlgDrawEquipment::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	DDX_Radio(pDX, IDC_RADIO_HENGXIANG, m_bZongxiang);
	DDX_Check(pDX, IDC_CHECK_FIX, m_bFixed);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
	//DDX_Text(pDX, IDC_EDIT_NAME, m_strFName);
	//DDX_Text(pDX, IDC_EDIT_TYPE, m_strStandard);
	DDX_Text(pDX, IDC_EDIT_PREWH, m_strPipe);
	DDX_Text(pDX, IDC_EDIT_NUM, m_strCount);
	DDX_Check(pDX, IDC_CHECK_DISPLAY, m_bIsDisplay);
	DDX_Text(pDX, IDC_EDIT_DEFINE, m_strDefine);
	DDX_Radio(pDX, IDC_RADIO_UP, m_nPosition);
	DDX_Control(pDX, IDC_COMBO_WEIHAO, m_CombWeihao);
	DDX_CBString(pDX, IDC_COMBO_WEIHAO, m_strWeihao);
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CDlgDrawEquipment::OnAcadKeepFocus (WPARAM, LPARAM) {
	return (TRUE) ;
}

BOOL CDlgDrawEquipment::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CenterWindow(acedGetAcadDwgView());
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_TreeCtrl.ModifyStyle(0, TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES);
	m_strParentPath = gGlobal.GetAppPath();
	m_TreeCtrl.SetParentPath(m_strParentPath);
	m_TreeCtrl.DisPlayTree(_T("�豸"), TRUE);
	if (!m_strBlkName.IsEmpty())
	{
		HTREEITEM hItem = m_TreeCtrl.GetRootItem();
		hItem = FindItem(hItem);
		if (hItem == NULL)
		{
			HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
			HTREEITEM hChild = m_TreeCtrl.GetChildItem(hRoot);
			m_TreeCtrl.Expand(hRoot, TVE_EXPAND);
			m_TreeCtrl.Expand(hChild, TVE_EXPAND);

			HTREEITEM hNextItem = m_TreeCtrl.GetChildItem(hChild);
			m_strFileName = m_TreeCtrl.GetFullPath(hNextItem) + _T(".dwg");
		}
		else
		{
			m_strBlkName = m_TreeCtrl.GetItemText(hItem);	
			m_TreeCtrl.SelectItem(hItem); //����ѡ�н��
			m_strFileName = m_TreeCtrl.GetFullPath(hItem) + _T(".dwg");
		}
	}
	else
	{
		HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
		HTREEITEM hChild = m_TreeCtrl.GetChildItem(hRoot);
		m_TreeCtrl.Expand(hRoot, TVE_EXPAND);
		m_TreeCtrl.Expand(hChild, TVE_EXPAND);

		HTREEITEM hNextItem = m_TreeCtrl.GetChildItem(hChild);
		m_strFileName = m_TreeCtrl.GetFullPath(hNextItem) + _T(".dwg");
	}
	
	InitDatabase();
	InitGraphList();
	OnBnClickedCheckFix();
	
	CStringArray tmpArr;
	tmpArr.RemoveAll();
	CString strGanNature = gGlobal.GetIniValue(_T("�����豸"), _T("λ������"));
	ArxDbgUtils::GetCommaFromString(strGanNature, tmpArr);
	for (int i=0; i<tmpArr.GetSize(); i++)
	{
		m_CombWeihao.AddString(tmpArr.GetAt(i));
	}
	int nCur = m_CombWeihao.FindString(-1, m_strWeihao);
	if (nCur = -1)
	{
		nCur = 0;
	}
	m_CombWeihao.SetCurSel(nCur);

	m_strCount = ArxDbgUtils::AddZeroForNumber(m_strCount, m_strWeihao);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgDrawEquipment::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAcUiDialog::OnCancel();
}

void CDlgDrawEquipment::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_baseInfo.GetFNumber().IsEmpty())//�ж�û��Fitemid�Ŀ鶼�ÿ�����״̬
	{
		AfxMessageBox(_T("��ʹ�õ������ݽ����ݵ���"));
		return;
	}
	BeginEditorCommand();
	/*if (!m_bIsModified)
	{
		int nRet = acedGetPoint(NULL, _T("\n��ѡ��һ��"), asDblArray(m_InsertPt));
		if (nRet != RTNORM)
		{
			CancelEditorCommand();
			return;
		}
	}*/

	GetDlgItem(IDC_EDIT_NUM)->GetWindowText(m_strCount);
	GetDlgItem(IDC_EDIT_PREWH)->GetWindowText(m_strPipe);
	//GetDlgItem(IDC_EDIT_NAME)->GetWindowText(m_strFName);
	//GetDlgItem(IDC_EDIT_TYPE)->GetWindowText(m_strStandard);
	GetDlgItem(IDC_EDIT_DEFINE)->GetWindowText(m_strDefine);

	HTREEITEM hCurSel = m_TreeCtrl.GetSelectedItem();
	m_strBlkName = m_TreeCtrl.GetItemText(hCurSel);	
	CBlkInfo blkInfo;
	blkInfo.SetInsertPt(m_InsertPt);
	blkInfo.SetBlkName(m_strBlkName);
	blkInfo.SetFilePath(m_strFileName);
	blkInfo.SetBlkType(_T("�豸"));

	CString strText;
	strText = m_strPipe + m_strCount;
	m_strIniFile = gGlobal.GetAppPath() + _T("�豸\\") + m_strBlkName + _T(".txt");
	//m_baseInfo.SetChartNum(strText);
	CBlkInsert blkInsert(blkInfo, m_baseInfo);
	blkInsert.SetText(strText);
	blkInsert.SetZongxiang(m_bZongxiang);
	blkInsert.SetModified(m_bIsModified);
	//////////////////////////////////////////////////////////////////////////
	blkInsert.SetPosition(m_nPosition);
	blkInsert.SetDrawText(m_bIsDisplay);
	CString strFName;
	CString strStandard = ArxDbgUtils::GetNameAndStandard(m_strFName, strFName);
	blkInsert.SetStandard(strStandard);
	blkInsert.SetDefine(m_strDefine);
	//////////////////////////////////////////////////////////////////////////
	if (blkInsert.Insert())
	{
		m_Exts = blkInsert.GetObjExts();
		CDataCell pCell;
		/*pCell.SetFName(m_baseInfo.GetFName());
		pCell.SetFErpCls(m_baseInfo.GetFErpCls());
		pCell.SetF107(m_baseInfo.GetDanzhong());
		pCell.SetF105(m_baseInfo.GetCailiao());
		pCell.SetFItemId(m_baseInfo.GetFItemId());
		pCell.SetF106(m_baseInfo.GetBeizhu());
		pCell.SetFMaund(m_baseInfo.GetDanwei());
		pCell.SetFNumber(m_baseInfo.GetFNumber());*/
		pCell = m_blkFile.GetDataCellByDB(m_baseInfo);
		m_blkFile.SetFileName(m_strIniFile);
		m_blkFile.SetData(pCell);
		m_blkFile.Write();

		//DrawText();
		//д��ini�ļ�
		gGlobal.SetIniValue(_T("�����豸"), _T("����"), m_strBlkName);
		gGlobal.SetIniValue(_T("�����豸"), _T("�ܵ���"), m_strPipe);
		if (!m_bFixed)
		{
			//�Ա������������
			CString strPrefix, strNext, strNum;
			int nlen = ArxDbgUtils::GetPileLengthEx(m_strCount, strPrefix, strNext);
			nlen+=1;
			strNum.Format(_T("%d"), nlen);
			m_strCount = strPrefix+ strNum + strNext;
		}
		m_strCount = ArxDbgUtils::AddZeroForNumber(m_strCount, m_strWeihao);
		gGlobal.SetIniValue(_T("�����豸"), _T("λ��"), m_strCount);
		gGlobal.SetIniValue(_T("�����豸"), _T("����"), m_bZongxiang);
		gGlobal.SetIniValue(_T("�����豸"), _T("�̶�"), m_bFixed);
		gGlobal.SetIniValue(_T("�����豸"), _T("�Զ���"), m_strDefine);
		gGlobal.SetIniValue(_T("�����豸"), _T("����λ��"), m_nPosition);
		gGlobal.SetIniValue(_T("�����豸"), _T("��ʾ"), m_bIsDisplay);
		gGlobal.SetIniValue(_T("�����豸"), _T("λ��"), m_strWeihao);
		gGlobal.WriteIniFile();
	}
	else	
	{

	}
	
	CompleteEditorCommand();
	CAcUiDialog::OnOK();
}

void CDlgDrawEquipment::OnBnClickedButtonData()//��������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetRegInfo();

	CAcModuleResourceOverride rs;
	
	CDlgSQLDB dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_baseInfo = dlg.GetData();
		if (m_baseInfo.GetFNumber().IsEmpty())
		{
			AfxMessageBox(_T("û��ȡ������"));
			return;
		}
		else
		{
			m_strFName = m_baseInfo.GetFName();
			m_strStandard = m_baseInfo.GetBeizhu();
			CString strFName;
			CString strStandard = ArxDbgUtils::GetNameAndStandard(m_strFName, strFName);
			GetDlgItem(IDC_EDIT_NAME)->SetWindowText(strFName);
			GetDlgItem(IDC_EDIT_TYPE)->SetWindowText(strStandard);
			//GetDlgItem(IDC_EDIT_NAME)->SetWindowText(m_strFName);
			//GetDlgItem(IDC_EDIT_TYPE)->SetWindowText(m_strStandard);
		}
	}
	//CAcUiDialog::OnOK();
}

void CDlgDrawEquipment::OnBnClickedRadioHengxiang()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bZongxiang = FALSE;
}

void CDlgDrawEquipment::OnBnClickedRadioZongxiang()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bZongxiang = TRUE;
}

void CDlgDrawEquipment::OnBnClickedCheckFix()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_FIX);
	m_bFixed = (BOOL)pBtn->GetCheck();
}

void CDlgDrawEquipment::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM hCurSel = m_TreeCtrl.GetSelectedItem();

	if (m_TreeCtrl.ItemHasChildren(hCurSel) && (!m_TreeCtrl.GetParentItem(hCurSel)))//���ڵ�
	{

	}
	else if (m_TreeCtrl.ItemHasChildren(hCurSel) && m_TreeCtrl.GetParentItem(hCurSel))//��ѡΪ�ڵ�
	{

	}
	else if (!m_TreeCtrl.ItemHasChildren(hCurSel))
	{
		m_strBlkName = m_TreeCtrl.GetItemText(hCurSel);
		m_strFileName = m_TreeCtrl.GetFullPath(hCurSel) + _T(".dwg");
		InitDatabase();
		InitGraphList();
		m_strIniFile = gGlobal.GetAppPath() + _T("�豸\\") + m_strBlkName + _T(".txt");
		m_blkFile.SetFileName(m_strIniFile);
		bool bRet = m_blkFile.Read();
		if (bRet)
		{
			CDataCell pCell = m_blkFile.GetData();
			m_baseInfo = m_blkFile.SetDataCell(pCell);
			m_strFName = m_baseInfo.GetFName();
			m_strStandard = m_baseInfo.GetBeizhu();

			CString strFName;
			CString strStandard = ArxDbgUtils::GetNameAndStandard(m_strFName, strFName);
			GetDlgItem(IDC_EDIT_NAME)->SetWindowText(strFName);
			GetDlgItem(IDC_EDIT_TYPE)->SetWindowText(strStandard);

			SetRegInfo();
		}
		else
		{
			m_strFName = _T("");
			m_strStandard = _T("");
			//GetDlgItem(IDC_EDIT_NAME)->SetWindowText(m_strFName);
			//GetDlgItem(IDC_EDIT_TYPE)->SetWindowText(m_strStandard);
			m_baseInfo.SetFName(_T(""));
			m_baseInfo.SetFNumber(_T(""));
			m_baseInfo.SetBeizhu(_T(""));
			m_baseInfo.SetCailiao(_T(""));
			COperateReg Reg;
			CString strRootKey = _T("Software\\ZWSOFT\\ZWSQL");
			Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("NAME"), _T(""));
			Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("MARK"), _T(""));
			Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("STANDARD"), _T(""));
			Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("MATERIAL"), _T(""));
		}
	}	
	*pResult = 0;
}


void CDlgDrawEquipment::ClearDatabase()
{
	m_gsView.DeleteAllItem();
	m_gsView.SetCurDatabase(NULL);

	if (m_pDb!=NULL)
	{
		delete m_pDb;
		m_pDb = NULL;
	}
}

void CDlgDrawEquipment::InitDatabase()
{
	ClearDatabase();
	CAcModuleResourceOverride rs;
	m_pDb = new AcDbDatabase(false);
	m_pDb->readDwgFile(m_strFileName);
}

bool CDlgDrawEquipment::InitGraphList()
{
	CWnd* pWnd = GetDlgItem(IDC_STATIC_BMP);
	if (NULL == pWnd)
	{
		return false;
	}

	DWORD dwStyle = pWnd->GetStyle();
	CRect rc;
	pWnd->GetWindowRect(rc);
	ScreenToClient(rc);

	pWnd->DestroyWindow();
	if (!m_gsView.Create(rc, this, IDC_STATIC_BMP, dwStyle))
	{
		return false;
	}

	m_gsView.SetCurDatabase(m_pDb);
	m_gsView.ShowItemCaption(false);
	m_gsView.EnableDefault(false);
	m_gsView.EnableSel(true);
	m_gsView.SetLayer(1, 1);

	m_gsView.InsertItem(0, ACDB_MODEL_SPACE);
	return true;
}

HTREEITEM CDlgDrawEquipment::FindItem(HTREEITEM ht)
{
	CString strText;
	HTREEITEM hItem = NULL;
	m_TreeCtrl.Expand(ht,TVE_EXPAND);
	hItem = m_TreeCtrl.GetNextItem(ht,TVGN_NEXTVISIBLE);
	if(hItem != NULL)
	{
		strText = m_TreeCtrl.GetItemText(hItem);
		if (strText.CompareNoCase(m_strBlkName) == 0)
		{
			return hItem;
		}
		hItem = FindItem(hItem);
	}
	else
		return NULL;
	return hItem;
}

bool CDlgDrawEquipment::GetModified() const
{
	return m_bIsModified;
}

void CDlgDrawEquipment::SetModified(bool bModified)
{
	m_bIsModified = bModified;
}

AcGePoint3d CDlgDrawEquipment::GetInsertPt() const
{
	return m_InsertPt;
}

void CDlgDrawEquipment::SetInsertPt(AcGePoint3d pt)
{
	m_InsertPt = pt;
}


void CDlgDrawEquipment::DrawText()
{
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//��������
	CString strText;
	strText = m_strPipe + m_strCount;
	if (strText.IsEmpty())
	{
		return;
	}
	
	AcGePoint3d minPt,maxPt;
	minPt = m_Exts.minPoint();
	maxPt = m_Exts.maxPoint();
	double dLength = abs(maxPt.x - minPt.x);
	double dHeight = abs(maxPt.y - minPt.y);
	AcGePoint3d textPt;
	textPt.x = minPt.x + 1.5*dLength;
	textPt.y = minPt.y + 0.5*dHeight;
	textPt.z = 0;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//������
	AcDbObjectId layerId = ArxDbgUtils::CreateNewLayer(_T("TEXT"), 6);
	if (!m_bZongxiang)
	{
		AcDbObjectId textId = MyDrawEntity::DrawText(textPt, strText, 2.23, AcDbObjectId::kNull, AcDb::kTextLeft, AcDb::kTextBase);
		MyEditEntity::openEntChangeLayer(textId, layerId);
	}
	else
	{
		AcDbObjectId textId = MyDrawEntity::DrawText(textPt, strText, 2.23, AcDbObjectId::kNull, AcDb::kTextMid, AcDb::kTextBase);
		textId = MyEditEntity::openEntChangeRotation(textId, PI/2);
		MyEditEntity::openEntChangeLayer(textId, layerId);
	}

}


void CDlgDrawEquipment::SetRegInfo()
{
	COperateReg Reg;
	CString strRootKey = _T("Software\\ZWSOFT\\ZWSQL");
	Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("NAME"), m_baseInfo.GetFName());
	Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("MARK"), m_baseInfo.GetFNumber());
	Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("STANDARD"), m_baseInfo.GetBeizhu());
	Reg.SetRegister(HKEY_CURRENT_USER, strRootKey, _T("MATERIAL"), m_baseInfo.GetCailiao());
}


void CDlgDrawEquipment::OnBnClickedRadioDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nPosition = 2;
}

void CDlgDrawEquipment::OnBnClickedRadioRight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nPosition = 3;	
}
void CDlgDrawEquipment::OnBnClickedRadioUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nPosition = 0;
}

void CDlgDrawEquipment::OnBnClickedRadioLeft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nPosition = 1;
}

void CDlgDrawEquipment::OnBnClickedCheckDisplay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_DISPLAY);
	m_bIsDisplay = (BOOL)pBtn->GetCheck();
}


void CDlgDrawEquipment::OnCbnSelchangeComboWeihao()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCursel = m_CombWeihao.GetCurSel();
	if (nCursel == -1)
	{
		nCursel = 0;
	}
	m_CombWeihao.SetCurSel(nCursel);
	m_CombWeihao.GetLBText(m_CombWeihao.GetCurSel(), m_strWeihao);
	GetDlgItem(IDC_EDIT_NUM)->GetWindowText(m_strCount);
	m_strCount = ArxDbgUtils::AddZeroForNumber(m_strCount, m_strWeihao);
	GetDlgItem(IDC_EDIT_NUM)->SetWindowText(m_strCount);
}

void CDlgDrawEquipment::OnRBClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint point;

	GetCursorPos(&point);

	CPoint pointInTree = point;

	m_TreeCtrl.ScreenToClient(&pointInTree);

	HTREEITEM item;

	UINT flag = TVHT_ONITEM;

	item = m_TreeCtrl.HitTest(pointInTree, &flag);

	if(item != NULL)

	{

		m_TreeCtrl.SelectItem(item);

		CMenu menu;

		menu.LoadMenu(IDR_MENU1);

		//menu.EnableMenuItem(ID_32771, MF_GRAYED);
		//menu.EnableMenuItem(ID_32772, MF_GRAYED);

		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | 

			TPM_RIGHTBUTTON, point.x, point.y, this, NULL);

	}

	//CRect rc;
	//m_TreeCtrl.GetWindowRect(rc);

	//if (PtInRect(rc, point))
	//{
	//	CMenu menu ;//��������Ҫ�õ���cmenu����  
	//	menu.LoadMenu(IDR_MENU1);//װ���Զ�����Ҽ��˵�  
	//	CPoint tmpPoint = point;
	//	::ScreenToClient(m_TreeCtrl, &tmpPoint);
	//	if (m_TreeCtrl.HitTest(tmpPoint)==NULL)
	//	{
	//		menu.EnableMenuItem(ID_32771, MF_GRAYED);
	//		menu.EnableMenuItem(ID_32772, MF_GRAYED);
	//	}
	//	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); //��ָ��λ����ʾ�����˵�
	//}
}

void CDlgDrawEquipment::OnAddBlock()
{
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	m_strBlkName = m_TreeCtrl.GetItemText(hItem);	
	m_TreeCtrl.SelectItem(hItem); //����ѡ�н��
	CString strPath = m_TreeCtrl.GetPath(hItem);
	if (m_TreeCtrl.ItemHasChildren(hItem) && (!m_TreeCtrl.GetParentItem(hItem)))//���ڵ�
	{
		strPath = strPath + m_strBlkName + _T("\\");
	}
	else if (m_TreeCtrl.ItemHasChildren(hItem) && m_TreeCtrl.GetParentItem(hItem))//��ѡΪ�ڵ�
	{
		strPath = strPath + m_strBlkName + _T("\\");
	}
	BeginEditorCommand();
	if (!addBlockToPath(strPath))
	{
		CancelEditorCommand();
		return;
	}
	m_TreeCtrl.DisPlayTree(_T("�豸"), TRUE);
	hItem = m_TreeCtrl.GetRootItem();
	hItem = FindItem(hItem);
	if (hItem == NULL)
	{
		HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
		HTREEITEM hChild = m_TreeCtrl.GetChildItem(hRoot);
		m_TreeCtrl.Expand(hRoot, TVE_EXPAND);
		m_TreeCtrl.Expand(hChild, TVE_EXPAND);

		HTREEITEM hNextItem = m_TreeCtrl.GetChildItem(hChild);
		m_strFileName = m_TreeCtrl.GetFullPath(hNextItem) + _T(".dwg");
	}
	else
	{
		m_strBlkName = m_TreeCtrl.GetItemText(hItem);	
	}
	CompleteEditorCommand();
}

void CDlgDrawEquipment::OnDelBlock()
{
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	m_strBlkName = m_TreeCtrl.GetItemText(hItem);	
	m_TreeCtrl.SelectItem(hItem); //����ѡ�н��
	m_strFileName = m_TreeCtrl.GetFullPath(hItem) + _T(".dwg");
	ClearDatabase();
	BOOL bIsOk = ::DeleteFile(m_strFileName);
	if (!bIsOk)
	{
		CString strTmp;
		strTmp.Format(_T("%s�ļ�����ռ��״̬�����ȹر��ļ�"), m_strFileName);
		AfxMessageBox(strTmp);
	}
	m_TreeCtrl.DisPlayTree(_T("�豸"), TRUE);
	hItem = m_TreeCtrl.GetRootItem();
	hItem = FindItem(hItem);
	if (hItem == NULL)
	{
		HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
		HTREEITEM hChild = m_TreeCtrl.GetChildItem(hRoot);
		m_TreeCtrl.Expand(hRoot, TVE_EXPAND);
		m_TreeCtrl.Expand(hChild, TVE_EXPAND);

		HTREEITEM hNextItem = m_TreeCtrl.GetChildItem(hChild);
		m_strFileName = m_TreeCtrl.GetFullPath(hNextItem) + _T(".dwg");
	}
	else
	{
		m_strBlkName = m_TreeCtrl.GetItemText(hItem);	
	}
}

