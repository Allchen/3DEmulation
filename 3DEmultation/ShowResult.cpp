// ShowResult.cpp : 实现文件
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


// CShowResult 诊断

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

CMy3DEmultationDoc* CShowResult::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DEmultationDoc)));
	return (CMy3DEmultationDoc*)m_pDocument;
}
// CShowResult 消息处理程序


int CShowResult::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_render.IniOpenGL(this->m_hWnd))
	{
		::MessageBox(NULL, _T("初始化OpenGL失败."), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}
	return 0;
}


void CShowResult::OnDraw(CDC* /*pDC*/)
{
	// TODO: 在此添加专用代码和/或调用基类
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
	// TODO: 在此处添加消息处理程序代码
}


BOOL CShowResult::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CFormView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CShowResult::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_render.OnLButtonDown(point);
	CFormView::OnLButtonDown(nFlags, point);
}


void CShowResult::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_render.OnLButtonUp();
	CFormView::OnLButtonUp(nFlags, point);
}


BOOL CShowResult::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_render.OnMouseWheel(zDelta, pt);
	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CShowResult::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CFormView::PreCreateWindow(cs);
}


void CShowResult::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_render.OnMouseMove(point);
	CFormView::OnMouseMove(nFlags, point);
}


void CShowResult::OnDestroy()
{
	CFormView::OnDestroy();
	//m_render.OnDestroy();
	// TODO: 在此处添加消息处理程序代码
}
