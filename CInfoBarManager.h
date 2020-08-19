#pragma once

#include "IInfoBarHost.h"
#include "IInfoBarMessage.h"

#include "CInfoBarMessageImpl.h"

const IID IID_IBrowserProgressConnecion = { 0x20174539,0xb2c7,0x4ec7,{0x97,0x0b,0x04,0x20,0x1f,0x9c,0xdb,0xad} };

class CInfoBarManager
{
public:
	CInfoBarManager();
	~CInfoBarManager();

	void InitializeSimple(LPCWSTR message);
	void Initialize(CComObject<CInfoBarMessageImpl>* message);

	void ShowInfoBar();
	void Close();

private:
	CComObject<CInfoBarMessageImpl>* infoMsg = NULL;

	IGlobalInterfaceTable* git = NULL;
	IInfoBarHost* host = NULL;
	IUnknown* browserProgress = NULL;
};

