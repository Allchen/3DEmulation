#include "stdafx.h"
#include "C3D_Render.h"
#include"3DEmultation.h"

extern CMy3DEmultationApp theApp;
C3D_Render::C3D_Render()
	:m_hWND(NULL), m_hDC(NULL), m_hRC(NULL),
	m_LPos(20,0,20),
	m_ground(20, 0, 20),
	m_mouseWheel(0),
	m_angleX(0.0),
	m_angleY(0.0),
	m_eye(m_ground.x, m_ground.y + m_ground.x * 2, m_ground.z),
	m_scale(1.0),
	m_scaleUnit(2.0),
	m_leftBtnDown(false),
	m_oldPoint(CPoint())
{
}


C3D_Render::~C3D_Render()
{
}

/*
Attach() 将OpenGL输出附加到 hwndDisp 所指的窗口上.
要输出,必须调用此函数.
*/
bool C3D_Render::Attach(HWND hwndDisp)
{
	// 如果和之前的窗口相同，则直接返回
	if (hwndDisp == m_hWND)
	{
		return true;
	}

	if (hwndDisp == NULL)
	{
		return false;
	}

	// Free the target DeviceContext (window)
	wglMakeCurrent(NULL, NULL);
	if (m_hDC != NULL)
		::ReleaseDC(m_hWND, m_hDC);

	// Attach()到新的hwndDisp上
	m_hWND = hwndDisp;
	m_hDC = ::GetDC(m_hWND);
	if (!wglMakeCurrent(m_hDC, m_hRC))
	{
		return false;
	}
	return true;
}

bool  C3D_Render::PixelFormat(HDC hDC)
{
	static PIXELFORMATDESCRIPTOR pfd =			//pfd 告诉窗口我们所希望的东东
	{
		sizeof(PIXELFORMATDESCRIPTOR),		//上诉格式描述符的大小
		1,									// 版本号
		PFD_DRAW_TO_WINDOW |				// 格式必须支持窗口
		PFD_SUPPORT_OPENGL |				// 格式必须支持OpenGL
		PFD_DRAW_TO_BITMAP |
		//PFD_SUPPORT_GDI | 
		PFD_DOUBLEBUFFER,					// 必须支持双缓冲
		PFD_TYPE_RGBA,						// 申请 RGBA 格式
		24,									// 选定色彩深度
		0, 0, 0, 0, 0, 0,					// 忽略的色彩位
		0,									// 无Alpha缓存
		0,									// 忽略Shift Bit
		0,									// 无聚集缓存
		0, 0, 0, 0,							// 忽略聚集位
		32,									// 32位 Z-缓存 (深度缓存) 
		0,									// 无模板缓存
		0,									// 无辅助缓存
		PFD_MAIN_PLANE,						// 主绘图层
		0,									// 保留
		0, 0, 0								// 忽略层遮罩
	};

	int pixelformat;

	/*
	下面举例说明如何设置像素格式。
	　　CClientDC clientDC(this);
	  　　int PixelFormat = ChoosePixelFormat(clientDC.m_hDC,&pfd);
		　　BOOL result=SetPixelFormat(clientDC.m_hDC,PixelFormat,&pfd);

		  　　第一行语句说明得到一个应用窗口客户区的设置描述表。
			第一行调用ChoosePixelFormat()选择一个像素格式，并将像素格式索引号返回给pixelFormat变量；
			函数中第一个参数是选择像素格式的设备描述表的句柄，第二个参数是PIXELFORMATDESCRIPTOR结构
			的地址。如果调用失败则返回0；否则返回像素格式索引号。
			第三行调用SetPixelFormat()设置像素格式，三个参数分别是设备描述表的句柄、像素格式索引号
			和PIXELFORMATDESCRIPTOR结构的地址。如果调用成功则返回TRUE，否则返回FALSE。
			*/


	if ((pixelformat = ChoosePixelFormat(hDC, &pfd)) == 0)
	{
		pixelformat = 1;
		if (DescribePixelFormat(hDC,
			pixelformat,
			sizeof(PIXELFORMATDESCRIPTOR),
			&pfd) == 0)
		{
			return FALSE;
		}
		return FALSE;
	}

	if (SetPixelFormat(hDC, pixelformat, &pfd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

//初始化
bool C3D_Render::IniOpenGL(HWND hwndDisp)
{
	//获取显示窗口的窗口句柄
	HDC hDC = ::GetDC(hwndDisp);

	//重绘判断
	if (hDC == this->m_hDC)
	{
		m_hRC = wglCreateContext(hDC);
		return true;
	}

	if (!PixelFormat(hDC))
	{
		return false;
	}

	// Create HGLRC
	if ((m_hRC = wglCreateContext(hDC)) == NULL)
	{
		return false;
	}

	// Free the target DeviceContext (window)
	wglMakeCurrent(NULL, NULL);
	::ReleaseDC(hwndDisp, hDC);

	Attach(hwndDisp);

	// 启用阴影平滑
	glShadeModel(GL_SMOOTH);
	//黑色背景
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//设置深度缓存
	glClearDepth(1.0f);
	//启用深度测试
	glEnable(GL_DEPTH_TEST);
	//所作深度测试的类型
	glDepthFunc(GL_LEQUAL);
	//告诉系统对透视进行修正
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	//纹理
	glEnable(GL_TEXTURE_2D);
	if (!m_Texture.LoadBitmap("ground.bmp"))
	{
		return false;
	}
	glGenTextures(1, &m_Texture.ID);                        /**< 生成一个纹理对象名称 */

	glBindTexture(GL_TEXTURE_2D, m_Texture.ID);             /**< 创建纹理对象 */
															/** 控制滤波 */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/** 创建纹理 */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture.imageWidth,
		m_Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		m_Texture.image);

	GLfloat LightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 	/**< 环境光参数 */
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };		/**< 漫射光参数 */
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	/**< 镜面光参数 */
															/** 设置光源的属性值 */
	float lightPosition[3] = {100,100,100 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				/**< 设置环境光 */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				/**< 设置漫射光 */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);			/**< 设置漫射光 */
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);			/**< 设置光源位置 */
																/** 启用光照和光源 */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	return true;
}

