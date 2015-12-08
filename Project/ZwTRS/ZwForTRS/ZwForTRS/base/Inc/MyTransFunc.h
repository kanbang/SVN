#pragma once
#include <vector>
using namespace std;
class MyTransFunc
{
public:
	MyTransFunc(void);
	~MyTransFunc(void);

	static AcGePoint3d My2d23d(AcGePoint2d);
	static AcGePoint2d My3d22d(AcGePoint3d);
	static AcGePoint3dArray My2d23d(AcGePoint2dArray);
	static AcGePoint2dArray My3d22d(AcGePoint3dArray);
	static AcGePoint3d MyMidPoint(AcGePoint3d, AcGePoint3d);
	static double MyTransFunc::GetBulgeOf3Pt(AcGePoint3d &startPt //���
											,AcGePoint3d &interPt //�м�һ��
											,AcGePoint3d &endPt   //�յ�
											);
	//������תΪ�Ƕ�
	static double CurveToRotation(double dCurve);
	//���Ƕ�תΪ����
	static double RotationToCurve(double dRotation);
	//ͨ��������������ݵõ��ĵ�ĵ���
	static AcGePoint3dArray OperateTwoPointsAndGetPoints(AcGePoint3d minPt, AcGePoint3d maxPt);

	static AcDbSortentsTable* get_sortents_table_of(AcDbEntity* pEnt);

	static void DuiXiangPaiXu(AcDbObjectId ent_id, bool TopOrDow = true);//��������
	//kmp�ַ���ƥ��
	//��һ������Ϊԭʼ���ݣ��ڶ�������Ϊ����ƥ����ַ���
	//����-1��ʾû���ҵ�������ֵΪ�ҵ�ƥ����
	//static int KMP(CString s,CString t);
	static void get_next(CString t, int next[ ]);
	static int KMP(CString text, CString find); 


};
