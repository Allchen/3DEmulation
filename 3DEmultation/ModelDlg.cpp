// ModelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DEmultation.h"
#include "ModelDlg.h"
#include "afxdialogex.h"
#include"MainFrm.h"
#include"3DEmultationDoc.h"
#include"3DEmultationView.h"
#include"ShowResult.h"

// CModelDlg �Ի���

IMPLEMENT_DYNAMIC(CModelDlg, CDialogEx)

CModelDlg::CModelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MODEL, pParent)
{

}

CModelDlg::~CModelDlg()
{
}

void CModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_cbModelList);
}


BEGIN_MESSAGE_MAP(CModelDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_DELETE_MODEL, &CModelDlg::OnClickedBtnDeleteModel)
	ON_BN_CLICKED(IDC_BTN_MODEL_PARAMETER, &CModelDlg::OnClickedBtnModelParameter)
	ON_BN_CLICKED(IDC_BTN_OPEN_MODEL, &CModelDlg::OnClickedBtnOpenModel)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CModelDlg::OnSelchangeComboModelList)
	ON_BN_CLICKED(IDOK, &CModelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CModelDlg ��Ϣ�������


void CModelDlg::OnClickedBtnDeleteModel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMy3DEmultationView *pView = (CMy3DEmultationView *)((CMainFrame *)AfxGetMainWnd())->m_splitterWnd.GetPane(0,0);
	if (nullptr == pView)
	{
		AfxMessageBox(_T("��ȡ��ͼ��ָ��ʧ��!"));
		return;
	}

	if (!pView->m_render.IsModelExisted(m_cbIndex2ModelID[GetCurComBoxID()]))
	{
		AfxMessageBox(_T("ģ�Ͳ�����!"));
		return;
	}
	pView->m_render.DeleteModel(m_cbIndex2ModelID[GetCurComBoxID()]);
	UpdataCBIndex2ModelID(GetCurComBoxID());
	m_cbModelList.DeleteString(GetCurComBoxID());
	m_cbModelList.SetCurSel(CB_ERR);

	SetCurComBoxID(CB_ERR);
}


void CModelDlg::OnClickedBtnModelParameter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMy3DEmultationView *pView = (CMy3DEmultationView *)((CMainFrame *)AfxGetMainWnd())->m_splitterWnd.GetPane(0, 0);
	CShowResult *pRView = (CShowResult *)((CMainFrame *)AfxGetMainWnd())->m_splitterWnd.GetPane(0, 1);
	if (nullptr == pView && nullptr == pRView)
	{
		AfxMessageBox(_T("��ȡ��ͼ��ָ��ʧ��!"));
		return;
	}

	if (pView->m_render.GetModelMap().empty())
	{
		AfxMessageBox(_T("û�м���ģ��!"));
		return;
	}

	int modelID = m_cbIndex2ModelID[GetCurComBoxID()];
	ModelParameter modelParaDlg;
	modelParaDlg.SetTransParameter(pView->m_render.GetModelMap()[modelID].GetTransPara());
	modelParaDlg.SetLightPos(pView->m_render.GetLPos());
	modelParaDlg.SetLightPos(pRView->m_render.GetLPos());
	if (modelParaDlg.DoModal() == IDOK)
	{
		pView->m_render.GetModelMap()[modelID].SetTransPara(modelParaDlg.GetTransParameter());
		pView->m_render.SetLPos(modelParaDlg.GetLightPos());
		pRView->m_render.SetLPos(modelParaDlg.GetLightPos());
	}
}


void CModelDlg::OnClickedBtnOpenModel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fDlg(TRUE, _T(".3ds"), NULL, OFN_HIDEREADONLY, _T("3DS �ļ�(*.3DS)|*.3ds||"));

	if (fDlg.DoModal() == IDOK)
	{
		m_fileName = fDlg.GetFileName();
		m_pathName = fDlg.GetPathName();
		C3DSModel model;
		model.Load3DS(fDlg.GetPathName());

		CString fileItem(_T("ģ��"));
		CString tmp;
		tmp.Format(_T("%d:"), m_addModelTime);
		fileItem = fileItem + tmp + fDlg.GetPathName();

		//m_cbIndex2ModelID.push_back(m_addModelTime);
		m_cbIndex2ModelID[m_cbModelList.GetCount()] = m_addModelTime;
		SetCurComBoxID(m_cbModelList.GetCount());

		m_cbModelList.InsertString(m_cbModelList.GetCount(), fileItem);
		m_cbModelList.SetCurSel(m_cbModelList.GetCount() - 1);
		CMy3DEmultationView *pView = (CMy3DEmultationView *)((CMainFrame *)AfxGetMainWnd())->m_splitterWnd.GetPane(0, 0);
		if (nullptr == pView)
		{
			AfxMessageBox(_T("��ȡ��ͼ��ָ��ʧ��!"));
			return;
		}
		pView->m_render.AddModel(m_addModelTime, model);
		pView->m_render.SetCurModelID(m_cbIndex2ModelID[m_addModelTime]);

		++m_addModelTime;

	}
}

void CModelDlg::OnSelchangeComboModelList()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CModelDlg::UpdataCBIndex2ModelID(int index)
{
	if (index < 0 || index >= m_cbModelList.GetCount())
	{
		return;
	}
	std::unordered_map<int, int> tmp;
	for (auto iter = m_cbIndex2ModelID.begin(); iter != std::prev(m_cbIndex2ModelID.end()); ++iter)
	{
		if (iter->first < index)
		{
			tmp[iter->first] = iter->second;
		}
		else
		{
			tmp[iter->first] = (std::next(iter))->second;
		}
	}

	m_cbIndex2ModelID.swap(tmp);
}

void CModelDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
