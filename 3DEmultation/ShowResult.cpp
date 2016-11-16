// ShowResult.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DEmultation.h"
#include "ShowResult.h"


// CShowResult

IMPLEMENT_DYNCREATE(CShowResult, CFormView)

CShowResult::CShowResult()
	: CFormView(IDD_SHOWRESULT)
{

}

CShowResult::~CShowResult()
{
}

void CShowResult::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShowResult, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CShowResult ���

#ifdef _DEBUG
void CShowResult::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowResult::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

CMy3DEmultationDoc* CShowResult::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DEmultationDoc)));
	return (CMy3DEmultationDoc*)m_pDocument;
}
// CShowResult ��Ϣ�������


int CShowResult::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_render.IniOpenGL(this->m_hWnd))
	{
		::MessageBox(NULL, _T("��ʼ��OpenGLʧ��."), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}
	return 0;
}


void CShowResult::OnDraw(CDC* /*pDC*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	CMy3DEmultationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_render.RenderScene();
}


void CShowResult::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	if (cx <= 0 || cy <= 0)
	{
		return;
	}
	m_render.PreRender(cx, cy);
	// TODO: �ڴ˴������Ϣ����������
}


BOOL CShowResult::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CFormView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CShowResult::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_render.OnLButtonDown(point);
	CFormView::OnLButtonDown(nFlags, point);
}


void CShowResult::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_render.OnLButtonUp();
	CFormView::OnLButtonUp(nFlags, point);
}


BOOL CShowResult::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_render.OnMouseWheel(zDelta, pt);
	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CShowResult::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CFormView::PreCreateWindow(cs);
}


void CShowResult::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_render.OnMouseMove(point);
	CFormView::OnMouseMove(nFlags, point);
}


void CShowResult::OnDestroy()
{
	CFormView::OnDestroy();
	//m_render.OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
}
