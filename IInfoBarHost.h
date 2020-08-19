#pragma once

#include <atlbase.h>
#include <ShObjIdl_core.h>

#include "IInfoBarMessage.h"

//Undocumented Interface.

const IID IID_IInfoBarHost = { 0xe38fe0f3,0x3db0,0x47ee,0xa3,0x14,0x25,0xcf,0x7f,0x4b,0xf5,0x21 };

#if defined(__cplusplus) && !defined(CINTERFACE)

MIDL_INTERFACE("e38fe0f3-3db0-47ee-a314-25cf7f4bf521")
IInfoBarHost : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE Inform(IInfoBarMessage* msg) = 0;

	virtual HRESULT STDMETHODCALLTYPE CancelInform(GUID guid) = 0;
};

#endif