#include "stdafx.h"
#include "CInfoBarMessageImpl.h"

HRESULT STDMETHODCALLTYPE CInfoBarMessageImpl::GetMessageID(GUID* guid, INT* intVal) {
	//Our InformationBar GUID
	*guid = this->guid;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CInfoBarMessageImpl::GetMessageW(LPWSTR* message) {
	if (!this->message) {
		return E_FAIL;
	}

	*message = (LPWSTR)CoTaskMemAlloc(sizeof(WCHAR) * (this->messageLen + 1));
	wcscpy_s(*message, this->messageLen + 1, this->message);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CInfoBarMessageImpl::CreateMenu(HMENU* pMwnu) {
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CInfoBarMessageImpl::HandleMenu(HWND hwnd, int intVal) {
	return E_NOTIMPL;
}

GUID* CInfoBarMessageImpl::GetMessageGUID() {
	return &(this->guid);
}

void CInfoBarMessageImpl::SetMessageW(LPCWSTR message) {
	if (!message) {
		return;
	}

	if (this->message) {
		free(this->message);
		this->message = NULL;
		this->messageLen = 0;
	}

	this->messageLen = (DWORD)wcslen(message);
	this->message = (LPWSTR)malloc(sizeof(WCHAR) * (this->messageLen + 1));
	if (!this->message) {
		this->messageLen = 0;
		return;
	}

	wcscpy_s(this->message, this->messageLen + 1, message);
	
}