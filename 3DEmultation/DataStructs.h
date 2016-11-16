#pragma  once
#include <vector>
#include <string>
#include <cmath>
//using namespace std;
//3DS Related Structure 
#define BYTE unsigned char
#define WORD unsigned short 
#define UINT unsigned int
#define	 MAX_TEXTURE 100

// HDL64E-S2��������

// GeneralDefiniton
const float PI = 3.14;
const UINT LASER_NUM = 512;						// 64·����
const float HORI_FOV = 30;                    // ˮƽ�ӳ���360��
const float HORI_AZIMUTH_RES = 0.06;           // ˮƽɨ��ֱ���0.06��

const float VERT_FOV = 30;                   // ��ֱ�ӳ���33.2��
const float VERT_SCAN_RANGE_LOWBOUND = -24.33; // ��ֱɨ���½�-24.33��
const float VERT_SCAN_RANGE_UPBOUND = 2.0;       // ��ֱɨ���Ͻ�2��
const float VERT_SCAN_VERT_RES = 0.06;			//��ֱɨ��ֱ���0.06��
												 // UpperBlock
const UINT UPPERBLOCK_LASER_NUM = 32;          // �ϲ�ģ����32·����
const float UPPERBLOCK_LOWBOUND = -8.33;       // �ϲ�ģ�鴹ֱɨ���½�-8.33��
const float UPPERBLOCK_UPBOUND = 2.0;          // �ϲ�ģ�鴹ֱɨ���Ͻ�2��
const float UPPERBLOCK_VERT_RES = 0.333;       // �ϲ�ģ�鴹ֱɨ��ֱ���1/3��

											   // LowerBlock
const UINT LOWERBLOCK_LASER_NUM = 32;           // �²�ģ����32·����
const float LOWERBLOCK_LOWBOUND = -24.33;       // �²�ģ�鴹ֱɨ���½�
const float LOWERBLOCK_UPBOUND = -8.33;           // �²�ģ�鴹ֱɨ���Ͻ�
const float LOWERBLOCK_VERT_RES = 0.500;       // �²�ģ�鴹ֱɨ��ֱ���1/2��

const UINT CAMERA_NUM = 5000;
const float CAMERA_HORI = 30;
const float HORI_CAMERA_RES = 0.006;
const float CAMERA_VERT = 30;
const float VERT_CAMERA_RES = 0.006;
namespace my
{ 
	//#define  BYTE unsigned char
	//#define  WORD unsigned short 
	//#define  UINT unsigned int

	//#define MAX_TEXTURES 100

	const float inch2Meter = 39.37;// 0.0254;
	const float meter2Inch = 0.0254;

	struct STRING
	{
		char string[128];
	};

	// 2ά����
	struct Vector2
	{
		float x, y;
		Vector2() :x(0), y(0){};
		Vector2(float x1,float y1) :x(x1), y(y1){};
	};

	// 3ά����
	struct Vector3
	{
	public:
		// ������ʼ��
		Vector3():x(0),y(0),z(0) {}
		Vector3(float X, float Y, float Z)	{ x = X; y = Y; z = Z; }
		Vector3(const Vector3& v) :x(v.x), y(v.y), z(v.z){}

		// �������
		Vector3 operator+(Vector3 &vVector)	{ return Vector3(x + vVector.x, y + vVector.y, z + vVector.z); }
		// �������
		Vector3 operator-(Vector3 &vVector)	{ return Vector3(x - vVector.x, y - vVector.y, z - vVector.z); }
		// �������
		Vector3 operator*(float num)		{ return Vector3(x * num, y * num, z * num); }
		Vector3 operator/(float num)		{ return Vector3(x / num, y / num, z / num); }
		Vector3 operator=(const Vector3& v)		{ x = v.x; y = v.y; z = v.z; return *this; }

		// ���������Ĳ��
		Vector3 Cross(const Vector3 &rhs) const { return Vector3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x); }

		// ���������ĵ��
		float Dot(const Vector3 &rhs) const { return x*rhs.x + y*rhs.y + z*rhs.z; }

		//������������
		float GetLength() const { return (float)sqrt((x*x) + (y*y) + (z*z)); }

		// ���������ĳ��ȵ�ƽ��
		float GetSquaredLength() const { return (x*x) + (y*y) + (z*z); }

		void GetVector3(float X, float Y, float Z) { x = X; y = Y; z = Z; }

		Vector3 GetVector(float X, float Y, float Z) const { return Vector3(X, Y, Z); }

