#pragma once
//绘制纵断面图形
#include "Utils.h"
#include "BcUtils.h"
#include "ZdmDataInfo.h"
#include "CBiaochiForRQY.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//绘制纵断面的具体流程
class CDrawZDM
{
public:
	CDrawZDM(void);
	~CDrawZDM(void);
	CDrawZDM(CZdmDataInfo* pZDM);
	//处理编组
	AcDbObjectId Draw();

	void setData(CZdmDataInfo* pZDM);
	
	AcDbObjectId insert();
private:
	//初始数据获取
	bool initdata();
	//
	bool DrawLine();
	//绘制地面线相关的文字
	bool DrawDMText();
	//绘制管道相关的文字
	bool DrawXMText();

	//************************************
	// Method:    DrawSMXLine
	// FullName:  CDrawZDM::DrawSMXLine
	// Access:    private 
	// Returns:   bool
	// Qualifier: 根据现状水面线数据及设计水面线数据绘制两条水面线
	//************************************
	bool DrawSMXLine(bool bIsDeFault = true);

	//************************************
	// Method:    AddObjToDict
	// FullName:  CDrawZDM::AddObjToDict
	// Access:    private 
	// Returns:   bool
	// Qualifier: 先找strlabel所在的group，然后打开往group中添加实体id
	// Parameter: CString strLabel
	// Parameter: AcDbObjectId objId
	//************************************
	bool AddObjToDict(CString strLabel, AcDbObjectId objId);

	bool ModifyDictbyInt(int nCur);

	//************************************
	// Method:    ChangeDictName
	// FullName:  CDrawZDM::ChangeDictName
	// Access:    private 
	// Returns:   bool
	// Qualifier: 将原始strPreGroupName改为strGroupName
	// Parameter: CString strGroupName
	// Parameter: CString strPreGroupName
	//************************************
	bool ChangeDictName(CString strGroupName, CString strPreGroupName, bool bIsDeFault = true);

private:
	CZdmDataInfo m_pZDM;
	AcDbObjectIdArray m_idArrs;
	double m_dLen;
	double m_dWidth;
	double m_dXScale;
	double m_dYScale;
};
