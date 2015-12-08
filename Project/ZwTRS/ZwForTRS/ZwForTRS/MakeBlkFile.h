#pragma once
#include "DataBaseInfo.h"
#include "BlkRefCsv.h"

class CMakeBlkFile//����blkFile
{
public:
	CMakeBlkFile(void);
	CMakeBlkFile(LPCTSTR strFileName);
	~CMakeBlkFile();
	bool Save();
	void SetFileName(LPCTSTR strFileName);
	//���ÿ������
	void SetDBInfo(CDataBaseInfo dbInfo);

private:
	bool GetBasePt();
	bool SelectEnt();//ѡ��ʵ��
	bool SaveToFile();

private:
	AcGePoint3d m_insertPt;
	CString m_strFileName;//�ļ���
	AcDbObjectIdArray m_objIdArrs;//id��
	CDataBaseInfo m_baseInfo;
	CBlkRefCsv m_blkFile;
};

