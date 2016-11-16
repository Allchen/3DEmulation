
// 3DEmultationView.cpp : CMy3DEmultationView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "3DEmultation.h"
#endif

#include "3DEmultationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DEmultationView

IMPLEMENT_DYNCREATE(CMy3DEmultationView, CFormView)

BEGIN_MESSAGE_MAP(CMy3DEmultationView, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMy3DEmultationView 构造/析构

CMy3DEmultationView::CMy3DEmultationView()
	: CFormView(IDD_MY3DEMULTATION_FORM)
{
	// TODO: 在此处添加构造代码

}

CMy3DEmultationView::~CMy3DEmultationView()
{
}

void CMy3DEmultationView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMy3DEmultationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CFormView::PreCreateWindow(cs);
}

void CMy3DEmultationView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMy3DEmultationView 诊断

#ifdef _DEBUG
void CMy3DEmultationView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy3DEmultationView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy3DEmultationDoc* CMy3DEmultationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DEmultationDoc)));
	return (CMy3DEmultationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DEmultationView 消息处理程序


int CMy3DEmultationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if(!m_render.IniOpenGL(this->m_hWnd))
	{
		::MessageBox(NULL, _T("初始化OpenGL失败."), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}
	return 0;
}


void CMy3DEmultationView::OnDraw(CDC* /*pDC*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CMy3DEmultationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_render.RenderScene();
}


void CMy3DEmultationView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	if (cx <= 0 || cy <= 0)
	{
		return;
	}
	m_render.PreRender(cx, cy);
	// TODO: 在此处添加消息处理程序代码
}


void CMy3DEmultationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_render.OnMouseMove(point);
	CFormView::OnMouseMove(nFlags, point);
}


void CMy3DEmultationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_render.OnLButtonDown(point);
	CFormView::OnLButtonDown(nFlags, point);
}


void CMy3DEmultationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_render.OnLButtonUp();
	CFormView::OnLButtonUp(nFlags, point);
}


BOOL CMy3DEmultationView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CFormView::OnEraseBkgnd(pDC);
	return TRUE;
}


BOOL CMy3DEmultationView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_render.OnMouseWheel(zDelta, pt);
	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}


void CMy3DEmultationView::OnDestroy()
{
	CFormView::OnDestroy();
	m_render.OnDestroy();
	
	// TODO: 在此处添加消息处理程序代码
}

bool CMy3DEmultationView::RayHitModel(my::Ray scanRay, my::SPACEPOINT &scanPoint, int modelID)
{
	if (m_render.m_modelMap[modelID].RayHitSphere(scanRay))
	{
		my::Vector3 vModel;
		my::Vector3 Lux1;
		float dist = INT_MAX;
		if (m_render.m_modelMap[modelID].RayRealHitModel(scanRay, vModel, dist, Lux1, m_render.m_LPos))
		{
			scanPoint.x = vModel.x;
			scanPoint.y = vModel.y;
			scanPoint.z = vModel.z;
			scanPoint.fDistance = dist;
			scanPoint.Lux = Lux1;
			return true;
		}
	}
	return false;
}

bool CMy3DEmultationView::RayHitModels(my::Ray scanRay, my::SPACEPOINT &scanPoint, int &modelID)
{
	bool hitModel = false;
	my::SPACEPOINT scanPointTmp;
	scanPointTmp.fDistance = INT_MAX;
	for (auto iter = m_render.m_modelMap.begin(); iter != m_render.m_modelMap.end(); ++iter)
	{
		/*Move2Center(iter->first);
		iter->second.m_3DModel.m_vCenter.x = 0;
		iter->second.m_3DModel.m_vCenter.y = 0;
		iter->second.m_3DModel.m_vCenter.z = 0;*/
		if (RayHitModel(scanRay, scanPoint, iter->first))
		{
			if (scanPoint.fDistance < scanPointTmp.fDistance)
			{
				scanPointTmp = scanPoint;
				modelID = iter->first;
			}
			hitModel = true;
		}
	}
	if (!hitModel)
	{
		return false;
	}
	else
	{
		scanPoint = scanPointTmp;
		return true;
	}
}