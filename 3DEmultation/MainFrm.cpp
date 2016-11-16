
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "3DEmultation.h"

#include "MainFrm.h"
#include"3DEmultationDoc.h"
#include"3DEmultationView.h"
#include"ShowResult.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_MENU_MODEL, &CMainFrame::OnModel)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
	:m_init(false)
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style = WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
	cs.lpszName = _T("3DEmultation");
	HWND hwnd = ::GetDesktopWindow();
	RECT rect;
	::GetClientRect(hwnd, &rect);
	cs.cy = rect.bottom / 2;
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	GetClientRect(&rect);
	m_splitterWnd.CreateStatic(this, 1, 2);
	if (!m_splitterWnd.CreateView(0, 0,
		RUNTIME_CLASS(CMy3DEmultationView),
		CSize(rect.Width() / 2, rect.Height()),
		pContext)) {
		m_init = false;
		return false;
}
	if (!m_splitterWnd.CreateView(0, 1,
		RUNTIME_CLASS(CShowResult),
		CSize(rect.Width() - rect.Width() / 2, rect.Height()),
		pContext)) {
		m_init = false;
		return false;
	}
	m_init = true;
	return true;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rc;
	GetClientRect(&rc);
	if (m_init&&nType != SIZE_MINIMIZED) {
		m_splitterWnd.SetRowInfo(0, cy, 0);

		m_splitterWnd.SetColumnInfo(0, rc.Width() / 2, 0);
		m_splitterWnd.SetColumnInfo(1, rc.Width() / 2, 0);
		m_splitterWnd.RecalcLayout();
	}
}


void CMainFrame::OnModel()
{
	// TODO: 在此添加命令处理程序代码
	if (m_modelDlg.GetSafeHwnd() && m_modelDlg.IsWindowVisible())
	{
		m_modelDlg.ShowWindow(SW_HIDE);
	}
	else
	{
		if (!m_modelDlg.GetSafeHwnd())
		{
			m_modelDlg.Create(IDD_MODEL, this);
		}
		m_modelDlg.ShowWindow(SW_SHOW);
	}
	POSITION pos = NULL;
	CMy3DEmultationDoc * pDoc = (CMy3DEmultationDoc *)GetActiveDocument();
	if (pDoc != NULL)
		pos = pDoc->GetFirstViewPosition();
	while (pos != NULL) {
		CView* pNextView = pDoc->GetNextView(pos);
		if (pNextView->IsKindOf(RUNTIME_CLASS(CMy3DEmultationView)))
		{
			CMy3DEmultationView * pLeftView = (CMy3DEmultationView*)pNextView;
			pLeftView->Invalidate(1);
		}
		if (pNextView->IsKindOf(RUNTIME_CLASS(CShowResult)))
		{
			CShowResult * pRightView = (CShowResult*)pNextView;
			pRightView->Invalidate(1);
		}
	}
}
