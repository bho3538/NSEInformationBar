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

	if (this->sessionProvider) {
		this->sessionProvider->Release();
	}

	if (this->sprovider) {
		this->sprovider->Release();
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

void CInfoBarManager::ShowInfoBar(IShellView* shview) {
	HRESULT hr;
	DWORD dwCookie = 0;

	if (!this->sprovider) {
		hr = shview->QueryInterface(IID_IServiceProvider, (PVOID*)&sprovider);
		if (FAILED(hr)) {
			goto escapeArea;
		}
	}

	if (!this->sessionProvider) {
		hr = this->sprovider->QueryService(IID_IBrowserProgressAggregator, IID_IBrowserProgressSessionProvider, (PVOID*)&this->sessionProvider);
		if (FAILED(hr)) {
			goto escapeArea;
		}
	}

	hr = sessionProvider->GetCurrentSession(&dwCookie);
	if (FAILED(hr)) {
		goto escapeArea;
	}

	//Get GIT
	if (!this->git) {
		hr = CoCreateInstance(CLSID_StdGlobalInterfaceTable, NULL, CLSCTX_INPROC_SERVER,
			IID_IGlobalInterfaceTable, (PVOID*)&this->git);
		if (FAILED(hr)) {
			goto escapeArea;
		}
	}

	hr = this->git->GetInterfaceFromGlobal(dwCookie, IID_IBrowserProgressConnecion, (PVOID*)&this->browserProgress);
	if (hr == S_OK) {
		hr = this->browserProgress->QueryInterface(IID_IInfoBarHost, (PVOID*)&this->host);
		if (hr == S_OK) {
			//Call Relase in explorer inside
			this->infoMsg->AddRef();
			this->host->Inform(this->infoMsg);
		}
	}

escapeArea:

	return;
}

void CInfoBarManager::Close() {
	if (this->host && this->infoMsg) {
		GUID messageId = *(this->infoMsg->GetMessageGUID());
		this->host->CancelInform(messageId);
	}
}