

//-----------------------------------------------------------------------------
//----- DlgEquipmentStats.cpp : Implementation of CDlgEquipmentStats
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "DlgEquipmentStats.h"
#include "Global.h"
#include "MyEditEntity.h"
#include "ArxDbgUtils.h"
//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CDlgEquipmentStats, CAcUiDialog)

BEGIN_MESSAGE_MAP(CDlgEquipmentStats, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(IDOK, &CDlgEquipmentStats::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL, &CDlgEquipmentStats::OnCbnSelchangeComboModel)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CDlgEquipmentStats::CDlgEquipmentStats (CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CDlgEquipmentStats::IDD, pParent, hInstance)
, m_strTemplate(_T(""))
{
	/*for (vector<CDataBaseInfo*>::iterator iter = m_Data.begin();
		iter != m_Data.end();
		++iter)
	{
		CDataBaseInfo* pData = NULL;
		pData = *iter;
		if (pData != NULL)
		{
			delete pData;
		}
	}*/
	m_ExcelData.clear();
	m_strData.clear();
	/*for (map<CString, pair<CDataBaseInfo*, int> >::iterator iter = m_Data.begin();
		iter != m_Data.end();
		++iter)
	{
		CDataBaseInfo* pData = NULL;
		pData = iter->second.first;
		if (pData != NULL)
		{
			delete pData;
			pData = NULL;
		}
	}
	m_Data.clear();*/
	//m_DataCount.clear();
}

CDlgEquipmentStats::~CDlgEquipmentStats()
{
	/*for (vector<CDataBaseInfo*>::iterator iter = m_Data.begin();
		iter != m_Data.end();
		++iter)
	{
		CDataBaseInfo* pData = NULL;
		pData = *iter;
		if (pData != NULL)
		{
			delete pData;
		}
	}*/
	m_ExcelData.clear();
	m_strData.clear();
	/*for (map<CString, pair<CDataBaseInfo*, int> >::iterator iter = m_Data.begin();
		iter != m_Data.end();
		++iter)
	{
		CDataBaseInfo* pData = NULL;
		pData = iter->second.first;
		if (pData != NULL)
		{
			delete pData;
			pData = NULL;
		}
	}*/
	m_Data.clear();
	//m_DataCount.clear();
}

//-----------------------------------------------------------------------------
void CDlgEquipmentStats::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	DDX_Control(pDX, IDC_COMBO_MODEL, m_CombTemplate);
	DDX_CBString(pDX, IDC_COMBO_MODEL, m_strTemplate);
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CDlgEquipmentStats::OnAcadKeepFocus (WPARAM, LPARAM) {
	return (TRUE) ;
}

BOOL CDlgEquipmentStats::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	UpdateData(FALSE);

	//��Ŀ¼����ȡxls�ļ�
	CString strPath = gGlobal.GetAppPath() + _T("ͳ��ģ��\\*.*");
	CStringArray strAllFileNameArr;
	strAllFileNameArr.RemoveAll();
	CFileFind ff;
	BOOL b = FALSE;
	b = ff.FindFile(strPath);

	BOOL bFlgLast = FALSE; //��־�ű��������һ���ļ�
	if(b)
	{
		bFlgLast = FALSE;
	}
	else
	{
		bFlgLast = TRUE;
	}

	while(b || !bFlgLast)
	{
		if (!b)
		{
			bFlgLast = TRUE;
		}	
		if(!ff.IsDirectory()&&!ff.IsDots())
		{
			CString strFilename;
			strFilename = ff.GetFilePath();
			strFilename.MakeUpper();
			if(strFilename.Find(_T(".XLS")) != -1)
			{			
				CString strtemp1;
				strtemp1 = strFilename.Right(strFilename.GetLength() - strFilename.ReverseFind('\\')-1);	
				strAllFileNameArr.Add(strtemp1);// strtemp1);
			}			
		}		
		if(!bFlgLast)
		{
			b = ff.FindNextFile();
		}
	}
	ff.Close();
	
	if (strAllFileNameArr.GetSize() < 1)
	{
		AfxMessageBox(_T("û��ģ���ļ�"));
		return FALSE;
	}
	m_strTemplate = gGlobal.GetIniValue(_T("�豸ͳ��"), _T("ģ����"));
	for (int i=0; i<strAllFileNameArr.GetSize(); i++)
	{
		m_CombTemplate.AddString(strAllFileNameArr.GetAt(i));
	}
	int nCursel = m_CombTemplate.FindString(-1, m_strTemplate);
	if (nCursel == -1)
	{
		nCursel = 0;
	}
	m_CombTemplate.SetCurSel(nCursel);
	m_CombTemplate.GetLBText(m_CombTemplate.GetCurSel(), m_strTemplate);


	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgEquipmentStats::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BeginEditorCommand();
	bool bRet = SelectEnt();
	if (!bRet)
	{
		//AfxMessageBox(_T("û��ѡ��ʵ��"));
		CancelEditorCommand();
		return;
	}
	if (OutPutFile())
	{
		WriteData();
	}
	gGlobal.SetIniValue(_T("�豸ͳ��"), _T("ģ����"), m_strTemplate);
	gGlobal.WriteIniFile();
	CAcUiDialog::OnOK();
	CancelEditorCommand();
}


