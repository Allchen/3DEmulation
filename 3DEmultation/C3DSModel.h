#pragma once
#include "DataStructs.h"
#include "ModelParameter.h"
#include <cmath>

class C3DSModel
{
public:
	C3DSModel();
	~C3DSModel();
	bool IsLoad();											//�Ƿ��Ѽ���ģ��
	bool Load3DS(CString filename);
	void Render(void);
	float GetMinHeight()const { return m_3DModel.m_minV.y; }

	void SetTransPara(my::T3ds transPara);
	void SetPosX(float x){ m_transPara.x = x; }
	void SetPosY(float y){ m_transPara.y = y; }
	void SetPosZ(float z){ m_transPara.z = z; }
	void SetRotateX(float x){ m_transPara.d_x = x; }
	void SetRotateY(float y){ m_transPara.d_y = y; }
	void SetRotateZ(float z){ m_transPara.d_z = z; }
	void SetScaleX(float x){ m_transPara.scaleX = x; }
	void SetScaleY(float y){ m_transPara.scaleY = y; }
	void SetScaleZ(float z){ m_transPara.scaleZ = z; }
	my::T3ds GetTransPara(){ return m_transPara; }
	float GetPosX(){ return m_transPara.x; }
	float GetPosY(){ return m_transPara.y; }
	float GetPosZ(){ return m_transPara.z; }
	float GetRotateX(){ return m_transPara.d_x; }
	float GetRotateY(){ return m_transPara.d_y; }
	float GetRotateZ(){ return m_transPara.d_z; }
	float GetScaleX(){ return m_transPara.scaleX; }
	float GetScaleY(){ return m_transPara.scaleY; }
	float GetScaleZ(){ return m_transPara.scaleZ; }
	bool RayHitSphere( my::Ray &ray);
	bool RayRealHitModel(my::Ray &ray, my::Vector3 &vecHit, float &dist,my::Vector3 &Lux,my::Vector3 LightP);
	float GetRais();
	my::Vector3 GetCenterPoint();
	bool GetModelFaceVert(int vertID, my::Vector3 &vert);
	void UpdataModelMatrix();
	void CalModelFaceVert();
	my::t3DModel m_3DModel;
	
private:
	FILE *m_FilePtr;										// 3ds�ļ�ָ��
	int  DisplayList;										////ģ�͵���ʾ�б��ţ�����opengl��Ⱦ��ͼ��
	my::T3ds m_transPara;
	bool m_isLoad;
	std::vector<my::Vector3> m_modelFaceVert;							//ģ�Ͷ�������������ϵ�е�λ��
	float m_modelChangeMatrix[16];
	float m_modelTransMatrix[16];
	float m_modelRotateXMatrix[16];
	float m_modelRotateYMatrix[16];
	float m_modelRotateZMatrix[16];
	float m_modelScaleMatrix[16];

	BYTE ReadByte(void);									// ���ļ��ж�ȡ1���ֽ�
	WORD ReadWord(void);									// ���ļ��ж�ȡ2���ֽ�
	UINT ReadUint(void);									// ���ļ��ж�ȡ4���ֽ�
	UINT ReadString(my::STRING *pStr);						// ���ļ��ж�ȡ�ַ����������ַ������ȣ�
	float ReadFloat(void);									// ���ļ��ж�ȡ������
	UINT ReadMaterial(UINT n);								// ��ȡ����
	UINT ReadObject(UINT n);								// ��ȡ3ds����	
	bool ReadChunk(my::tChunk *pChunk);						// ��ȡ3ds��һ��Chunk��Ϣ
	UINT ReadPrimary(UINT n);								// ��ȡ3ds�ļ���ҪChunk
	UINT ReadEdit(UINT n);									// ��ȡ3ds�������༭Chunk
	UINT ReadObjectInfo(my::t3DObject *pObj, UINT n);		// ��ȡ3ds������Ϣ
	UINT ReadFacetInfo(my::t3DObject *pObj, UINT n);		// ��ȡ����Ϣ
	UINT ReadMatDif(my::tMaterial *pMat, UINT n);			// ��ȡ���ʵ�����������
	UINT ReadMatMap(my::tMaterial *pMat, UINT n);			// ��ȡ���ʵ�����
	my::Vector3 TransformVert(const my::Vector3& fPointSrc);
	void Release(void);										// �ͷ�3dsģ����Դ
	

	my::Vector3 Cross(my::Vector3 v1, my::Vector3 v2);		// �����������Ĳ��
	my::Vector3 Normalize(my::Vector3 vNormal);				// ������λ��
	my::Vector3 GetLux(my::t3DObject *obj,int nFace,my::Vector3 Crossdot,my::Vector3 lightP);
	void ComputeNormals(void);								// ���㶥�㷨����
	void MatrixMulti(float left[], float right[], int rowLeft, int colLeft, int colRight, float res[]);
	void ChangeCenterXYZ(float before[], float after[]);
	bool GetLineABCD(const my::Ray &ray, float &A, float &B, float &C, float &D);//Ax + By + Cz + D = 0;
	bool TriangleHitFace(double A, double B, double C, double D, my::Vector3 triVerts[]);
	bool RayHitTriangle(const my::Ray &ray, my::Vector3 vtri[], float &t, float &u, float &v);
	bool RayHitTriFace(const my::Ray &ray, my::Vector3 vtri[], my::Vector3& vecHit, float &dist);
};

