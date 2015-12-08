#pragma once

//#ifdef _DLL_SAMPLE
//#define DLL_SAMPLE_API __declspec(dllexport)
//#else
//#define DLL_SAMPLE_API __declspec(dllimport)
//#endif

class  /*DLL_SAMPLE_API*/ CDataBaseInfo//�����Ļ�����Ϣ
{
public:
	CDataBaseInfo(void);
	CDataBaseInfo(const CDataBaseInfo& scl);
	~CDataBaseInfo(void);
	//��ȡ��Ϣ
	CString GetFItemId() const;
	CString GetFName() const;
	CString GetShuliang() const;
	CString GetCailiao() const;
	CString GetDanzhong() const;
	CString GetZongzhong() const;
	CString GetBeizhu() const;
	CString GetDanwei() const;
	CString GetFErpCls() const;
	CString GetReChuli() const;
	CString GetBiaoMianChuli() const;
	CString GetFNumber() const;//���ϴ���
	//CString GetChartNum() const;//����ͼ���
	//������Ϣ
	void SetFItemId(LPCTSTR str);
	void SetFName(LPCTSTR str);
	void SetShuliang(LPCTSTR str);
	void SetCailiao(LPCTSTR str);
	void SetDanzhong(LPCTSTR str);
	void SetZongzhong(LPCTSTR str);
	void SetBeizhu(LPCTSTR str);
	void SetDanwei(LPCTSTR str);
	void SetFErpCls(LPCTSTR str);
	void SetReChuli(LPCTSTR str);
	void SetBiaoMianChuli(LPCTSTR str);
	void SetFNumber(LPCTSTR str);
	//void SetChartNum(LPCTSTR str);

	CDataBaseInfo&   operator = (const CDataBaseInfo& scl);

private:
	CString m_strDaihao;//����
	CString m_strMingcheng;//����
	CString m_strShuliang;//����
	CString m_strCailiao;//����
	CString m_strDanzhong;//����
	CString m_strZongzhong;//����
	CString m_strBeiZhu;//��ע
	CString m_strDanwei;//��λ
	CString m_strLingjianLeixing;//�������
	CString m_strReChuli;//�ȴ���
	CString m_strBiaoMianChuli;//���洦��
	CString m_strFNumber;//���ϴ���
	//CString m_strChartNum;//����ͼ���
};