void C3D_Render::PreRender(int cx,int cy) 
{
	//选择投影矩阵
	glMatrixMode(GL_PROJECTION);
	//重置投影矩阵
	glLoadIdentity();
	//计算窗口的外观比例
	gluPerspective(45.0f, (GLfloat)cx / (GLfloat)cy, 0.1f, 3.0*10e+11f);
	//设置模型观察矩阵
	glMatrixMode(GL_MODELVIEW);
	//重置模型观察矩阵
	glLoadIdentity();
	//设置当前的视口
	glViewport(0, 0, cx, cy);
}

void C3D_Render::RenderScene() 
{
	wglMakeCurrent(m_hDC, m_hRC);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	float length = m_ground.x;
	float width = m_ground.z;
	float height = m_ground.y + 500;
	m_scale = 1 - 7 * m_mouseWheel / 1200;
	//length = max(m_scanParameter.send.GetLength(), m_cameraParamameter.startP.GetLength());
	gluLookAt(m_eye.x, m_eye.y, m_eye.z,//eye
		0.0, 0.0, 0.0,//center
		0.0, 1.0, 0.0);//up
	glRotatef(m_angleX, 1, 0, 0);
	glRotatef(m_angleY, 0, 1, 0);
	DrawLight();
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);	/**< 关闭光照 */
	DrawAxis(length / 2);
	DrawGround(length, width);
	//DrawScanLine();
	//DrawCameraLine();
	//DrawModels();
	//DrawPointCloud(m_pointCloud, m_pointCloudType);
	//DrawCameraPhoto(m_cameraData, m_cameraDataType);
	//DrawScanOut();
	//DrawCameraOut();
	glEnable(GL_LIGHTING); /**< 启用光照 */
	glPopAttrib();
	DrawModels();
	SwapBuffers(m_hDC);
	//wglMakeCurrent(NULL, NULL);
}

void C3D_Render::DrawAxis(int length)
{
	glPushMatrix();

	GLfloat zero[] = { 0, 0, 0 };
	GLfloat x[] = { length, 0, 0 };
	GLfloat y[] = { 0, length, 0 };
	GLfloat z[] = { 0, 0, length };

	glLineWidth(20);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3fv(zero);
	glVertex3fv(x);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3fv(zero);
	glVertex3fv(y);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3fv(zero);
	glVertex3fv(z);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(x[0], x[1], x[2]);
	//font.PrintText("X", x[0], x[1]);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(y[0], y[1], y[2]);
	//font.PrintText("Y", x[0], x[1]);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(z[0], z[1], z[2]);
	//font.PrintText("Z", z[0], z[1]);
	glPopMatrix();
}

