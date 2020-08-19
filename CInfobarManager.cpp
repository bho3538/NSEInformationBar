#include "stdafx.h"
#include "CInfoBarManager.h"


CInfoBarManager::CInfoBarManager()
{
}


CInfoBarManager::~CInfoBarManager()
{
	if (this->infoMsg) {
		this->infoMsg->Release();
	}
	if (this->browserProgress) {
		this->browserProgress->Release();
	}

	if (this->host) {
		this->host->Release();
	}

	if (this->git) {
		this->git->Release();
	}
}

void CInfoBarManager::InitializeSimple(LPCWSTR message) {
	HRESULT hr = S_OK;
	if (message) {
		hr = CComObject<CInfoBarMessageImpl>::CreateInstance(&this->infoMsg);
		if (hr == S_OK) {
			this->infoMsg->SetMessageW(message);
		}
	}
}
void CInfoBarManager::Initialize(CComObject<CInfoBarMessageImpl>* message) {
	if (message) {
		this->infoMsg = message;
		this->infoMsg->AddRef();
	}
}

void CInfoBarManager::ShowInfoBar() {
	HRESULT hr;

	//Get GIT
	hr = CoCreateInstance(CLSID_StdGlobalInterfaceTable,NULL,CLSCTX_INPROC_SERVER,
		IID_IGlobalInterfaceTable,(PVOID*)&this->git);

	if (SUCCEEDED(hr)) {
		//i dont't know how to get dwCookie From Explorer Internal.
		//networkexplorer.dll (My Network Places) know dwCookie from Explorer Internal.
		//In this case, brute-force dwCookie value.
		for (DWORD i = 0; i < MAXDWORD; i++) {
			hr = this->git->GetInterfaceFromGlobal(i, IID_IBrowserProgressConnecion, (PVOID*)&this->browserProgress);
			if (hr == S_OK) {
				hr = this->browserProgress->QueryInterface(IID_IInfoBarHost, (PVOID*)&this->host);

				if (hr == S_OK) {
					//Call Relase in explorer inside
					this->infoMsg->AddRef();
					this->host->Inform(this->infoMsg);
				}
				break;
			}
		}
	}
}

void CInfoBarManager::Close() {
	if (this->host && this->infoMsg) {
		GUID messageId = *(this->infoMsg->GetMessageGUID());
		this->host->CancelInform(messageId);
	}
}