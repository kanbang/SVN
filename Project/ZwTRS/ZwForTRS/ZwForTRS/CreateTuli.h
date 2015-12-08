#pragma once
#include <map>
#include <utility>
using namespace std;

//���ƿ����Ϣ
class CBlkRefInFo
{
public:
	CBlkRefInFo(void);
	~CBlkRefInFo();
	
	//��ȡ��Ϣ
	//��ȡ���������
	AcGePoint3d GetBasePt() const;
	AcDbExtents GetExts() const;
	AcDbObjectId GetBlkId() const;
	//LPCTSTR GetBlkName() const;
	double GetBlkScale() const;

	//��ȡ����
	double GetLength() const;
	double GetWidth() const;
	AcGePoint3d GetMidPt() const;

	//������Ϣ
	void SetBasePt(AcGePoint3d basePt);
	void SetExts(AcDbExtents exts);
	void SetBlkId(AcDbObjectId blkId);
	//void SetBlkName(LPCTSTR strName);
	void SetBlkScale(double dScale);

	CBlkRefInFo&   operator = (const CBlkRefInFo& scl);
private:
	AcGePoint3d m_BasePt;//������
	AcDbExtents m_Exts;//���
	AcDbObjectId m_blkId;//id
	//CString		m_strBlkName;//����
	double		m_dScale;//����
};

//��������ͼ����ܵ����ݣ��������ȣ���ȵ�
typedef map<CString, pair<CBlkRefInFo*, int> > DataMap;
class CCreateFrame
{
public:
	CCreateFrame(void);
	~CCreateFrame(void);
	//��ȡ����
	AcGePoint3d GetBasePt() const;
 	//��������
	void SetBasePt(AcGePoint3d basePt);	
	
	//��ȡ���еĿ�����
	DataMap GetData() const;
	//�������еĿ�����
	void SetData(DataMap data);

	bool DoIt();
private:
	//����
	//�������
	bool DrawFrame();
	//������������
	void DrawSpecialText(AcGePoint3d basePt, double dLen, double dWidth, CString strText, bool bIsNum = false);
	//�����ⲿ����
	void DrawSpecialBlkRef(AcGePoint3d basePt, CBlkRefInFo* blkInfo);

	//��������
	void Clear();
	//��ӵ�ѡ����
	void AppendToSS(AcDbObjectId objId);

	//�ƶ�ʵ��
	void MoveEntity();
private:
	double m_dXuhao;	//��ų���
	double m_dTuli;//ͼ������
	double m_dSBMC;//�豸����
	double m_dCount;//����
	double m_dBeizhu;//��ע
	double m_dTextHeight;//���������еĸ߶�
	double m_dHeight;//ͼ�������еĸ߶�
	double m_dTxtHeight;//���ָ߶�
	double m_dScale;
	double m_dNumTextHeight;//�������ָ߶�
	AcGePoint3d m_basePt;//���½ǵ�Ĳ����

	ads_name m_ssname;//ѡ��
	DataMap m_Data;
	AcDbObjectIdArray m_IdArrs;
};


class CCreateTuli
{
public:
	CCreateTuli(void);
	~CCreateTuli(void);

	void doIt();
	
	double GetBlkLength() const;
	double GetBlkHeight() const;
	//double GetTextLength() const;
	//double GetTextHeight() const;

	void SetBlkLength(double dBlkLength);
	void SetBlkHeight(double dBlkHeight);
	//void SetTextLength(double dTextLength);
	//void SetTextHeight(double dTextHeight);

private:
	bool AddEntity();

	void MoveEntity();
	void CloneAndMoveEntity(AcDbObjectId entId, AcGeMatrix3d m);
	bool ChangeBlkRef(AcDbObjectId objId);//�޸Ŀ���յ�λ��
	void CalcScale(AcDbObjectId objId);//�������
	void Clear();
private:
	double m_BlkLength;//�������ռ�ĳ���
	double m_BlkHeight;//�������ռ�ĸ߶�
	double m_TextLength;//������ռ����
	double m_TextHeight;//������ռ���
	double m_dScale;//����
	//std::map<CString, std::pair<AcGePoint3d ,AcDbObjectId> > m_EntitySet;
	DataMap m_EntitySet;
	ads_name m_ssname;
};