void C3D_Render::DrawGround(int length, int width)
{
	glPushMatrix();
	GLfloat groundColor[] = { 0.5, 0.5, 0.5 };
	glColor3fv(groundColor);
	glBindTexture(GL_TEXTURE_2D, m_Texture.ID);
	glBegin(GL_QUADS);
	//地形1
	glTexCoord2f(length, 0.0);   glVertex3f(length / 2, 0, -width / 2);
	glTexCoord2f(0.0, 0.0);      glVertex3f(-length / 2, 0, -width / 2);
	glTexCoord2f(0.0, width);    glVertex3f(-length / 2, 0, width / 2);
	glTexCoord2f(length, width); glVertex3f(length / 2, 0, width / 2);

	//地形2
	// 	glTexCoord2f(length, 0.0);   glVertex3f(length, 0, 0);
	// 	glTexCoord2f(0.0, 0.0);      glVertex3f(0, 0, 0);
	// 	glTexCoord2f(0.0, width);    glVertex3f(0, 0, width);
	// 	glTexCoord2f(length, width); glVertex3f(length, 0, width);

	//没有纹理
	// 	glVertex3f(length, 0, 0);
	// 	glVertex3f(0, 0, 0);
	// 	glVertex3f(0, 0, width);
	// 	glVertex3f(length, 0, width);
	glEnd();
	glPopMatrix();
}

void C3D_Render::DrawLight()
{
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);	/**< 关闭光照 */
	glTranslatef(m_LPos.x, m_LPos.y, m_LPos.z);
	glutWireSphere(1.0, 15, 15);
	glEnable(GL_LIGHTING); /**< 启用光照 */
	glPopAttrib();
	glPopMatrix();
}

void C3D_Render::OnMouseMove(CPoint point)
{
	if (m_leftBtnDown)
	{
		m_angleX += (point.y - m_oldPoint.y) / 20;
		m_angleY += (point.x - m_oldPoint.x) / 20;
		CWnd *pWnd = CWnd::FromHandle(m_hWND);
		pWnd->Invalidate();
	}
}

void C3D_Render::OnLButtonDown(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_leftBtnDown = true;
	m_oldPoint = point;
}


void C3D_Render::OnLButtonUp()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_leftBtnDown = false;
}

void C3D_Render::OnMouseWheel(short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_mouseWheel += zDelta;
	int step = zDelta / 60;
	m_eye.x -= step;
	m_eye.y -= step;
	m_eye.z -= step;
	CWnd *pWnd = CWnd::FromHandle(m_hWND);
	pWnd->Invalidate();
}

void C3D_Render::OnDestroy()
{
	//Delete the RC
	if (m_hRC)
	{
		//Make the RC non-current
		if (wglMakeCurrent(NULL, NULL) == FALSE)
		{
			::MessageBox(NULL, _T("释放DC或RC失败。"), _T("关闭错误"), MB_OK | MB_ICONINFORMATION);
		}
		//Delete the rendering context
		if (wglDeleteContext(m_hRC) == FALSE)
		{
			::MessageBox(NULL, _T("释放RC失败。"), _T("关闭错误"), MB_OK | MB_ICONINFORMATION);
		}
		m_hRC = NULL;
	}

	//Set it to NULL
	m_hDC = NULL;
}

void C3D_Render::AddModel(int id, const C3DSModel &model)
{
	m_modelMap[id] = model;
	m_modelID2PointType[id] = my::POINT_OBJ_DOWN;
	if (m_modelMap.size() == 2)
	{
		int firstModelID = m_modelMap.begin()->first;
		int secondModelID = std::next(m_modelMap.begin())->first;
		if (m_modelMap[firstModelID].GetMinHeight() > m_modelMap[secondModelID].GetMinHeight())
		{
			m_modelID2PointType[firstModelID] = my::POINT_OBJ_UP;
		}
		else
		{
			m_modelID2PointType[secondModelID] = my::POINT_OBJ_UP;
		}
	}
}

void C3D_Render::DrawModels()
{
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.7);
	for (auto iter = m_modelMap.begin(); iter != m_modelMap.end(); ++iter)
	{
		/*Move2Center(iter->first);
		iter->second.m_3DModel.m_vCenter.x = 0;
		iter->second.m_3DModel.m_vCenter.y = 0;
		iter->second.m_3DModel.m_vCenter.z = 0;*/
		glPushMatrix();
		glTranslatef(iter->second.GetPosX(), iter->second.GetPosY(), iter->second.GetPosZ());
		glScalef(iter->second.GetScaleX(), iter->second.GetScaleY(), iter->second.GetScaleZ());
		glRotatef(iter->second.GetRotateX(), 1, 0, 0);
		glRotatef(iter->second.GetRotateY(), 0, 1, 0);
		glRotatef(iter->second.GetRotateZ(), 0, 0, 1);
		iter->second.Render();
		glPopMatrix();
	}
	glPopMatrix();
}