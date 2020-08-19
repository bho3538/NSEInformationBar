#pragma once

#include <atlbase.h>
#include <ShObjIdl_core.h>

//Undocumented Interface.

const IID IID_InfoBarMessage = { 0x819d1334,0x9d74,0x4254,0x9a,0xc8,0xdc,0x74,0x5e,0xbc,0x53,0x86 };

#if defined(__cplusplus) && !defined(CINTERFACE)

MIDL_INTERFACE("819d1334-9d74-4254-9ac8-dc745ebc5386")
IInfoBarMessage : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetMessageID(GUID* guid,INT* intVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMessageW(LPWSTR* message) = 0;

	virtual HRESULT STDMETHODCALLTYPE CreateMenu(HMENU* pMwnu) = 0;

	virtual HRESULT STDMETHODCALLTYPE HandleMenu(HWND hwnd,int intVal) = 0;

};

#endif