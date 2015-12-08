
//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("")
#include ".\base\Inc\Global.h"
#include "DlgTKManage.h"
#include "DlgDrawGD.h"
#include "GDDataInDWG.h"
#include "DlgFindBlock.h"
#include "DlgDrawEquipment.h"
#include "DlgDrawInstrument.h"
#include "CutEntity.h"
#include "DlgSQLDbSet.h"
#include "DlgSQLDB.h"
#include "OperateReg.h"
#include "MyEditEntity.h"
#include "DlgInsertOther.h"
#include "BlkInfo.h"
#include "DlgCreateNewBlk.h"
#include "DataStore.h"
#include "CreateTuli.h"
#include "DlgEquipmentStats.h"
#include "OperateReg.h"
#include "BaseDataInDwg.h"
#include "CObjectAppendToDb.h"
#include "CAppEditorReactor.h"
CObjectAppendToDb* m_dbReactor = NULL;
CAppEditorReactor* m_dbEditorReactor = NULL;

CDlgFindBlock* FindBlkDlg = NULL;
Adesk::Boolean startFINDBLKDlg()
{
	CAcModuleResourceOverride resOverride;
	HWND hwndAcad = adsw_acadMainWnd();

	if ( !hwndAcad ) 
	{
		AfxMessageBox( _T("Unable to locate AutoCAD parent window.") );
		return Adesk::kFalse;
	}

	CWnd *pWnd = CWnd::FromHandle ( hwndAcad );
	if( FindBlkDlg == NULL ) 
	{
		if ( (FindBlkDlg = new CDlgFindBlock ( pWnd )) == NULL ) 
		{
			AfxMessageBox ( _T("Unable to allocate a CMDITestDialog.") );
			return Adesk::kFalse;
		}
		BOOL succeeded = FindBlkDlg->Create ( pWnd );
		if ( !succeeded ) 
		{
			AfxMessageBox ( _T("Unable to create the dialog.") );
			return Adesk::kFalse;
		}
	}
	FindBlkDlg->ShowWindow(SW_SHOWNORMAL);

	return Adesk::kTrue;
}

Adesk::Boolean endFINDBLKDlg()
{
	if ( !FindBlkDlg )
		return Adesk::kTrue;

	BOOL ok = FindBlkDlg->DestroyWindow();
	delete FindBlkDlg;
	FindBlkDlg = NULL;

	return ok;
}

