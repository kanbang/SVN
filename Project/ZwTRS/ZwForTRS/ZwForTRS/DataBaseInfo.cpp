#include "StdAfx.h"
#include "DataBaseInfo.h"

CDataBaseInfo::CDataBaseInfo(void)
{	
	m_strShuliang = _T("1");
	m_strDanzhong = _T("");
}

CDataBaseInfo::CDataBaseInfo(const CDataBaseInfo& scl)
{
	*this = scl;
}


CDataBaseInfo::~CDataBaseInfo(void)
{
}

//����
CString CDataBaseInfo::GetFItemId() const
{
	return m_strDaihao;
}
//����
CString CDataBaseInfo::GetFName() const
{
	return m_strMingcheng;
}
//����
CString CDataBaseInfo::GetShuliang() const
{
	return m_strShuliang;
}
//����
CString CDataBaseInfo::GetCailiao() const
{
	return m_strCailiao;
}
//����
CString CDataBaseInfo::GetDanzhong() const
{
	return m_strDanzhong;
}
//����
CString CDataBaseInfo::GetZongzhong() const
{
	return m_strZongzhong;
}
//��ע��ִ�б�׼
CString CDataBaseInfo::GetBeizhu() const
{
	return m_strBeiZhu;
}
//��λ
CString CDataBaseInfo::GetDanwei() const
{
	return m_strDanwei;
}
//�������
CString CDataBaseInfo::GetFErpCls() const
{
	return m_strLingjianLeixing;
}
//�ȴ���
CString CDataBaseInfo::GetReChuli() const
{
	return m_strReChuli;
}
//���洦��
CString CDataBaseInfo::GetBiaoMianChuli() const
{
	return m_strBiaoMianChuli;
}
//���ϴ���
CString CDataBaseInfo::GetFNumber() const
{
	return m_strFNumber;
}

//CString CDataBaseInfo::GetChartNum() const
//{
//	return m_strChartNum;
//}
//������Ϣ

//����
void CDataBaseInfo::SetFItemId(LPCTSTR str)
{
	m_strDaihao = str;
}
//����
void CDataBaseInfo::SetFName(LPCTSTR str)
{
	m_strMingcheng = str;
}
//����
void CDataBaseInfo::SetShuliang(LPCTSTR str)
{
	m_strShuliang = str;
}
//����
void CDataBaseInfo::SetCailiao(LPCTSTR str)
{
	m_strCailiao = str;
}
//����
void CDataBaseInfo::SetDanzhong(LPCTSTR str)
{
	m_strDanzhong = str;
}
//����
void CDataBaseInfo::SetZongzhong(LPCTSTR str)
{
	m_strZongzhong = str;
}
//��ע��ִ�б�׼
void CDataBaseInfo::SetBeizhu(LPCTSTR str)
{
	m_strBeiZhu = str;
}
//��λ
void CDataBaseInfo::SetDanwei(LPCTSTR str)
{
	m_strDanwei = str;
}
//�������
void CDataBaseInfo::SetFErpCls(LPCTSTR str)
{
	m_strLingjianLeixing = str;
}

//�ȴ���
void CDataBaseInfo::SetReChuli(LPCTSTR str)
{
	m_strReChuli = str;
}
//���洦��
void CDataBaseInfo::SetBiaoMianChuli(LPCTSTR str)
{
	m_strBiaoMianChuli = str;
}
//���ϴ���
void CDataBaseInfo::SetFNumber(LPCTSTR str)
{
	m_strFNumber = str;
}

//void CDataBaseInfo::SetChartNum(LPCTSTR str)
//{
//	m_strChartNum = str;
//}

CDataBaseInfo&   CDataBaseInfo::operator = (const CDataBaseInfo& scl)
{
	m_strDaihao = scl.GetFItemId();//����
	m_strMingcheng = scl.GetFName();//����
	m_strShuliang = scl.GetShuliang();//����
	m_strCailiao = scl.GetCailiao();//����
	m_strDanzhong = scl.GetDanzhong();//����
	m_strZongzhong = scl.GetZongzhong();//����
	m_strBeiZhu = scl.GetBeizhu();//��ע
	m_strDanwei = scl.GetDanwei();//��λ
	m_strLingjianLeixing = scl.GetFErpCls();//�������
	m_strReChuli = scl.GetReChuli();//�ȴ���
	m_strBiaoMianChuli = scl.GetBiaoMianChuli();//���洦��
	m_strFNumber = scl.GetFNumber();//���ϴ���
	//m_strChartNum = scl.GetChartNum();//����ͼ���
	return *this;
}
