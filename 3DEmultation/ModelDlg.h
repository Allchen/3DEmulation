#pragma once
#include<string>
#include<unordered_map>
#include"ModelParameter.h"
#include"DataStructs.h"
#include"C3DSModel.h"
#include "afxwin.h"


// CModelDlg �Ի���

class CModelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelDlg)

public:
	CModelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModelDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	int m_addModelTime;
	int m_curModelID;
	CString m_fileName;
	CString m_pathName;
	C3DSModel m_model;
	std::unordered_map<int, int> m_cbIndex2ModelID;
	void UpdataCBIndex2ModelID(int index);
public:
	int GetAddModelTimes() { return m_addModelTime; }
	int GetCurComBoxID() { return m_curModelID; }
	void SetCurComBoxID(int i) { m_curModelID = i; }
	CString get3DSFileName() { return m_fileName; }
	CString get3DSPathName() { return m_pathName; }
	C3DSModel getMoldel() { return m_model; }
	CComboBox m_cbModelList;
	afx_msg void OnClickedBtnDeleteModel();
	afx_msg void OnClickedBtnModelParameter();
	afx_msg void OnClickedBtnOpenModel();
	afx_msg void OnSelchangeComboModelList();
	afx_msg void OnBnClickedOk();
};