//attach all
void attachDbReactorToAll()
{
	if (m_dbReactor == NULL) 
	{
		m_dbReactor = new CObjectAppendToDb;
		AcDbDatabase* tmpDb;
		AcDbVoidPtrArray dbPtrs;
		ArxDbgUtils::getAllDatabases(dbPtrs);

		//acutPrintf(_T("\nAttaching Database Reactor to all active databases..."));

		int len = dbPtrs.length();
		for (int i=0; i<len; i++) {
			tmpDb = static_cast<AcDbDatabase*>(dbPtrs[i]);
			tmpDb->addReactor(m_dbReactor);
		}
	}
}
//Remove DbReactor
void removeDbReactorFromAll()
{
	if (m_dbReactor != NULL) 
	{
		AcDbDatabase* tmpDb;
		AcDbVoidPtrArray dbPtrs;
		ArxDbgUtils::getAllDatabases(dbPtrs);

		acutPrintf(_T("\nRemoving Database Reactor from all active databases..."));

		int len = dbPtrs.length();
		for (int i=0; i<len; i++) {
			tmpDb = static_cast<AcDbDatabase*>(dbPtrs[i]);
			tmpDb->removeReactor(m_dbReactor);
		}
	}
}
//�������˵��
bool DoUpDate()
{
	bool bRet = false;
	COperateReg reg;
	BOOL bNoticeUpdate;
	bNoticeUpdate = (BOOL)reg.GetDwordFromReg(_T("Software\\ZWSOFT\\ZWSQL"), _T("NOTICEUPDATE"));
	if (bNoticeUpdate)
	{
		CTime curTime;
		curTime = CTime::GetCurrentTime();
		int nCurYear,nCurMonth,nCurDay,nYear,nMonth,nDay;
		nCurYear = curTime.GetYear();
		nCurMonth = curTime.GetMonth();
		nCurDay = curTime.GetDay();
		nYear = reg.GetDwordFromReg(_T("Software\\ZWSOFT\\ZWSQL"), _T("YEAR"));
		nMonth = reg.GetDwordFromReg(_T("Software\\ZWSOFT\\ZWSQL"), _T("MONTH"));
		nDay = reg.GetDwordFromReg(_T("Software\\ZWSOFT\\ZWSQL"), _T("DAY"));
		if (nYear > nCurYear)
		{
			return true;
		}
		else if (nYear < nCurDay)
		{
			return false;
		}
		else
		{
			if (nMonth > nCurMonth)
			{
				return true;
			}
			else if (nMonth < nCurMonth)
			{
				return false;
			}
			else
			{
				if (nDay - nCurDay >= 7)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include "CAcadApplication.h"
#include "CAcadDocument.h"
#include "CAcadModelSpace.h"
#include "CAcadMenuBar.h"
#include "CAcadMenuGroup.h"
#include "CAcadMenuGroups.h"
#include "CAcadPopupMenu.h"
#include "CAcadPopupMenus.h"
//����cui�ļ�
bool LoadPartialMenu(const TCHAR* filePath   //�ֲ��˵��ļ���  
					 ,const TCHAR* menuGroupName  )

{
	//����еĻ���ж��

	long i, menuGroupNum;   //�˵�����Ŀ

	VARIANT index;

	VariantInit(&index);

	index.vt = VT_I4;

	CString strGroupName(menuGroupName);

	CAcadApplication acadApp(acedGetAcadWinApp()->GetIDispatch(TRUE));

	CAcadMenuGroups menuGroups(acadApp.get_MenuGroups());

	CAcadMenuGroup menuGroup;

	menuGroupNum = menuGroups.get_Count();

	for (i = 0; i < menuGroupNum; i++) {

		index.lVal = i;

		menuGroup = menuGroups.Item(index);

		if (menuGroup.get_Name() == strGroupName) {

			menuGroup.Unload();

			break;
			//return false;

		}

	}

	//���ز˵�

	VARIANT BaseMenu;   //�Ƿ����Ϊ�����˵�

	VariantInit(&BaseMenu);

	BaseMenu.vt = VT_BOOL;

	BaseMenu.boolVal = FALSE;

	menuGroup = menuGroups.Load(CString(filePath), BaseMenu);
	// �Ѳ˵��ڲ˵�������ʾ����

	CAcadMenuBar menuBar(acadApp.get_MenuBar());  //��ǰ�˵���

	CAcadPopupMenus popupMenus(menuGroup.get_Menus()); //Ҫ����Ĳ˵���

	CAcadPopupMenu popupMenu;

	long curPopupMenuNum = menuBar.get_Count();   //��ǰ�˵����ϲ˵�����Ŀ

	long n = popupMenus.get_Count();

	for (long i = 0; i < n; i++) {

		index.lVal = i;

		popupMenu = popupMenus.Item(index);

		index.lVal = i + curPopupMenuNum;

		popupMenu.InsertInMenuBar(index);

	}

	return true;

}
static void initLoadMenu()
{
	TCHAR buf[1000];
#ifdef ARX
	DWORD pathLength =GetModuleFileName(GetModuleHandle(_T("ZwForTRS.arx")),buf,1000);
#else
	DWORD pathLength =GetModuleFileName(GetModuleHandle(_T("ZwForTRS.zrx")),buf,1000);
#endif
	if(pathLength)
	{
		CString path;
		path = buf;
		path=path.Left(path.ReverseFind('\\'));
		if(path!=_T(""))
		{
			path += _T("\\TRSCAD.mnu");
		}
		LoadPartialMenu(path, _T("TRSCAD"));
	}
}


//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CZwForTRSApp : public AcRxArxApp {

public:
	CZwForTRSApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;

		gGlobal.SetIni(gGlobal.GetIniPath());
		// TODO: Add your initialization code here
		if (DoUpDate())
		{
			AfxMessageBox(_T("��ʹ��IMDB����������ݿ�"));
		}
		CGDDataInDWG::rxInit();
		CBaseDataInDwg::rxInit();
		//CAppEditorReactor::rxInit();
		initLoadMenu();
		acrxBuildClassHierarchy();	
		//////////////////////////////////////////////////////////////////////////
		//����Ӧ��
		if (m_dbEditorReactor == NULL)
		{
			m_dbEditorReactor = new CAppEditorReactor;
			acedEditor->addReactor(m_dbEditorReactor);
		}
		attachDbReactorToAll();
		//////////////////////////////////////////////////////////////////////////

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		
		// TODO: Unload dependencies here
		endFINDBLKDlg();
		//����Ӧ��
		if (m_dbEditorReactor != NULL)
		{
			acedEditor->removeReactor(m_dbEditorReactor);
			delete m_dbEditorReactor;
			m_dbEditorReactor = NULL;
		}
		removeDbReactorFromAll();
		//////////////////////////////////////////////////////////////////////////
		//deleteAcRxClass(CAppEditorReactor::desc());
		deleteAcRxClass(CGDDataInDWG::desc());
		deleteAcRxClass(CBaseDataInDwg::desc());
		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}


	// - ZwForTRS.TK command (do not rename)
	//static void ZwForTRSTK(void)//ͼ��
	//{
		// Add your code for command ZwForTRS.TK here
		/*CAcModuleResourceOverride myResource;
		CDlgTKManage dlg;
		dlg.DoModal();*/
	//}


	// - ZwForTRS.HZGD command (do not rename)
	static void ZwForTRSHZGD(void)//���ƹܵ�
	{
		// Add your code for command ZwForTRS.HZGD here
		CAcModuleResourceOverride rs;
		CDlgDrawGD dlg;
		dlg.DoModal();
	}

	// - ZwForTRS.TKCZ command (do not rename)
	static void ZwForTRSTKCZ(void)//ͼ�����
	{
		// Add your code for command ZwForTRS.TKCZ here
		if( FindBlkDlg ) 
		{		
			FindBlkDlg->ShowWindow( SW_SHOWNORMAL );
			return;
		}

		if( !FindBlkDlg && !startFINDBLKDlg() ) 
		{
			ads_printf( _T("Failed to create modeless dialog box.\n") );
		}
	}

	// - ZwForTRS.LEGEND command (do not rename)
	static void ZwForTRSLEGEND(void)//����ͼ��
	{
		// Add your code for command ZwForTRS.LEGEND here
		CCreateTuli tuli;
		tuli.doIt();
	}

	// - ZwForTRS.CRSB command (do not rename)
	static void ZwForTRSCRSB(void)//�����豸
	{
		// Add your code for command ZwForTRS.CRSB here
		acedCommand(RTSTR, _T("wipeout"), RTSTR, _T("F"), RTSTR, _T("off"), RTNONE);
		CAcModuleResourceOverride rs;
		CDlgDrawEquipment dlg;
		dlg.DoModal();
	}

	// - ZwForTRS.CRYB command (do not rename)
	static void ZwForTRSCRYB(void)//�����Ǳ�
	{
		// Add your code for command ZwForTRS.CRYB here	
		acedCommand(RTSTR, _T("wipeout"), RTSTR, _T("F"), RTSTR, _T("off"), RTNONE);
		CAcModuleResourceOverride rs;
		CDlgDrawInstrument dlg;
		dlg.DoModal();	
	}

	// - ZwForTRS.test command (do not rename)

	static void ZwForTRSDBSET(void)//����
	{
		// Add your code for command ZwForTRS.test here
		//CCutEntity cut;
		//cut.doIt();
		CAcModuleResourceOverride rs;
		CDlgSQLDbSet dlg;
		dlg.DoModal();
		/*COperateCsv csv;
		csv.SetFileName(_T("D:\\aa.csv"));
		csv.Read();*/

		/*
		//�ж��ļ��Ƿ����ûд
		CDataStore data;
		vector<CString> m_Fitem(5, _T("ss"));
		vector<CString> m_Fname(5, _T("name"));
		vector<CString> m_F105(5, _T("1"));
		vector<CString> m_F106(5, _T("20"));
		data.SetF105Vec(m_F105);
		data.SetF106Vec(m_F106);
		data.SetFItemVec(m_Fitem);
		data.SetFNameVec(m_Fname);
		COperateCsv csv;
		csv.SetFileName(_T("D:\\bb.csv"));
		csv.SetData(data);
		csv.Write();*/
		
		//bRet = db.CheckLayer();

	}

	// - ZwForTRS.ImportDB command (do not rename)
	static void ZwForTRSImportDB(void)
	{
		// Add your code for command ZwForTRS.ImportDB here
#ifndef UNICODE
		CString strRootKey = _T("Software\\ZWSOFT\\ZWSQL");
		CString strAddress;
		COperateReg Reg;
		TCHAR ResStr[MAX_PATH];
		if (Reg.GetRegister(HKEY_CURRENT_USER, strRootKey,  _T("ADDRESS"), _T(""), ResStr) > 0)
		{
			strAddress = ResStr;
		}
		if (strAddress.IsEmpty())
		{
			AfxMessageBox(_T("��һ�����д˳�����ָ�����ݿ�"));
		}
#endif
		CAcModuleResourceOverride rs;
		CDlgSQLDB dlg;
		dlg.DoModal();
	}

	// - ZwForTRS.ModEquip command (do not rename)
	static void ZwForTRSModEquip(void)//�޸��豸
	{
		// Add your code for command ZwForTRS.ModEquip here
		ads_name ename;
		AcGePoint3d pt;
		int nRet = acedEntSel(_T("\n��ѡ��Ҫ�޸ĵ�ʵ��"), ename, asDblArray(pt));
		if (nRet != RTNORM)
		{
			return;
		}
		AcDbObjectId objId = AcDbObjectId::kNull;
		acdbGetObjectId(objId, ename);
		AcDbEntity* pEnt = NULL;
		if (acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead)!= Acad::eOk)
		{
			return;
		}
		CString strTmp;
		AcGePoint3d insertPt;
		if (pEnt->isKindOf(AcDbBlockReference::desc()))
		{	
			AcDbBlockReference* pBlkRef = AcDbBlockReference::cast(pEnt);
			insertPt = pBlkRef->position();
			CString strBlockname;
			ArxDbgUtils::symbolIdToName(pBlkRef->blockTableRecord(), strBlockname);
			pBlkRef->close();
			strTmp = MyEditEntity::GetObjStrXdata(objId, ZRXDBG_TYPE);
			if (strTmp.IsEmpty())
			{	
				pEnt->close();
				AfxMessageBox(_T("û��ѡ���豸������"));
				return;
			}
			else if (strTmp.CompareNoCase(_T("�豸")) == 0)
			{
				gGlobal.SetIniValue(_T("�����豸"), _T("����"), strBlockname);
				CAcModuleResourceOverride rs;
				CDlgDrawEquipment dlg;
				dlg.SetInsertPt(insertPt);
				dlg.SetModified(true);
				if (dlg.DoModal() == IDOK)
				{
					MyEditEntity::EraseObj(objId);
				}
			}
			else if (strTmp.CompareNoCase(_T("����")) == 0)
			{
				gGlobal.SetIniValue(_T("��������"), _T("����"), strBlockname);
				CAcModuleResourceOverride rs;
				CDlgDrawInstrument dlg;
				dlg.SetInsertPt(insertPt);
				dlg.SetModified(true);
				if (dlg.DoModal() == IDOK)
				{
					MyEditEntity::EraseObj(objId);
				}
			}
		}
		else
		{
			pEnt->close();
			AfxMessageBox(_T("û��ѡ���豸������"));
			return;
		}
	}

	// - ZwForTRS.ModInstrument command (do not rename)
	//static void ZwForTRSModInstrument(void)//�޸��Ǳ�
	//{
	//	// Add your code for command ZwForTRS.ModInstrument here
	//}

	// - ZwForTRS.InsertOther command (do not rename)
	static void ZwForTRSInsertOther(void)//��������ͼ��
	{
		// Add your code for command ZwForTRS.InsertOther here
		acedCommand(RTSTR, _T("wipeout"), RTSTR, _T("F"), RTSTR, _T("off"), RTNONE);
		CAcModuleResourceOverride rs;
		CDlgInsertOther dlg;
		dlg.DoModal();
	}

	// - ZwForTRS.CreateBlk command (do not rename)
	static void ZwForTRSCreateBlk(void)//�����¿�
	{
		// Add your code for command ZwForTRS.CreateBlk here
		CAcModuleResourceOverride rs;
		CDlgCreateNewBlk dlg;
		dlg.DoModal();
	}

	// - ZwForTRS.CollectEquipment command (do not rename)
	static void ZwForTRSCollectEquipment(void)//�豸ͳ��
	{
		// Add your code for command ZwForTRS.CollectEquipment here
		CAcModuleResourceOverride rs;
		CDlgEquipmentStats dlg;
		dlg.DoModal();
	}
//#ifndef UNICODE
//#include "OperateBom.h"
//	static void ZwForTRSSCMX(void)//������ϸ
//	{
//		// Add your code for command ZwForTRS.CollectEquipment here
//		COperateBom bom;
//		bom.DoIt();
//	}
//#endif
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CZwForTRSApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, HZGD, DRAWGD, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, TKCZ, TKCZ, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, LEGEND, SCTL, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, CRSB, CS, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, CRYB, CB, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, DBSET, DBSET, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, ImportDB, IMDB, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, ModEquip, XGSB, ACRX_CMD_TRANSPARENT, NULL)
//ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, ModInstrument, XGYQ, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, InsertOther, CRQT, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, CreateBlk, CJXK, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, CollectEquipment, SBTJ, ACRX_CMD_TRANSPARENT, NULL)
//#ifndef UNICODE
//ACED_ARXCOMMAND_ENTRY_AUTO(CZwForTRSApp, ZwForTRS, SCMX, SCMX, ACRX_CMD_TRANSPARENT, NULL)
//#endif
