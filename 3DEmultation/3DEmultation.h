
// 3DEmultation.h : 3DEmultation Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy3DEmultationApp:
// �йش����ʵ�֣������ 3DEmultation.cpp
//

class CMy3DEmultationApp : public CWinApp
{
public:
	CMy3DEmultationApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy3DEmultationApp theApp;
