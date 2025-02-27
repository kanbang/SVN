#include "StdAfx.h"
#include "BcUtils.h"

CBcUtils::CBcUtils(void)
{
	m_Data.clear();
}

CBcUtils::~CBcUtils(void)
{
	m_Data.clear();
}

bool CBcUtils::add( LPCTSTR strLabel, CZdmDataInfo data)
{
	//将数据写入dictionary中
	getAllData();
	map<CString, CZdmDataInfo>::iterator iter = m_Data.find(strLabel);	
	AcDbObjectId StyleId;

	if (iter == m_Data.end())//如果dictionary中没有就添加记录
	{
		AcDbDictionary* testDict = MyBaseUtils::openDictionaryForWrite(
			CBiaochiForRQY::dictName(), true,
			acdbHostApplicationServices()->workingDatabase());

		Acad::ErrorStatus es;
		if (testDict->getAt(strLabel, StyleId) != Acad::eOk)
		{
			CBiaochiForRQY* newRec = new CBiaochiForRQY;

			newRec->setLabel(data.label());
			newRec->setCount(data.getCount());
			newRec->setDesignDmx(data.getDesignDmx());
			newRec->setRealDmx(data.getRealDmx());
			newRec->setJiedian(data.getJiedian());
			newRec->setGuanDi(data.getGuanDi());
			newRec->setWaShen(data.getWaShen());
			newRec->setPoDu(data.getPoDu());
			newRec->setJuli(data.getJuli());
			newRec->setcurData(data.getcurData());
			////////////////////
			newRec->setHasBulge(data.getHasBulge());
			newRec->setDesingDmxS(data.getDesingDmxS());
			newRec->setRealDmxS(data.getRealDmxS());
			newRec->setJiedianS(data.getJiedianS());

			es = testDict->setAt(strLabel, newRec, StyleId);
			if (es == Acad::eOk) 
			{
				newRec->close();
			}
			else 
			{
				delete newRec;
				StyleId = AcDbObjectId::kNull;
			}
		}

		testDict->close();
	}
	else//如果有，就表示要修改当前数据
	{
		modify(strLabel, data);
	}
	return true;
}

bool CBcUtils::insert( LPCTSTR strLabel, CZdmDataInfo data)
{
	getAllData();
	map<CString, CZdmDataInfo>::iterator iter = m_Data.find(strLabel);
	if (iter == m_Data.end())
	{
		//没有找到，说明插入的数据不对，不能在那个位置插入数据
		return false;
	}
	else
	{
		//倒序查找
		for (map<CString, CZdmDataInfo>::reverse_iterator iRevers = m_Data.rbegin();
			iRevers != m_Data.rend(); ++iRevers)
		{
			//CZdmDataInfo data = iRevers->second;
			CString strName = iRevers->first;
			if (strName.CompareNoCase(strLabel) == 0)
			{
				break;
			}
			CString strCount = iRevers->second.getCount();
			int nCount = MyTransFunc::StringToInt(strCount);
			nCount++;
			strName = BC_DICT + strCount;
			iRevers->second.setCount(strCount);
			iRevers->second.setLabel(strName);
		}

		m_Data.insert(make_pair(strLabel, data));
		//删除所有，然后添加
		delAll();
		addAll();
	}
	return true;
}

bool CBcUtils::modify( LPCTSTR strLabel, CZdmDataInfo pData )
{
	getAllData();
	map<CString, CZdmDataInfo>::iterator iter = m_Data.find(strLabel);
	if (iter == m_Data.end())
	{
		//没有找到
		return false;
	}
	else	
	{
		//CZdmDataInfo tmpData = iter->second;
		iter->second.setLabel(pData.label());
		iter->second.setCount(pData.getCount());
		iter->second.setDesignDmx(pData.getDesignDmx());
		iter->second.setRealDmx(pData.getRealDmx());
		iter->second.setJiedian(pData.getJiedian());
		iter->second.setGuanDi(pData.getGuanDi());
		iter->second.setWaShen(pData.getWaShen());
		iter->second.setPoDu(pData.getPoDu());
		iter->second.setJuli(pData.getJuli());
		iter->second.setcurData(pData.getcurData());
		////////////////////
		iter->second.setHasBulge(pData.getHasBulge());
		iter->second.setDesingDmxS(pData.getDesingDmxS());
		iter->second.setRealDmxS(pData.getRealDmxS());
		iter->second.setJiedianS(pData.getJiedianS());

		//删除所有，然后添加
		delAll();
		addAll();
	}
	return true;
}
//
bool CBcUtils::del( LPCTSTR strLabel )
{
	getAllData();
	map<CString, CZdmDataInfo>::iterator iter = m_Data.find(strLabel);
	if (iter != m_Data.end())
	{
		//倒序查找
		bool bIsErased = false;
		for (map<CString, CZdmDataInfo>::iterator iTr = m_Data.begin();
			iTr != m_Data.end();)
		{
			CZdmDataInfo data = iTr->second;
			CString strName = iTr->first;
			if (strName.CompareNoCase(strLabel) == 0)
			{
				m_Data.erase(iTr++);
				bIsErased = true;
			}
			else
			{
				if (bIsErased)
				{
					CString strCount = data.getCount();
					int nCount = MyTransFunc::StringToInt(strCount);
					nCount--;
					strName = _T("ZW_FOR_WHRQY_") + strCount;
					data.setCount(strCount);
				}	
				++iTr;
			}	
		}
		//删除所有，然后添加
		delAll();
		addAll();
	}
	else
	{
		//没有这个元素
		return false;
	}
	return true;
}