bool CDlgEquipmentStats::SelectEnt()
{
	bool bRet = false;

	ads_name ssname;
	struct resbuf*	filter=acutBuildList(-4,_T("<and"), RTDXF0, _T("INSERT"), -4, _T("and>"), RTNONE);
	int nRet = acedSSGet(NULL, NULL, NULL, filter, ssname);
	acutRelRb(filter);
	if (nRet != RTNORM)
	{
		return false;
	}
	long sslen;
	acedSSLength(ssname, &sslen);
	ads_name ename;
	AcDbObjectId objId = AcDbObjectId::kNull;
	for (int i=0; i<sslen; i++)
	{
		acedSSName(ssname, i, ename);
		acdbGetObjectId(objId, ename);
		AcDbEntity* pEnt = NULL;
		if (acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead) != Acad::eOk)
		{
			continue;
		}
		int nCount =1;
		if (pEnt->isKindOf(AcDbBlockReference::desc()))
		{
			AcDbBlockReference* pBlkRef = AcDbBlockReference::cast(pEnt);
			CString strBlockName;
			ArxDbgUtils::symbolIdToName(pBlkRef->blockTableRecord(), strBlockName);
			
			pBlkRef->close();

			//CString strChartNum = MyEditEntity::GetObjStrXdata(objId, ZRXDBG_LIUCHENGTU_NUM);
			/*pair<CString, int> tmpPair;
			tmpPair.first = strChartNum;
			tmpPair.second = nCount;*/

			/*pair<map<CString, pair<CString, int> >::iterator, bool > bRet = m_DataCount.insert(strBlockName, tmpPair);
			if (!bRet.second)
			{
				bRet.first->second.second++;
			}	*/
			GetEntInfoById(objId);
		}
		else
		{
			pEnt->close();
		}
	}
	
	acedSSFree(ssname);
	if (m_Data.size() < 1)
	{
		AfxMessageBox(_T("û��ѡ��ʵ��"));
		return false;
	}
	CString strini;
	strini = m_strTemplate.Left(m_strTemplate.Find('.')) + _T(".ini");
	CString strIniFile = gGlobal.GetAppPath() + _T("ͳ��ģ��\\") + strini;
	//if (m_dataSort.setData(m_Data, strIniFile))
	//{	
	//	//map<CString, map<CString, DataVec> > retMap = m_dataSort.getData();
	//	m_ExcelData = m_dataSort.getData();
	//	m_strData = m_dataSort.getStrData();
	//	m_nCombine = m_dataSort.getCombineCount();
	//	m_nStart = m_dataSort.getStart();
	//	if (m_ExcelData.size() < 1)
	//	{
	//		return false;
	//	}
	//}
	//else
	//{
	//	return false;
	//}
	

	return true;
}

