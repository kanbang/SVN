// CZwcadmCom.h : CCZwcadmCom ������

#pragma once
#include "resource.h"       // ������



#include "zwcadm_com_i.h"
#import "ZwmPEBridgePlugins.dll" no_namespace raw_interfaces_only, raw_native_types, no_namespace, named_guids


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CCZwcadmCom

class ATL_NO_VTABLE CCZwcadmCom :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCZwcadmCom, &CLSID_CZwcadmCom>,
	public IDispatchImpl<ICZwcadmCom, &IID_ICZwcadmCom, &LIBID_zwcadm_comLib, /*wMajor =*/ 1, /*wMinor =*/ 0>, 
	public IProjectFrameworkAddin
{
public:
	CCZwcadmCom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CZWCADMCOM)


BEGIN_COM_MAP(CCZwcadmCom)
	COM_INTERFACE_ENTRY(ICZwcadmCom)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IProjectFrameworkAddin)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	// IProjectFrameworkAddin
	STDMETHOD(CallTitleMenuFunction)(BSTR bstrCommandName, IPETitleCollection** ppPETitleCollection, BSTR bstrFileName, BSTR* bstrErrorMsg, long *lSucceeded);
	STDMETHOD(CallBomMenuFunction)(BSTR bstrCommandName, BSTR FileName, IPETitleCollection** ppPETitleCollection, IPEBomCollections** ppPEBomCollections, BSTR* ErrorMsg, long *lSucceeded);


};

OBJECT_ENTRY_AUTO(__uuidof(CZwcadmCom), CCZwcadmCom)
