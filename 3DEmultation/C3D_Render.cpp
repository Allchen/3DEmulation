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
Attach() ��OpenGL������ӵ� hwndDisp ��ָ�Ĵ�����.
Ҫ���,������ô˺���.
*/
bool C3D_Render::Attach(HWND hwndDisp)
{
	// �����֮ǰ�Ĵ�����ͬ����ֱ�ӷ���
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

	// Attach()���µ�hwndDisp��
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
	static PIXELFORMATDESCRIPTOR pfd =			//pfd ���ߴ���������ϣ���Ķ���
	{
		sizeof(PIXELFORMATDESCRIPTOR),		//���߸�ʽ�������Ĵ�С
		1,									// �汾��
		PFD_DRAW_TO_WINDOW |				// ��ʽ����֧�ִ���
		PFD_SUPPORT_OPENGL |				// ��ʽ����֧��OpenGL
		PFD_DRAW_TO_BITMAP |
		//PFD_SUPPORT_GDI | 
		PFD_DOUBLEBUFFER,					// ����֧��˫����
		PFD_TYPE_RGBA,						// ���� RGBA ��ʽ
		24,									// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,					// ���Ե�ɫ��λ
		0,									// ��Alpha����
		0,									// ����Shift Bit
		0,									// �޾ۼ�����
		0, 0, 0, 0,							// ���Ծۼ�λ
		32,									// 32λ Z-���� (��Ȼ���) 
		0,									// ��ģ�建��
		0,									// �޸�������
		PFD_MAIN_PLANE,						// ����ͼ��
		0,									// ����
		0, 0, 0								// ���Բ�����
	};

	int pixelformat;

	/*
	�������˵������������ظ�ʽ��
	����CClientDC clientDC(this);
	  ����int PixelFormat = ChoosePixelFormat(clientDC.m_hDC,&pfd);
		����BOOL result=SetPixelFormat(clientDC.m_hDC,PixelFormat,&pfd);

		  ������һ�����˵���õ�һ��Ӧ�ô��ڿͻ���������������
			��һ�е���ChoosePixelFormat()ѡ��һ�����ظ�ʽ���������ظ�ʽ�����ŷ��ظ�pixelFormat������
			�����е�һ��������ѡ�����ظ�ʽ���豸������ľ�����ڶ���������PIXELFORMATDESCRIPTOR�ṹ
			�ĵ�ַ���������ʧ���򷵻�0�����򷵻����ظ�ʽ�����š�
			�����е���SetPixelFormat()�������ظ�ʽ�����������ֱ����豸������ľ�������ظ�ʽ������
			��PIXELFORMATDESCRIPTOR�ṹ�ĵ�ַ��������óɹ��򷵻�TRUE�����򷵻�FALSE��
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

//��ʼ��
bool C3D_Render::IniOpenGL(HWND hwndDisp)
{
	//��ȡ��ʾ���ڵĴ��ھ��
	HDC hDC = ::GetDC(hwndDisp);

	//�ػ��ж�
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

	// ������Ӱƽ��
	glShadeModel(GL_SMOOTH);
	//��ɫ����
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//������Ȼ���
	glClearDepth(1.0f);
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//������Ȳ��Ե�����
	glDepthFunc(GL_LEQUAL);
	//����ϵͳ��͸�ӽ�������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	//����
	glEnable(GL_TEXTURE_2D);
	if (!m_Texture.LoadBitmap("ground.bmp"))
	{
		return false;
	}
	glGenTextures(1, &m_Texture.ID);                        /**< ����һ������������� */

	glBindTexture(GL_TEXTURE_2D, m_Texture.ID);             /**< ����������� */
															/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture.imageWidth,
		m_Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		m_Texture.image);

	GLfloat LightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 	/**< ��������� */
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };		/**< �������� */
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	/**< �������� */
															/** ���ù�Դ������ֵ */
	float lightPosition[3] = {100,100,100 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				/**< ���û����� */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				/**< ��������� */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);			/**< ��������� */
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);			/**< ���ù�Դλ�� */
																/** ���ù��պ͹�Դ */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	return true;
}

void C3D_Render::PreRender(int cx,int cy) 
{
	//ѡ��ͶӰ����
	glMatrixMode(GL_PROJECTION);
	//����ͶӰ����
	glLoadIdentity();
	//���㴰�ڵ���۱���
	gluPerspective(45.0f, (GLfloat)cx / (GLfloat)cy, 0.1f, 3.0*10e+11f);
	//����ģ�͹۲����
	glMatrixMode(GL_MODELVIEW);
	//����ģ�͹۲����
	glLoadIdentity();
	//���õ�ǰ���ӿ�
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
	glDisable(GL_LIGHTING);	/**< �رչ��� */
	DrawAxis(length / 2);
	DrawGround(length, width);
	//DrawScanLine();
	//DrawCameraLine();
	//DrawModels();
	//DrawPointCloud(m_pointCloud, m_pointCloudType);
	//DrawCameraPhoto(m_cameraData, m_cameraDataType);
	//DrawScanOut();
	//DrawCameraOut();
	glEnable(GL_LIGHTING); /**< ���ù��� */
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
	//����1
	glTexCoord2f(length, 0.0);   glVertex3f(length / 2, 0, -width / 2);
	glTexCoord2f(0.0, 0.0);      glVertex3f(-length / 2, 0, -width / 2);
	glTexCoord2f(0.0, width);    glVertex3f(-length / 2, 0, width / 2);
	glTexCoord2f(length, width); glVertex3f(length / 2, 0, width / 2);

	//����2
	// 	glTexCoord2f(length, 0.0);   glVertex3f(length, 0, 0);
	// 	glTexCoord2f(0.0, 0.0);      glVertex3f(0, 0, 0);
	// 	glTexCoord2f(0.0, width);    glVertex3f(0, 0, width);
	// 	glTexCoord2f(length, width); glVertex3f(length, 0, width);

	//û������
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
	glDisable(GL_LIGHTING);	/**< �رչ��� */
	glTranslatef(m_LPos.x, m_LPos.y, m_LPos.z);
	glutWireSphere(1.0, 15, 15);
	glEnable(GL_LIGHTING); /**< ���ù��� */
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_leftBtnDown = true;
	m_oldPoint = point;
}


void C3D_Render::OnLButtonUp()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_leftBtnDown = false;
}

void C3D_Render::OnMouseWheel(short zDelta, CPoint pt)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
			::MessageBox(NULL, _T("�ͷ�DC��RCʧ�ܡ�"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		}
		//Delete the rendering context
		if (wglDeleteContext(m_hRC) == FALSE)
		{
			::MessageBox(NULL, _T("�ͷ�RCʧ�ܡ�"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
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