void CDlgEquipmentStats::GetEntInfoById(AcDbObjectId objId)
{
	CDataBaseInfo* dataInfo = new CDataBaseInfo();
	dataInfo->SetFItemId(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_DAIHAO));
	dataInfo->SetFName(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_MINGCHENG));
	//dataInfo->SetShuliang(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_SHULIANG));
	dataInfo->SetCailiao(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_CAILIAO));
	dataInfo->SetDanzhong(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_DANZHONG));
	//dataInfo->SetZongzhong(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_ZONGZHONG));
	dataInfo->SetBeizhu(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_BEIZHU));
	dataInfo->SetDanwei(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_DANWEI));
	dataInfo->SetFErpCls(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_LINGJIANLEIXING));
	//dataInfo->SetReChuli(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_RECHULI));
	//dataInfo->SetBiaoMianChuli(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_BIAOMIANCHULI));
	dataInfo->SetFNumber(MyEditEntity::GetObjStrXdata(objId, ZRXDBG_FNUMBER));
	CString strChartNum = MyEditEntity::GetObjStrXdata(objId, ZRXDBG_LIUCHENGTU_NUM);

	pair<CString, CDataBaseInfo*> tmpPair;
	tmpPair.first = strChartNum;
	tmpPair.second = dataInfo;
	m_Data.push_back(tmpPair);
	/*pair<CDataBaseInfo*, int> tmpPair;
	int nCount = 1;
	tmpPair.first = dataInfo;
	tmpPair.second = nCount;
	pair<map<CString, pair<CDataBaseInfo*, int> >::iterator, bool> bRet = m_Data.insert(make_pair(strChartNum, tmpPair));
	if (!bRet.second)
	{
	bRet.first->second.second++;
	}*/
}

bool CDlgEquipmentStats::OutPutFile()
{
	struct resbuf *result = NULL;
	int status = acedGetFileNavDialog(_T("����EXCEL"), _T("*.xls"), _T("XLS"), _T("����EXCELĿ¼"), 1, &result);
	if (status == RTNORM)
	{
		for (resbuf* tp = result; tp!=NULL; tp=tp->rbnext)
		{
			if (tp->restype == 5005)
			{
				m_strFileName = tp->resval.rstring;
			}
		}
		acutRelRb(result);
	}
	else
	{
		return false;
	}


	return true;
}


