#pragma once
//#include"stdafx.h"
#include "resource.h"
#include"DataStructs.h"

// ModelParameter 对话框

class ModelParameter : public CDialogEx
{
	DECLARE_DYNAMIC(ModelParameter)

public:
	ModelParameter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModelParameter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_PARAMETER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_posX;
	float m_posY;
	float m_posZ;
	float m_rotateX;
	float m_rotateY;
	float m_rotateZ;
	float m_scaleX;
	float m_scaleY;
	float m_scaleZ;
	float m_lpX;
	float m_lpY;
	float m_lpZ;
	afx_msg void OnBnClickedOk();
	my::Vector3 GetLightPos();
	void SetLightPos(my::Vector3);
	void SetLPX(float x) { m_lpX = x; }
	void SetLPY(float y) { m_lpY = y; }
	void SetLPZ(float z) { m_lpZ = z; }
	float GetLPX() { return m_lpX; }
	float GetLPY() { return m_lpY; }
	float GetLPZ() { return m_lpZ; }
	my::T3ds GetTransParameter();
	void SetTransParameter(my::T3ds parameter);
	void SetPosX(float x) { m_posX = x; }
	void SetPosY(float y) { m_posY = y; }
	void SetPosZ(float z) { m_posZ = z; }
	void SetRotateX(float x) { m_rotateX = x; }
	void SetRotateY(float y) { m_rotateY = y; }
	void SetRotateZ(float z) { m_rotateZ = z; }
	void SetScaleX(float x) { m_scaleX = x; }
	void SetScaleY(float y) { m_scaleY = y; }
	void SetScaleZ(float z) { m_scaleZ = z; }
	float GetPosX() { return m_posX; }
	float GetPosY() { return m_posY; }
	float GetPosZ() { return m_posZ; }
	float GetRotateX() { return m_rotateX; }
	float GetRotateY() { return m_rotateY; }
	float GetRotateZ() { return m_rotateZ; }
	float GetScaleX() { return m_scaleX; }
	float GetScaleY() { return m_scaleY; }
	float GetScaleZ() { return m_scaleZ; }
	
};