		//��λ������
		void Normalize()
		{
			float length = GetLength();

			if (length == 1 || length == 0)
				return;

			float scalefactor = 1.0f / length;
			x *= scalefactor;
			y *= scalefactor;
			z *= scalefactor;
		}
		float x, y, z;
	};

	// ����Chunk��Ϣ
	struct tChunk
	{
		WORD ID;										// Chunk��ID
		UINT length;									// Chunk�ĳ���
/*		tChunk() :ID(0), length(0){};*/
	};

	// ����3ds��һЩ��ʹ�õ���ChunkID
	// ��Chunk,��ÿ���ļ��Ŀ�ʼλ��                                                                                                                                                                                                                                                                                                                                                                                                                                     
	const WORD PRIMARY = 0x4D4D;
	const WORD PRIM_EDIT = 0x3D3D;						// ChunkID��3dsģ��
	const WORD EDIT_MAT = 0xAFFF;						// ChunkID������
	const WORD MAT_NAME = 0xA000;						// ChunkID����������
	const WORD MAT_AMB = 0xA010;						// ChunkID�����ʻ��������ԣ�ûʹ�õ���
	const WORD MAT_DIF = 0xA020;						// ChunkID����������������
	const WORD MAT_SPE = 0xA030;						// ChunkID�����ʾ��淴�����ԣ�ûʹ�õ���
	const WORD MAT_MAP = 0xA200;						// ChunkID�����ʵ�����
	const WORD MAP_NAME = 0xA300;						// ChunkID�����������
	const WORD EDIT_OBJECT = 0x4000;					// ChunkID��3ds������桢�����Ϣ
	const WORD OBJECT_INFO = 0x4100;					// ChunkID���������Ҫ��Ϣ
	const WORD OBJECT_VERTEX = 0x4110;					// ChunkID������Ķ�����Ϣ
	const WORD OBJECT_FACET = 0x4120;					// ChunkID�����������Ϣ
	const WORD FACET_MAT = 0x4130;						// ChunkID��������еĲ���
	const WORD FACET_SMOOTH = 0x4150;					// ChunkID����⻬��Ϣ��ûʹ�õ���
	const WORD OBJECT_UV = 0x4140;						// ChunkID������������Ϣ
	const WORD OBJECT_LOCAL = 0x4160;
	const WORD PRIM_KEY = 0xB000;						// ChunkID�����еĹؼ�֡��Ϣ��ûʹ�õ���
	const WORD COLOR_BYTE = 0x0011;						// ChunkID����ɫ


	// ��������Ϣ���������������������ֵ��
	struct tFace
	{//vertIndexҪ�ĳ�vector?????//need to do
		int vertIndex[3];								// 3�����������ֵ
		int	matID;										// �����Ӧ�Ĳ���ID
/*		tFace() :vertIndex(3, 0), matID(0){}*/
	};

	// ���浥��3ds����
	struct t3DObject
	{
		int  numOfVerts;								// �ö��󶥵�ĸ���
		int  numOfFaces;								// �ö�����ĸ���
		int  numTexVertex;								// �ö�����������ĸ���
		my::STRING	 objName;							// ������������
		my::Vector3  *pVerts;							// ���涥������
		my::Vector3  *pNormals;							// �����ķ�����
		my::Vector2  *pTexVerts;						// ������������
		my::tFace	 *pFaces;							// ��������Ϣ���������������Ӧ�Ĳ��ʣ�
// 		t3DObject() :numOfVerts(0), numOfFaces(0), numTexVertex(0), objName(my::STRING()),
// 			pVerts(nullptr), pNormals(nullptr), pTexVerts(nullptr), pFaces(nullptr){}
	} ;

	// ���������Ϣ��
	struct tMaterial
	{
		my::STRING  matName;							// ���ʵ�����
		my::STRING  mapName;							// ��������ƣ�bmp��jpg�ȵ��ļ�����
		BYTE	color[3];								// ������ɫ
		UINT	texureId;								// �����ID��ָ�����������
		bool	isTexMat;								// �ò����ǲ��ǰ���������
// 		tMaterial() :matName(my::STRING()), mapName(my::STRING()),
// 			color(3, 0), texureId(0), isTexMat(false){}
	};

	// ��������3dsģ��
	struct t3DModel
	{
		int numOfObjects;								// 3ds����ĸ���
		int numOfMaterials;								// 3ds���ʵĸ���
		std::vector<my::tMaterial> pMaterials;			// ����3ds����
		std::vector<my::t3DObject> pObject;				// ����3ds����

		my::Vector3			m_maxV;						// ģ�����X,Y,Zֵ
		my::Vector3			m_minV;						// ģ����СX,Y,Zֵ
		my::Vector3			m_vCenter;					// ��Χ������
		float				m_Rais;						// ��Χ�а뾶
// 		t3DModel() :numOfObjects(0), numOfMaterials(0), pMaterials(std::vector<my::tMaterial>()),
// 			pObject()
	};

	struct ScanLine
	{
		my::Vector3 start;
		my::Vector3 end;
		ScanLine(my::Vector3 s, my::Vector3 e) :start(s), end(e){}
	};

	struct T3ds
	{
		T3ds(){
			x = 0;//x���꣨��λ���ף�
			y = 0;//y���꣨��λ���ף�
			z = 0;//z���꣨��λ���ף�
			scaleX = 1.0; //���ű���	
			scaleY = 1.0; //���ű���	
			scaleZ = 1.0; //���ű���	
			d_x = 0;
			d_y = 0;
			d_z = 0;
		}
		float x, y, z;
		float scaleX, scaleY, scaleZ;
		float d_x;      //  ��x��ת�Ƕ� (��λ����) Range: 0 -- 360
		float d_y;      //  ��y��ת�Ƕ� (��λ����) Range: 0 -- 360	
		float d_z;      //  ��z��ת�Ƕ� (��λ����) Range: 0 -- 360
	};

	struct Ray
	{
		my::Vector3 origin;
		my::Vector3 direction;
		Ray():origin(),direction(){}
		Ray(const my::Vector3 &start, const my::Vector3 &d) :origin(start), direction(d){}
	};

	struct POINT3D
	{
		float x;			//�ռ��x����	
		float y;			//�ռ��y����
		float z;			//�ռ��z����

		POINT3D(){}
		POINT3D(float x1, float y1, float z1) :x(x1), y(y1), z(z1){}
	};

	struct MakeOUT
	{
		float x;
		float y;
		float z;
		int show;
		float r;
		float g;
		float b;
		MakeOUT() :x(0),y(0),z(0), show(-1),r(0),g(0),b(0) {}
		MakeOUT(float X, float Y, float Z, int bshow) :x(X), y(Y), z(Z), show(bshow),r(0),g(0),b(0) {}
		void GetShowScan(float X, float Y, float Z, int bshow) { x = X; y = Y; z = Z; show = bshow; }
		void GetShowCamera(float X, float Y, float Z, float R, float G, float B,int bshow) { x = X; y = Y; z = Z; r = R; g = G; b = B; show = bshow; }
	};

	struct SPACEPOINT
	{
		float x;			//�ռ��x����	
		float y;			//�ռ��y����
		float z;			//�ռ��z����
		float fDistance;	//�ռ�õ㵽�����ľ���
		my::Vector3 Lux;

		operator POINT3D(){ return POINT3D(x, y, z); }
		bool operator==(float val)
		{ 
			return (std::fabs(x - val) < 10e-6 
					&& std::fabs(y - val) < 10e-6 
					&& std::fabs(z - val) < 10e-6 
					&& std::fabs(fDistance - val) < 10e-6); 
		}
		SPACEPOINT() :x(0), y(0), z(0), fDistance(0),Lux(0,0,0){}
		SPACEPOINT(float x1, float y1, float z1, float d) :x(x1), y(y1), z(z1), fDistance(d){}
	};

	const float PI = 3.14159265;

	enum POINT_TYPE{ POINT_GROUND = -1, POINT_OBJ_DOWN = 1, POINT_OBJ_UP = 2 };

	struct CAMERA_PARAMETER
	{
		my::Vector3 startP;
		my::Vector3 angle;
		my::Vector3 cur;
		my::Vector3 lightP;
		CAMERA_PARAMETER() :startP(0, 0, 0), angle(startP), cur(startP),lightP(startP){}
		CAMERA_PARAMETER(float startPX, float startPY, float startPZ, float angleX, float angleY, float angleZ,float lightPX,float lightPY,float lightPZ) :
			startP(startPX, startPY, startPZ), angle(angleX, angleY, angleZ), cur(0, 0, 0),lightP(lightPX,lightPY,lightPZ) {}

		CAMERA_PARAMETER operator=(const CAMERA_PARAMETER& cameraParameter)
		{
			startP = cameraParameter.startP;
			angle = cameraParameter.angle;
			cur = cameraParameter.cur;
			lightP = cameraParameter.lightP;

			return *this;
		}
	};

	struct SCAN_PARAMETER 
	{
		my::Vector3 send;
		my::Vector3 angle;
		my::Vector3 end;
		my::Vector3 cur;
		float stepX;
		float stepY;
// 		float length;
// 		float width;
		SCAN_PARAMETER() :send(0, 0, 0), angle(0, 0, 0), end(angle), cur(angle), stepX(0), stepY(0){}
		SCAN_PARAMETER(float sendX, float sendY, float sendZ, float angleX, float angleY, float angleZ, float endX, float endY, float endZ, float stepX1, float stepY1) :
			send(sendX,sendY,sendZ), angle(angleX, angleY, angleZ), end(endX, endY, endZ), cur(0,0,0), stepX(stepX1), stepY(stepY1){}

		SCAN_PARAMETER operator=(const SCAN_PARAMETER& scanParameter)
		{
			send = scanParameter.send;
			angle = scanParameter.angle;
			end = scanParameter.end;
			cur = scanParameter.cur;
			stepX = scanParameter.stepX;
			stepY = scanParameter.stepY;

			return *this;
		}
	};
}