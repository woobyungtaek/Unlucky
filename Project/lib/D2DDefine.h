#pragma once
#include <atlstr.h>

#pragma region VK 키
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47 
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A
#pragma endregion

#pragma region Transform

#define PI 3.14f
#define DEGREETORADIAN(d)	(d * PI / 180.0f)

#pragma endregion

class Vector3;

///외부 사용 Class
#pragma region Vector2

class Vector2
{
public:
	static  float Dot(Vector2& a, Vector2& b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}
	static  float Distance(Vector2& a, Vector2& b)
	{
		return (a - b).magnitude();
	}
	static  Vector2 Lerp(Vector2& a, Vector2& b, float t)
	{
		return (a * (1 - t)) + (b * t);
	}

	static  Vector2 one()
	{
		return Vector2(1, 1);
	}
	static  Vector2 zero()
	{
		return Vector2(0, 0);
	}
	static  Vector2 left()
	{
		return Vector2(-1, 0);
	}
	static  Vector2 right()
	{
		return Vector2(1, 0);
	}
	static  Vector2 up()
	{
		//GDI 기준 -
		return Vector2(0, -1);
	}
	static  Vector2 down()
	{
		//GDI 기준 +
		return Vector2(0, 1);
	}

public:
	Vector2() : x(0), y(0) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	~Vector2() {}

public:
	float x, y;

public:
	Vector2 normalized();
	float magnitude();
	float sqrMagnitude();

	//Vector2_Vector2
	void		operator= (const Vector2& orther);

	Vector2	operator+	(const Vector2& orther);
	Vector2	operator-	(const Vector2& orther);

	Vector2	operator*	(const Vector2& orther);
	Vector2	operator/	(const Vector2& orther);

	void		operator-=	(const Vector2& orther);
	void		operator+=	(const Vector2& orther);

	bool		operator==	(const Vector2& orther);
	bool		operator!=	(const Vector2& orther);

	//Vector2_Scala

	Vector2	operator*	(const float& scala);
	Vector2	operator/	(const float& scala);

	void		operator*=	(const float& scala);
	void		operator/=	(const float& scala);

	//Vector2_Vector3

	void		operator= (const Vector3& orther);

	Vector2	operator+	(const Vector3& orther);
	Vector2	operator-	(const Vector3& orther);

	Vector2	operator*	(const Vector3& orther);
	Vector2	operator/	(const Vector3& orther);

	void		operator-=	(const Vector3& orther);
	void		operator+=	(const Vector3& orther);

};
#pragma endregion

#pragma region Vector3
class Vector3
{
public:
	//Static 따로 Extern이 필요하다. ???
	static  float Dot(Vector3& a, Vector3& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}
	static  float Distance(Vector3& a, Vector3& b)
	{
		return (a - b).magnitude();
	}
	static  Vector3 Cross(Vector3& a, Vector3& b)
	{
		//i,  j, k
		//ax,ay,az
		//bx,by,bz
		float i = (a.y * b.z) - (a.z * b.y);
		float j = (a.x * b.z) - (a.z * b.x);
		float k = (a.x * b.y) - (a.y * b.x);
		return Vector3(i, -j, k);
	}
	static  Vector3 Lerp(Vector3& a, Vector3& b, float t)
	{
		return (a * (1 - t)) + (b * t);
	}

	static Vector3 one()
	{
		return Vector3(1, 1, 1);
	}
	static Vector3 zero()
	{
		return Vector3(0, 0, 0);
	}

	static Vector3 front()
	{
		//깊이 +, 시선 방향, 눈 방향
		return Vector3(0, 0, 1);
	}
	static Vector3 back()
	{
		//깊이 - 시선 반대 방향, 뒤통수 방향
		return Vector3(0, 0, -1);
	}
	static Vector3 left()
	{
		return Vector3(-1, 0, 0);
	}
	static Vector3 right()
	{
		return Vector3(1, 0, 0);
	}
	static Vector3 up()
	{
		//GDI 기준 -
		return Vector3(0, -1, 0);
	}
	static Vector3 down()
	{
		//GDI 기준 +
		return Vector3(0, 1, 0);
	}

public:
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3(float _x, float _y) : x(_x), y(_y), z(0) {}
	~Vector3() {}

public:
	float x, y, z;

public:
	Vector3 normalized();
	float magnitude();
	float sqrMagnitude();

