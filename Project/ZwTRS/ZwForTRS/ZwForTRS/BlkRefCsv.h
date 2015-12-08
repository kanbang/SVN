#pragma once

#include "BlkInfo.h"
class CBlkRefCsv
{
public:
	CBlkRefCsv(void);
	~CBlkRefCsv();

	//��ȡ�ļ�
	bool Read();
	bool Write();

	//
	CString GetFileName() const;
	void SetFileName(LPCTSTR strFileName);
	bool IsFileExit();

	//��������
	CDataCell GetData() const;
	void SetData(CDataCell pCell);

	//
	CDataBaseInfo SetDataCell(CDataCell pCell);
	CDataCell GetDataCellByDB(CDataBaseInfo dbInfo);

	//�����������
	void SetSpecialString(CDataBaseInfo dbInfo);

private:
	CDataCell m_pCell;
	CString m_strFileName;//�ļ���
};
