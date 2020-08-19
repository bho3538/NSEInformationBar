#pragma once

#include "IInfoBarMessage.h"


class ATL_NO_VTABLE CInfoBarMessageImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IInfoBarMessage
{
public:

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInfoBarMessageImpl)
		COM_INTERFACE_ENTRY(IInfoBarMessage)
	END_COM_MAP()

	CInfoBarMessageImpl() {
		//Create Random GUID
		CoCreateGuid(&guid);
	}

	~CInfoBarMessageImpl() {
		if (this->message) {
			free(this->message);
		}
	}

	HRESULT STDMETHODCALLTYPE CInfoBarMessageImpl::GetMessageID(GUID* guid, INT* intVal);
	HRESULT STDMETHODCALLTYPE CInfoBarMessageImpl::GetMessageW(LPWSTR* message);
	HRESULT STDMETHODCALLTYPE CInfoBarMessageImpl::CreateMenu(HMENU* pMwnu);
	HRESULT STDMETHODCALLTYPE CInfoBarMessageImpl::HandleMenu(HWND hwnd, int intVal);
	
	GUID* GetMessageGUID();

	void SetMessageW(LPCWSTR message);
private:
	GUID guid;

	LPWSTR message = NULL;
	DWORD messageLen = 0;
};

