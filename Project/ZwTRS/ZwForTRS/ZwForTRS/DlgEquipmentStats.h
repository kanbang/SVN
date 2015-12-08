

//-----------------------------------------------------------------------------
//----- DlgEquipmentStats.h : Declaration of the CDlgEquipmentStats
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "acui.h"
#include "BlkInfo.h"
#include "IniFile.h"
#include "CEBExcelOperate.h"
#include <map>
#include <vector>
#include <utility>
#include "DataSort.h"
#include "afxwin.h"
using namespace std;
//-----------------------------------------------------------------------------
class CDlgEquipmentStats : public CAcUiDialog {
	DECLARE_DYNAMIC (CDlgEquipmentStats)

public:
	CDlgEquipmentStats (CWnd *pParent =NULL, HINSTANCE hInstance =NULL) ;
	~CDlgEquipmentStats();

	enum { IDD = IDD_DLGEQUIPMENTSTATS} ;

protected:
	virtual void DoDataExchange (CDataExchange *pDX) ;
	afx_msg LRESULT OnAcadKeepFocus (WPARAM, LPARAM) ;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	bool SelectEnt();
	void GetEntInfoById(AcDbObjectId objId);

	//����ļ�
	bool OutPutFile();
	//������д��XLS��
	bool WriteData();

	
private:
	//��һ��������¼����ͼ��ţ��ڶ���������¼�������Ϣ������
	//map<CString, pair<CDataBaseInfo*, int> > m_Data;
	vector<pair<CString, CDataBaseInfo*> > m_Data;
	int m_nStart;//excel������ʼλ��
	int m_nCombine;//excel�ϲ�����
	CString m_strFileName;//�ļ���
	CDataSort m_dataSort;//
	//Excel������
	vector<pair<CString, DataVec> > m_ExcelData;
	//���ݷ���
	map<CString, vector<CString> > m_strData;

	//vector<pair<CString, CDataBaseInfo*> > m_DataTmp;
public:
	// ģ��
	CComboBox m_CombTemplate;
	CString m_strTemplate;
	afx_msg void OnCbnSelchangeComboModel();
} ;
