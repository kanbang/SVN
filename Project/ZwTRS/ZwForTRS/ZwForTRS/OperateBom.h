#pragma once

#include "ZwmToolKitExtLib.h"
#include "zwm.h"
#include "DataBaseInfo.h"
#include <map>
#include <vector>
#include <utility>
//using namespace std;
//����bom��
class COperateBom
{
public:
	COperateBom(void);
	~COperateBom(void);
	//////////////////////////////////////////////////////////////////////////
	bool DoIt();

private:
	//ѡ��ʵ��
	bool SelectEnt();
	//��������ӵ�bom
	bool AddDataToBom();
	//��ȡBom����bom����������
	bool GetBom();
	//����Bom������
	bool SetBom(CDataBaseInfo* pData, int nCount);
	//����bom��������
	ZwcadmBomRow SetBomCell();
	//param objIdΪ�����id
	void GetEntInfoById(AcDbObjectId objId);

private:
	ZwcadmApp m_appZwm;
	ZwcadmDb* m_pZwmDb;
	ZwcadmBom* m_pBom;
	//��һ��������¼����ͼ��ţ��ڶ���������¼�������Ϣ������
	map<CString, pair<CDataBaseInfo*, int> > m_Data;
};