bool CDlgEquipmentStats::WriteData()
{
	bool bRet = true;

	CMyExcelOperate m_Excel;
	CString strFilename1 = gGlobal.GetAppPath() + _T("ͳ��ģ��\\") + m_strTemplate;
	//ɾ��ͬ�����ļ�
	CFileFind  findFile;
	BOOL bRt = findFile.FindFile(m_strFileName,0);
	if (bRt)
	{
		bRt = DeleteFile(m_strFileName);
		if (!bRt)
		{
			CString strTmp;
			strTmp.Format(_T("%sexcel���ڱ�ռ��,\n�뱣������������ļ������ر�%s����ļ�"), m_strFileName, m_strFileName);
			AfxMessageBox(strTmp);
			return false;
		}
	}

	BOOL bisCopyed = CopyFile(strFilename1, m_strFileName, FALSE);
	if (!bisCopyed)
	{
		AfxMessageBox(_T("ģ��.xls�ļ����ڱ�ռ��״̬��\n�뱣������������ļ������ر�ģ��.xls����ļ�"));
		return false;
	}

	BOOL boo=m_Excel.OpenExcelFile(m_strFileName, _T(""));	
	if(!boo)
		return false;
	CStringList slData;
	std::pair<CString, CString> pairType;
	std::vector<std::pair<CString, CString>> vecType;
	std::pair<int, CString> secondType;
	int i=0;
	CString strCount;

	int nRow = 0;//��¼����	
	
	//for (map<CString, vector<CString> >::iterator iter = m_strData.begin();
	//	iter != m_strData.end();
	//	++iter)
	//{
	//	vector<CString> tmpVec;
	//	tmpVec.clear();
	//	tmpVec = iter->second;
	//	int nCount = 1;//��¼���
	//	//����һ��д������ͼǰ׺
	//	//////////////////////////////////////////////////////////////////////////
	//	//////////////////////////////////////////////////////////////////////////
	//	//////////////////////////////////////////////////////////////////////////

	//	m_Excel.WriteDataEx(m_nCombine*nRow+m_nStart, 1, iter->first);
	//	//Ĭ�ϴӵ�2�п�ʼ��19�н���
	//	m_Excel.MergeCell(m_nCombine*nRow + m_nStart, 2, m_nCombine*nRow + m_nStart, 19, m_nCombine);
	//	nRow++;
	//	//////////////////////////////////////////////////////////////////////////
	//	//////////////////////////////////////////////////////////////////////////
	//	//////////////////////////////////////////////////////////////////////////
	//	for (vector<CString>::iterator iTr = tmpVec.begin();
	//		iTr != tmpVec.end();
	//		++iTr)
	//	{
	//		CString strKey = *iTr;
	//		/*vector<pair<CString, DataVec> >::iterator mapIter = m_ExcelData.find(strKey);
	//		if (mapIter == m_ExcelData.end())
	//		{
	//		continue;
	//		}
	//		else*/
	//		{
	//			
	//			DataVec tmpDataVec = mapIter->second;
	//			bool bFirst = true;
	//			for (DataVec::iterator dataIter = tmpDataVec.begin();
	//				dataIter != tmpDataVec.end();
	//				++dataIter)
	//			{
	//				if (bFirst)
	//				{
	//					strCount.Format(_T("%d"), nCount);
	//					m_Excel.WriteDataEx(m_nCombine*nRow+m_nStart, dataIter->second, strCount);
	//					bFirst = false;
	//				}
	//				else
	//				{
	//					m_Excel.WriteDataEx(m_nCombine*nRow+m_nStart, dataIter->second, dataIter->first);
	//					bFirst = false;
	//				}
	//			}
	//			nCount++;
	//			nRow++;
	//		}
	//	}
	//}
	/*for (map<CString, pair<CDataBaseInfo*, int> >::iterator iter = m_Data.begin();
		iter != m_Data.end();
		++iter)
	{
		strCount.Format(_T("%d"), i);
		slData.RemoveAll();
		m_Excel.WriteDataEx(2*i+12,1,strCount);
		CDataBaseInfo* pDB = iter->second.first;
		m_Excel.WriteDataEx(2*i+12,2,pDB->GetFName());
		m_Excel.WriteDataEx(2*i+12,6,iter->first);
		m_Excel.WriteDataEx(2*i+12,8,pDB->GetBeizhu());
		m_Excel.WriteDataEx(2*i+12,12,pDB->GetCailiao());
		strCount.Format(_T("%d"), iter->second.second);
		m_Excel.WriteDataEx(2*i+12,19, strCount);

		i++;
	}*/

	for (vector<pair<CString, CDataBaseInfo*> >::iterator Iter = m_Data.begin();
		Iter != m_Data.end();
		++Iter)
	{
		//m_Excel.WriteDataEx(m_nCombine*nRow+m_nStart, dataIter->second, strCount);
		strCount.Format(_T("%d"), i+1);
		slData.RemoveAll();
		m_Excel.WriteDataEx(i+12,1,strCount);
		CDataBaseInfo* pDB = Iter->second;
		m_Excel.WriteDataEx(i+12,2,pDB->GetFName());
		m_Excel.WriteDataEx(i+12,3,Iter->first);
		m_Excel.WriteDataEx(i+12,4,pDB->GetCailiao());
		m_Excel.WriteDataEx(i+12,5,pDB->GetDanwei());
		m_Excel.WriteDataEx(i+12, 6, _T("1"));
		/*strCount.Format(_T("%d"), 1);
		m_Excel.WriteDataEx(i+12,19, strCount);*/
		i++;
	}


	boo = m_Excel.CloseExcelFile();
	if (!boo)
	{
		return false;
	}
	ShellExecute(NULL, _T("open"), m_strFileName, NULL, NULL, SW_SHOWNORMAL);
	return bRet;
}


void CDlgEquipmentStats::OnCbnSelchangeComboModel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCursel = m_CombTemplate.GetCurSel();
	if (nCursel == -1)
	{
		nCursel = 0;
	}
	m_CombTemplate.SetCurSel(nCursel);
	m_CombTemplate.GetLBText(m_CombTemplate.GetCurSel(), m_strTemplate);
}
