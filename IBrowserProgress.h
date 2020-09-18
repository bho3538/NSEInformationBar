#pragma once

#include <atlbase.h>
//Undocumented Interface.

//5EA8EEC4-C34B-4DE0-9B56-0E15FD8C8F80
const IID IID_IBrowserProgressAggregator = { 0x5ea8eec4,0xc34b,0x4de0,{0x9b,0x56,0x0e,0x15,0xfd,0x8c,0x8f,0x80} };
//18140CBD-AA23-4384-A38D-6A8D3E2BE505
const IID IID_IBrowserProgressSessionProvider = { 0x18140cbd,0xaa23,0x4384,{0xa3,0x8d,0x6a,0x8d,0x3e,0x2b,0xe5,0x05} };

#if defined(__cplusplus) && !defined(CINTERFACE)

MIDL_INTERFACE("18140CBD-AA23-4384-A38D-6A8D3E2BE505")
IBrowserProgressSessionProvider : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE BeginSession() = 0; //Unknown
	virtual HRESULT STDMETHODCALLTYPE EndSession() = 0;//Unknown
	virtual HRESULT STDMETHODCALLTYPE GetCurrentSession(PDWORD sessionId) = 0;
	virtual HRESULT STDMETHODCALLTYPE ActivateSession() = 0;//Unknown
};

#endif