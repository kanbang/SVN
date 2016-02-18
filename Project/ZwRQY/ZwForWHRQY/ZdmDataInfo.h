#pragma once

#include "Utils.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//��ʱ��������ת
class CZdmDataInfo
{
public:
	CZdmDataInfo(void);
	~CZdmDataInfo(void);

	//��������
	LPCTSTR             label() const;
	Acad::ErrorStatus   setLabel(LPCTSTR newLabel);

	CString	getCount() const;
	double getDesignDmx() const;
	double getRealDmx() const;
	LPCTSTR getJiedian() const;
	double getGuanDi() const;
	double getWaShen() const;
	double getPoDu() const;
	double getJuli() const;
	double getcurData() const;
	//////////////////////////////////////////////////////////////////////////
	bool   getHasBulge() const;
	double getDesingDmxS() const;
	double getRealDmxS() const;
	double getJiedianS() const;
	//double getcurDataS() const;

	Acad::ErrorStatus setCount(LPCTSTR nCount);
	Acad::ErrorStatus setDesignDmx(double strText);
	Acad::ErrorStatus setRealDmx(double strText);
	Acad::ErrorStatus setJiedian(LPCTSTR strText);
	Acad::ErrorStatus setGuanDi(double strText);
	Acad::ErrorStatus setWaShen(double strText);
	Acad::ErrorStatus setPoDu(double strPoDu);
	Acad::ErrorStatus setJuli(double strJuli);
	Acad::ErrorStatus setcurData(double dcurData);
	//////////////////////////////////////////////////////////////////////////
	Acad::ErrorStatus setHasBulge(bool bHasBulge);
	Acad::ErrorStatus setDesingDmxS(double strText);
	Acad::ErrorStatus setRealDmxS(double strText);
	Acad::ErrorStatus setJiedianS(double strText);
private:
	CString             m_label;
	CString		m_strCount;//����
	//////////////////////////////////////////////////////////////////////////
	double m_dDesignDmx;//��Ƶ�����
	double m_dRealDmx;//ʵ�ʵ�����
	CString m_strJiedian;//�ڵ�
	double m_dcurData;//��ǰ׮������
	double m_dGuanDi;//�ܵ�
	double m_dWaShen;//����
	double m_dPoDu;//�¶�
	double m_dJuli;//����
	//////////////////////////////////////////////////////////////////////////
	//��ͬһ��͹��
	bool   m_bHasBulge;//�Ƿ���͹��
	double m_dDesignDmxS;//�ڶ�����Ƶ�����
	double m_dRealDmxS;//�ڶ���ʵ�ʵ�����
	double m_dJiedianS;
};
