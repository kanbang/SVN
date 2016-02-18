#ifndef CBASEDATAFORZDDWG_H
#define CBASEDATAFORZDDWG_H
#include "MyBase.h"

class CBaseDataForZdDwg : public AcDbObject 
{

public:
                CBaseDataForZdDwg();
    virtual     ~CBaseDataForZdDwg();

    ACRX_DECLARE_MEMBERS(CBaseDataForZdDwg);

        // access to data members

    LPCTSTR             label() const;
    Acad::ErrorStatus   setLabel(LPCTSTR newLabel);

	CString					NumCount();
	Acad::ErrorStatus	setNumCount(CString nCount);

	CString					CurNum();
	Acad::ErrorStatus	setCurNum(CString nCount);

	double				XScale() const;
	Acad::ErrorStatus	setXScale(double dHx);

	double				YScale() const;
	Acad::ErrorStatus	setYScale(double dHx);

	double				minElavation() const;
	Acad::ErrorStatus	setMinElavation(double dElavation);

	double				maxElavation() const;
	Acad::ErrorStatus	setMaxElavation(double dElavation);

	bool				createBc() const;
	Acad::ErrorStatus	setcreateBc(bool bDrawBc);

	bool				createJiedian() const;
	Acad::ErrorStatus	setcreateJieidan(bool bDrawBc);

	AcGePoint3d			basePt() const;
	Acad::ErrorStatus	setbasePt(AcGePoint3d startPt);


	/*AcGePoint3d			endPt() const;
	Acad::ErrorStatus	setEndPt(AcGePoint3d endPt);*/

	/*double				hengxiang() const;
	Acad::ErrorStatus	setHengxiang(double dHx);

	double				zongxiang() const;
	Acad::ErrorStatus	setZongxiang(double dZx);*/
        // overridden from AcDbObject
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* filer) const;

private:
    // data members
    CString             m_label;
	CString				m_strNumCount;//ͼֽ�����ֵ�����
	CString				m_strCurNum;//��ǰͼֽ������

	double				m_dXScale;//x����
	double				m_dYScale;//y����

	double				m_dminElavation;//��ʼ���
	double				m_dmaxElavation;//��ֹ���

	bool				m_bDrawBc;//���Ʊ��
	bool				m_bDrawJiedian;//���ƽڵ�
	AcGePoint3d			m_basePt;//����

    static Adesk::Int16 m_version;
	static LPCTSTR		m_dictName;

	//AcGePoint3d			m_endPt;
	//double				m_dHengxiang;
	//double				m_dZongxiang;


        // Dxf Codes
    enum 
	{
        kDxfLabel       	= 1,
		kDxfNumCount		= 300,//90~99 32λ����ֵ
		kDxfCurNum			= 301,
		kDxfXScale			= 40,//4~59
		kDxfYScale			= 41,
		kDxfminElavation 	= 42,
		kDxfmaxElavation 	= 43,
		kDxfDrawBc			= 290,//290-299 ������־ֵ
		kDxfDrawJiedian		= 291,
		
		kDxfBasePt			= 10,//����
		/*kDxfHengxiang		= 140,
		kDxfZongxiang		= 141,
		kDxfStartPt			= 10,
		kDxfEndPt			= 11,*/
    };

public:
	static LPCTSTR		dictName()	{ return m_dictName; }
	static AcDbObjectId	getStandardStyle(AcDbDatabase* db, bool makeIfNotThere);

};


#endif    // ARXDBGDBADESKLOGOSTYLE_H