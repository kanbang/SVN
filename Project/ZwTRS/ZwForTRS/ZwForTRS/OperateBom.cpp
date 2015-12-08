#include "StdAfx.h"
#include "OperateBom.h"
#include "DataBaseInfo.h"
#include "MyEditEntity.h"

COperateBom::COperateBom(void)
{
	for (map<CString, pair<CDataBaseInfo*, int> >::iterator iter = m_Data.begin();
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
	m_Data.clear();
}

COperateBom::~COperateBom(void)
{
	for (map<CString, pair<CDataBaseInfo*, int> >::iterator iter = m_Data.begin();
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
	m_Data.clear();
}


bool COperateBom::DoIt()
{
	if (!GetBom())
	{
		return false;
	}
	if (!SelectEnt())
	{
		return false;
	}

	pair<CDataBaseInfo*, int> tmpPair;
	int nIndex = 1;
	for (map<CString, pair<CDataBaseInfo*, int> >::iterator iter = m_Data.begin();
		iter != m_Data.end();
		++iter)
	{
		CDataBaseInfo* pData = NULL;
		tmpPair = iter->second;
		pData = tmpPair.first;
		SetBom(pData, nIndex);
		nIndex++;

	}
	return true;
}

//ѡ��ʵ��
bool COperateBom::SelectEnt()
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
			
			pBlkRef->close();

			GetEntInfoById(objId);
		}
		else
		{
			pEnt->close();
		}
	}
	
	acedSSFree(ssname);
	return true;
}
//��������ӵ�bom
bool COperateBom::AddDataToBom()
{
	return true;
}
//��ȡBom����bom����������
bool COperateBom::GetBom()
{
	m_pZwmDb = m_appZwm.GetDb();
	if (m_pZwmDb)
	{
		m_pZwmDb->OpenFile(_T(""));
	}
	if (m_pZwmDb == NULL)
	{
		return false;
	}
	m_pBom = m_pZwmDb->GetBom();
	if (m_pBom == NULL)
	{
		return false;
	}
	////test
	//ZwcadmBomRow objBomRow;
	//m_pBom->GetItem(0, objBomRow);


	//CStringArray strArr;
	//strArr.RemoveAll();
	//objBomRow.GetLabels(strArr);
	//vector<CString> vec1;
	//vector<CString> vec2;
	//for (int i=0; i<strArr.GetSize(); i++)
	//{
	//	vec1.push_back(strArr.GetAt(i));
	//}
	//strArr.RemoveAll();
	//objBomRow.GetNames(strArr);
	//for (int i=0; i<strArr.GetSize(); i++)
	//{
	//	vec2.push_back(strArr.GetAt(i));
	//}
	//int nItemCount = objBomRow.GetItemCount();
	//for (int i=0; i<nItemCount; i++)
	//{		
	//	CString strLabel,strName,strValue;
	//	objBomRow.GetItem(i, strLabel, strName, strValue);

	//}
	//���bom���������
	
	//m_pBom->RomoveAll();
	return true;
}

//����Bom������
bool COperateBom::SetBom(CDataBaseInfo* pData, int nCount)
{
	ZwcadmBomRow objBomRow;

	CString strXuhao;
	strXuhao.Format(_T("%d"), nCount);
	objBomRow.SetItem(_T("���"), strXuhao);
	objBomRow.SetItem(_T("����"), pData->GetFName());
	objBomRow.SetItem(_T("����"), pData->GetFNumber());
	objBomRow.SetItem(_T("����"), pData->GetShuliang());
	objBomRow.SetItem(_T("����"), pData->GetCailiao());
	objBomRow.SetItem(_T("����"), pData->GetDanzhong());
	objBomRow.SetItem(_T("����"), pData->GetZongzhong());
	objBomRow.SetItem(_T("��ע"), pData->GetBeizhu());
	objBomRow.SetItem(_T("��λ"), pData->GetDanwei());
	objBomRow.SetItem(_T("�������"), pData->GetFErpCls());
	objBomRow.SetItem(_T("�ȴ���"), pData->GetReChuli());
	objBomRow.SetItem(_T("���洦��"), pData->GetBiaoMianChuli());
	m_pBom->AddItem(objBomRow);
	return true;
}


ZwcadmBomRow COperateBom::SetBomCell()
{
	//COMPNAME ���� COMPDES--����
	//RELQTY--���� COMPMAT--����
	//COMPWT--���� COMPTWT--���� COMPREMARK--��ע
	//COMPUMIS--��λ COMPITEM--�������
	///COMPTSUP--���洦�� COMPTTERM--�ȴ���
	ZwcadmBomRow objBomRow;

	return objBomRow;
}

void COperateBom::GetEntInfoById(AcDbObjectId objId)
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
	pair<CDataBaseInfo*, int> tmpPair;
	int nCount = 1;
	tmpPair.first = dataInfo;
	tmpPair.second = nCount;
	pair<map<CString, pair<CDataBaseInfo*, int> >::iterator, bool> bRet = m_Data.insert(make_pair(strChartNum, tmpPair));
	if (!bRet.second)
	{
		bRet.first->second.second++;
	}
}