	//Vector3_Vector3
	float operator[] (int idx);
	void operator= (const Vector3& orther);

	Vector3 operator+ (const Vector3& orther);
	Vector3 operator- (const Vector3& orther);
	Vector3 operator* (const Vector3& orther);
	Vector3 operator/ (const Vector3& orther);

	void operator+= (const Vector3& orther);
	void operator-= (const Vector3& orther);

	bool operator== (const Vector3& orther);
	bool operator!= (const Vector3& orther);

	//Vector3_Scala

	Vector3 operator* (const float& scala);
	Vector3 operator/ (const float& scala);
	void operator*= (const float& scala);
	void operator/= (const float& scala);

	//Vector3_Vector2

	void operator= (const Vector2& orther);

	Vector3 operator+ (const Vector2& orther);
	Vector3 operator- (const Vector2& orther);
	Vector3 operator* (const Vector2& orther);
	Vector3 operator/ (const Vector2& orther);

	void operator+= (const Vector2& orther);
	void operator-= (const Vector2& orther);
};
#pragma endregion
#pragma region T

class Transform
{
public:
	Vector3 mPosition;
	Vector3 mRotation;
	Vector3 mScale;
	
	float mRotationAngle;
public:
	Transform()
	{
		mPosition = Vector3::zero();
		mRotation = Vector3::zero();
		mScale = Vector3::zero();
		mRotationAngle = 0.0f;
	}
	~Transform()
	{
	};
	//이동행렬 만들기
	D2D1_MATRIX_3X2_F CreateTransMatrix();

	// 회전행렬 만들기
	D2D1_MATRIX_3X2_F CreateRotationMatrix();

	// 디그리각도(0 ~ 360도)만큼 회전 시키기
	void SetRotationAngle(float degreeAngle)
	{
		mRotationAngle += degreeAngle;

		if (mRotationAngle >= 360.0f)
			mRotationAngle = 0.0f;
	}
	// 디그리각도 값 읽기용으로 가져오기
	float GetRotationAngle() { return mRotationAngle; }
};
#pragma endregion

class Collider
{
public:
	Transform* ObjTransform;

public:
	Collider(Transform* objtransform)
	{
		ObjTransform = objtransform;
	};
	~Collider()
	{

	};
};

class GameObject
{
public:
	bool IsActive;
	
	Transform* ptransform;
    Collider* pcollider;


public:
	GameObject()
	{
		ptransform = new Transform();
		pcollider = new Collider(ptransform);
	}

	~GameObject()
	{

	};

public:
	//오브젝트의 트랜스폼을 조정한다.
	Vector3 GetPosition();
	Vector3 GetRotation();
	Vector3 GetScale();


	void SetPosition(Vector2 Pos);
	void SetPosition(Vector3 Pos);

	void SetRotation(Vector2 Pos);
	void SetRotation(Vector3 Pos);

	void SetScale(Vector2 Pos);	 
	void SetScale(Vector3 Pos);

	void Move(Vector2 Pos);

	virtual void Draw() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
};



//스프라이트 정보
class Sprite
{
public:
	Sprite()
	:FileName(), Motion(nullptr), Frame(NULL), SrcRect(), Pivot(), Delay(NULL)
	{};
	Sprite(CString fileName, LPCWSTR motion, int order, D2D1_RECT_F srcRect, POINT pivot, int delay) :
		FileName(fileName), Motion(motion), Frame(order), SrcRect(srcRect), Pivot(pivot), Delay(delay) {};
	~Sprite() {};

public:
	CString	FileName;
	LPCWSTR Motion;
	int		FrameCount;
	int		Frame;
	POINT	Pivot;
	int		Delay;
	D2D1_RECT_F SrcRect;

	int width;
	int height;
	//std::vector<D2D1_RECT_F> ColliderVec;

public:
	int GetWidth();
	int GetHeight();
};

//class SpriteRenderer
//{
//public:
//	SpriteRenderer();
//	~SpriteRenderer();
//
//private:
//	Sprite* mSpriteData;
//
//public:
//	void SetSpriteData(Sprite* data);
//	void Draw();
//};
//
//class Animator
//{
//public:
//	Animator();
//	~Animator();
//private:
//	SpriteRenderer* mRenderer;
//	int CurrentFrame;
//
//public:
//	void Update();
//
//	void Play();
//	void Pause();
//	void Stop();
//	void Resume();
//};