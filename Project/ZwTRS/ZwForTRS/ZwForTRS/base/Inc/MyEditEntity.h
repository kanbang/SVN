#pragma once
#define ZRXDBG_TYPE						_T("����")
#define ZRXDBG_DAIHAO					_T("����")
#define ZRXDBG_MINGCHENG				_T("����")
#define ZRXDBG_SHULIANG					_T("����")
#define ZRXDBG_CAILIAO					_T("����")
#define ZRXDBG_DANZHONG					_T("����")
#define ZRXDBG_ZONGZHONG				_T("����")
#define ZRXDBG_BEIZHU					_T("��ע")
#define	ZRXDBG_DANWEI					_T("��λ")
#define ZRXDBG_LINGJIANLEIXING			_T("�������")
#define ZRXDBG_RECHULI					_T("�ȴ���")
#define ZRXDBG_BIAOMIANCHULI			_T("���洦��")
#define ZRXDBG_FNUMBER					_T("���ϴ���")
#define ZRXDBG_LIUCHENGTU_NUM			_T("����ͼ���")
#define XDT_XG_CSTRING			20000
#define XDT_XG_INT				20001
#define XDT_XG_DOUBLE			20002
#define XDT_XG_HANDLE			20003
#define XDT_XG_POINT			20004

class MyEditEntity
{
public:
	MyEditEntity(void);
	~MyEditEntity(void);
	//��ʵ��򿪲��޸���ͼ��
	static AcDbObjectId openEntChangeLayer(AcDbObjectId entId, AcDbObjectId LayerId = AcDbObjectId::kNull);
	//��POLYLINE�Ŀ��
	static AcDbObjectId openPlineChangeWidth(AcDbObjectId plineId, double dWidth);
	//�޸�text, mtext, blockrefrence��rotation
	static AcDbObjectId openEntChangeRotation(AcDbObjectId entId, double dRotate);
	//blockrefrence��scale
	static AcDbObjectId openBlkRefChangeScale(AcDbObjectId entId, double dScale);

	//�޸����ֵ�textstyleId
	static AcDbObjectId openEntChangeTextStyle(AcDbObjectId entId, AcDbObjectId TextStyleId = AcDbObjectId::kNull);

	//�޸�ʵ����߿�
	static AcDbObjectId openEntChangeLineWeight(AcDbObjectId entId, AcDb::LineWeight type = AcDb::kLnWt053);
	//�޸�ʵ����ɫ
	static AcDbObjectId openEntChangeColor(AcDbObjectId entId, int nColor);

	//[Ϊ�޸��߸ˣ��½��ܵ���ԭ�йܵ����Ľӿ�
	//����ʵ�����ڵ�������е�����Id
	//ʹ�øýӿڵ�ʱ�����ж��ý�ͷ�ķ���ֵ�Ƿ�Ϊ��
	static AcDbObjectIdArray openObjAndGetGroupIds(AcDbObjectId objId);
	//�������ҵ��ʺϵ���id����ʵ�弯��
	static AcDbObjectIdArray openGroupIdsAndGetEntIds(AcDbObjectIdArray IdArrs, BOOL bIslimited = TRUE);
	//]
	//����
	static AcDbSortentsTable* get_sortents_table_of(AcDbObjectId objId);

	//��ͼ�㲢�����������
	static AcDbObjectId OpenLayerIdAppendDescription(AcDbObjectId objId, CString strDescription);
	static CString GetLayerIdDescription(AcDbObjectId objId);
	//�г����еĳ�0�����˵�����ֵ�ͼ��
	static void ListLayerNameWithDescription(CStringArray& strLayerNameArr, BOOL bIsMask = FALSE);

	static void ListLayerNameWithMetal(CStringArray& strLayerNameArr);
	//������Ϣ��obj
	static AcDbObjectId OpenObjAppendStrToXRecord(AcDbObjectId objId, CString strAppName, CString strTypeData);
	static AcDbObjectId OpenObjAppendIntToXRecord(AcDbObjectId objId, CString strAppName, int nTypeData);
	static AcDbObjectId OpenObjAppendDoubleToXRecord(AcDbObjectId objId, CString strAppName, double dTypeData);
	//static AcDbObjectId OpenObjAppendHandleToXRecord(AcDbObjectId objId, CString strAppName, AcDbHandle hData);
	
	static CString GetObjStrFromXRecord(AcDbObjectId objId, CString strAppName);
	static int GetObjIntFromXRecord(AcDbObjectId objId, CString strAppName);
	static double GetObjDoubleFromXRecord(AcDbObjectId objId, CString strAppName);
	//static AcDbHandle GetObjHandleFromXRecord(AcDbObjectId objId, CString strAppName);
	
	//[Special For gzsj
	//����һ����ӡ�벻�ɴ�ӡ��ͼ�㣬������id
	static AcDbObjectId CreateNewNoPlotLayer(CString strLayer, int nColor, BOOL bIsModified = FALSE);
	
	static void FrozenLayer(CStringArray& strLayer, bool bIsModified = true);
	
	static void FrozenPassivationLayer(bool bIsFrozen = true);

	static void UnFrozenLayer();

	static AcDbObjectId CreateDimstyle(CString strDimName, double dheight = 2.5, double dDimlfac = 1.0, bool bDimTih = false, bool bDimToh = false);
	//����dimstyle���ָ߶�
	//[����xdata
	//����objid������ʵ��򿪲����cstring����չ����
	static bool OpenObjAppendStrToXdata(AcDbObjectId objId, CString strAppName, CString strData);
	static bool OpenObjAppendIntToXdata(AcDbObjectId objId, CString strAppName, int nData);
	static bool OpenObjAppendDoubleToXdata(AcDbObjectId objId, CString strAppName, double dData);
	static bool OpenObjAppendHandleToXdata(AcDbObjectId objId, CString strAppName, AcDbHandle hData);
	//��ȡӦ�ó����
	static CString GetObjStrXdata(AcDbObjectId objId, CString strAppName);
	static double GetObjDoubleXdata(AcDbObjectId objId, CString strAppName);
	static int GetObjIntXdata(AcDbObjectId objId, CString strAppName);
	static AcDbHandle GetObjHandleXdata(AcDbObjectId objId, CString hData);

	static bool SetObjStrToXdata(AcDbObjectId objId, CString strAppName, CString strXdata);
	static bool SetObjDoubleToXdata(AcDbObjectId objId, CString strAppName, double dXdata);
	static bool SetObjIntToXdata(AcDbObjectId objId, CString strAppName, int nXdata);
	//]����xdata

	//������άxoyƽ�����������ཻ���
	static	BOOL JudgePointInArea(AcGePoint2d insertPt, AcGePoint2d minPt, AcGePoint2d maxPt);
	static int JudgeAreaInOtherArea(AcDbExtents curExts, AcDbExtents preExts);
	static int JudgeAreaInOtherArea(AcGePoint2d curMinPt,AcGePoint2d curMaxPt,AcGePoint2d preMinPt,AcGePoint2d preMaxPt);

	//��ȡʵ������
	static AcDbExtents OpenObjAndGetExts(AcDbObjectId objId);
	static double OpenObjAndGetWidth(AcDbObjectId objId);
	static double OpenObjAndGetLength(AcDbObjectId objId);
	
	static CString OpenObjAndGetString(AcDbObjectId objId);

	//ɾ��ʵ��
	static bool EraseObj(AcDbObjectId);
};