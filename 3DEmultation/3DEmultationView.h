
// 3DEmultationView.h : CMy3DEmultationView 类的接口
//

#pragma once
#include"3DEmultationDoc.h"
#include"C3D_Render.h"
class CMy3DEmultationView : public CFormView
{
protected: // 仅从序列化创建
	CMy3DEmultationView();
	DECLARE_DYNCREATE(CMy3DEmultationView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MY3DEMULTATION_FORM };
#endif

// 特性
public:
	CMy3DEmultationDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMy3DEmultationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

public:
	C3D_Render m_render;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDestroy();
//仿真时所用的函数
	bool RayHitModels(my::Ray scanRay, my::SPACEPOINT &scanPoint, int &modelID);
	bool RayHitModel(my::Ray scanRay, my::SPACEPOINT &scanPoint, int modelID);
};

#ifndef _DEBUG  // 3DEmultationView.cpp 中的调试版本
inline CMy3DEmultationDoc* CMy3DEmultationView::GetDocument() const
   { return reinterpret_cast<CMy3DEmultationDoc*>(m_pDocument); }
#endif

