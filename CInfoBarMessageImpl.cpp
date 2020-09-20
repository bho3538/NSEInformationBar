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

HRESULT STDMETHODCALLTYPE CInfoBarMessageImpl::CreateMenu(HMENU* pMenu) {
	HRESULT hr = S_OK;

	MENUITEMINFOW menuItem = {sizeof(MENUITEMINFOW),0,};
	HMENU hMenu = CreatePopupMenu();

	//4'rd parameter is menuId (uIDNewItem)
	InsertMenuW(hMenu, 0, MF_BYPOSITION | MF_STRING, 1, L"Menu 1"); 
	InsertMenuW(hMenu, 1, MF_BYPOSITION | MF_STRING, 2, L"Menu 2");
	menuItem.fType = MFT_SEPARATOR;
	menuItem.fMask = MIIM_TYPE;
	InsertMenuItemW(hMenu, 2, TRUE, &menuItem);
	InsertMenuW(hMenu, 3, MF_BYPOSITION | MF_STRING, 3, L"Menu 3");

	*pMenu = hMenu;
escapeArea:
	return hr;
}

HRESULT STDMETHODCALLTYPE CInfoBarMessageImpl::HandleMenu(HWND hwnd, INT menuId) {
	switch (menuId) {
		case 1: {
			MessageBoxW(hwnd, L"Menu1", L" NSE Information Bar", 0);
		}; break;
		case 2: {
			MessageBoxW(hwnd, L"Menu2", L" NSE Information Bar", 0);
		}; break;
		case 3: {
			MessageBoxW(hwnd, L"Menu3", L" NSE Information Bar", 0);
		}; break;
	}

	return S_OK;
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