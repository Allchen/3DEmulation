
// 3DEmultationView.h : CMy3DEmultationView ��Ľӿ�
//

#pragma once
#include"3DEmultationDoc.h"
#include"C3D_Render.h"
class CMy3DEmultationView : public CFormView
{
protected: // �������л�����
	CMy3DEmultationView();
	DECLARE_DYNCREATE(CMy3DEmultationView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MY3DEMULTATION_FORM };
#endif

// ����
public:
	CMy3DEmultationDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CMy3DEmultationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
//����ʱ���õĺ���
	bool RayHitModels(my::Ray scanRay, my::SPACEPOINT &scanPoint, int &modelID);
	bool RayHitModel(my::Ray scanRay, my::SPACEPOINT &scanPoint, int modelID);
};

#ifndef _DEBUG  // 3DEmultationView.cpp �еĵ��԰汾
inline CMy3DEmultationDoc* CMy3DEmultationView::GetDocument() const
   { return reinterpret_cast<CMy3DEmultationDoc*>(m_pDocument); }
#endif

