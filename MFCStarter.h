
// MFCStarter.h : main header file for the MFCStarter application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCStarterApp:
// See MFCStarter.cpp for the implementation of this class
//

class CMFCStarterApp : public CWinApp
{
public:
	CMFCStarterApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCStarterApp theApp;
