#pragma once
#include"3DEmultationDoc.h"
#include"C3D_Render.h"

// CShowResult 窗体视图

class CShowResult : public CFormView
{
	DECLARE_DYNCREATE(CShowResult)

protected:
	CShowResult();           // 动态创建所使用的受保护的构造函数
	virtual ~CShowResult();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOWRESULT };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	C3D_Render m_render;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnDraw(CDC* /*pDC*/);
public:
	CMy3DEmultationDoc* GetDocument() const;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};


