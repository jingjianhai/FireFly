
// FireFly.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFireFlyApp:
// �йش����ʵ�֣������ FireFly.cpp
//

class CFireFlyApp : public CWinApp
{
public:
	CFireFlyApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFireFlyApp theApp;