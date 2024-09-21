
// CS204_THE6.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCS204_THE6App:
// See CS204_THE6.cpp for the implementation of this class
//

class CCS204_THE6App : public CWinApp
{
public:
	CCS204_THE6App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCS204_THE6App theApp;