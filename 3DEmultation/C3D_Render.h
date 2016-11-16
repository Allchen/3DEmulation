#pragma once
#include"stdafx.h"
#include"CBMPLoader.h"
#include "C3DSModel.h"
#include <unordered_map>
#pragma comment( lib, "opengl32.lib" )      
#pragma comment( lib, "glu32.lib" )      
#pragma comment( lib, "glut32.lib" )    

class C3D_Render
{
public:
	C3D_Render();
	virtual ~C3D_Render();

	bool Attach(HWND hwndDisp);
	bool PixelFormat(HDC hDC);
	bool IniOpenGL(HWND hwndDisp);
	void PreRender(int cx,int cy);
	void RenderScene();
	void DrawModels();													//显示模型
	void DrawGround(int length, int width);								//显示地面
	void DrawLight();
	void DrawAxis(int length);											//显示坐标轴
	void OnMouseMove(CPoint point);
	void OnLButtonUp();
	void OnLButtonDown(CPoint point);
	void OnMouseWheel(short zDelta, CPoint pt);
	void OnDestroy();
	void AddModel(int id, const C3DSModel &model);
	bool IsModelExisted(int id) { return m_modelMap.end() != m_modelMap.find(id); }
	void DeleteModel(int id) { m_modelMap.erase(id); }
	void SetCurModelID(int id) { m_curModelID = id; }
	int GetCurModelID() { return m_curModelID; }
	my::Vector3 GetLPos() { return m_LPos; }
	void SetLPos(my::Vector3 pos) { m_LPos = pos; }
	
	std::unordered_map<int, C3DSModel>& GetModelMap() { return m_modelMap; }
public:
	HWND  m_hWND;							                         //上一次目标窗口
	HGLRC m_hRC;							                         //gl句柄
	HDC   m_hDC;
	C3DSModel m_3dCamera;
	C3DSModel m_3dRadar;
	CBMPLoader m_Texture;
	my::Vector3 m_LPos;
	my::Vector3 m_ground;												//x表示地面长度,y高,z宽度
	int m_mouseWheel;
	float m_angleX;
	float m_angleY;
	my::Vector3 m_eye;
	float m_scale;
	float m_scaleUnit;
	bool m_leftBtnDown;
	CPoint m_oldPoint;
	std::unordered_map<int, my::POINT_TYPE> m_modelID2PointType;
	std::unordered_map<int, C3DSModel> m_modelMap;
	int m_curModelID;
};

