#pragma once

class MyCalculateFunc
{
public:
	MyCalculateFunc(void);
	~MyCalculateFunc(void);
	//�ж�һ������Բ��
	static BOOL JudgePointInCircle(AcGePoint3d basePt, AcGePoint3d centerPt, double dRadius);

};