CZdmDataInfo CBcUtils::get( LPCTSTR strLabel )
{
	getAllData();
	map<CString, CZdmDataInfo>::iterator iter = m_Data.find(strLabel);
	CZdmDataInfo bcData = iter->second;
	return bcData;
}

//************************************
// Method:    getCount
// FullName:  CBcUtils::getCount
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
//int CBcUtils::getCount()
//{
//	getAllData();
//	int nCount = m_Data.size();
//	return nCount;
//}

map<CString, CZdmDataInfo> CBcUtils::getAllData()
{
	AcDbDictionary* testDict = MyBaseUtils::openDictionaryForRead(
		CBiaochiForRQY::dictName(),	acdbHostApplicationServices()->workingDatabase());
	Acad::ErrorStatus es;
	//如果没有数据直接退出
	if (testDict == NULL)
	{
		return m_Data;
	}

	AcDbDictionaryIterator* pIter = testDict->newIterator();
	for (; !pIter->done(); pIter->next())
	{
		AcDbObject* pObj = NULL;
		es = pIter->getObject(pObj, AcDb::kForRead);
		if (pObj->isKindOf(CBiaochiForRQY::desc()))
		{
			CZdmDataInfo data;
			CBiaochiForRQY* pEnt = CBiaochiForRQY::cast(pObj);
			data.setLabel(pEnt->label());
			data.setCount(pEnt->getCount());
			data.setDesignDmx(pEnt->getDesignDmx());
			data.setRealDmx(pEnt->getRealDmx());
			data.setJiedian(pEnt->getJiedian());
			data.setGuanDi(pEnt->getGuanDi());
			data.setWaShen(pEnt->getWaShen());
			data.setPoDu(pEnt->getPoDu());
			data.setJuli(pEnt->getJuli());
			data.setcurData(pEnt->getcurData());
			////////////////////
			data.setHasBulge(pEnt->getHasBulge());
			data.setDesingDmxS(pEnt->getDesingDmxS());
			data.setRealDmxS(pEnt->getRealDmxS());
			data.setJiedianS(pEnt->getJiedianS());
			m_Data.insert(make_pair(pEnt->label(), data));
		}
		es = pObj->close();	
	}
	delete pIter;
	
	testDict->close();
	return m_Data;
}

void CBcUtils::addAll()
{
	AcDbObjectId StyleId;
	AcDbDictionary* testDict = MyBaseUtils::openDictionaryForWrite(
		CBiaochiForRQY::dictName(), true,
		acdbHostApplicationServices()->workingDatabase());

	Acad::ErrorStatus es;

	for (map<CString, CZdmDataInfo>::iterator iter = m_Data.begin();
		iter != m_Data.end();
		++iter)
	{
		CString strLable = iter->first;
		CZdmDataInfo data = iter->second;
		if (testDict->getAt(strLable, StyleId) != Acad::eOk)
		{
			CBiaochiForRQY* newRec = new CBiaochiForRQY;

			newRec->setLabel(data.label());
			newRec->setCount(data.getCount());
			newRec->setDesignDmx(data.getDesignDmx());
			newRec->setRealDmx(data.getRealDmx());
			newRec->setJiedian(data.getJiedian());
			newRec->setGuanDi(data.getGuanDi());
			newRec->setWaShen(data.getWaShen());
			newRec->setPoDu(data.getPoDu());
			newRec->setJuli(data.getJuli());
			newRec->setcurData(data.getcurData());
			////////////////////
			newRec->setHasBulge(data.getHasBulge());
			newRec->setDesingDmxS(data.getDesingDmxS());
			newRec->setRealDmxS(data.getRealDmxS());
			newRec->setJiedianS(data.getJiedianS());

			es = testDict->setAt(strLable, newRec, StyleId);
			if (es == Acad::eOk) 
			{
				newRec->close();
			}
			else 
			{
				delete newRec;
				StyleId = AcDbObjectId::kNull;
			}
		}
	}
	testDict->close();
}

void CBcUtils::delAll()
{
	AcDbDictionary* testDict = MyBaseUtils::openDictionaryForWrite(
		CBiaochiForRQY::dictName(), true,
		acdbHostApplicationServices()->workingDatabase());
	Acad::ErrorStatus es;

	AcDbDictionaryIterator* pIter = testDict->newIterator();
	for (; !pIter->done(); pIter->next())
	{
		AcDbObjectId entId = pIter->objectId();
		testDict->remove(entId);
	}
	delete pIter;

	testDict->close();
}
