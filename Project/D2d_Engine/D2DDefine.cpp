#include "pch.h"
#include <math.h>

#pragma region Vector2

Vector2 Vector2::normalized()
{
	float length = magnitude();
	if (length <= 0)
	{
		return Vector2::zero();
	}
	return Vector2(x / length, y / length);
}
float Vector2::magnitude()
{
	return sqrt((x * x) + (y * y));
}
float Vector2::sqrMagnitude()
{
	return ((x * x) + (y * y));
}

#pragma region Vec2_Vec2

void Vector2::operator= (const Vector2& orther)
{
	x = orther.x;
	y = orther.y;
}

Vector2	Vector2::operator+	(const Vector2& orther)
{
	return Vector2(x + orther.x, y + orther.y);
}
Vector2	Vector2::operator-	(const Vector2& orther)
{
	return Vector2(x - orther.x, y - orther.y);
}

Vector2 Vector2::operator*	(const Vector2& orther)
{
	return Vector2(x * orther.x, y * orther.y);
}
Vector2 Vector2::operator/	(const Vector2& orther)
{
	return Vector2(x / orther.x, y / orther.y);
}

void	Vector2::operator-=	(const Vector2& orther)
{
	x -= orther.x;
	y -= orther.y;
}
void	Vector2::operator+=	(const Vector2& orther)
{
	x += orther.x;
	y += orther.y;
}

bool	Vector2::operator==	(const Vector2& orther)
{
	return (x == orther.x) && (y == orther.y);
}
bool	Vector2::operator!=	(const Vector2& orther)
{
	return !(*this == orther);
}

#pragma endregion

#pragma region Vec2_Scala

Vector2	Vector2::operator*	(const float& scala)
{
	return Vector2(x * scala, y * scala);
}
Vector2	Vector2::operator/	(const float& scala)
{
	return Vector2(x / scala, y / scala);
}

void	Vector2::operator*=	(const float& scala)
{
	x *= scala;
	y *= scala;
}
void	Vector2::operator/=	(const float& scala)
{
	x /= scala;
	y /= scala;
}

#pragma endregion

#pragma region Vec2_Vec3

void Vector2::operator= (const Vector3& orther)
{
	x = orther.x;
	y = orther.y;
}

Vector2	Vector2::operator+	(const Vector3& orther)
{
	return Vector2(x + orther.x, y + orther.y);
}
Vector2	Vector2::operator-	(const Vector3& orther)
{
	return Vector2(x - orther.x, y - orther.y);
}

Vector2 Vector2::operator*	(const Vector3& orther)
{
	return Vector2(x * orther.x, y * orther.y);
}
Vector2 Vector2::operator/	(const Vector3& orther)
{
	return Vector2(x / orther.x, y / orther.y);
}

void	Vector2::operator-=	(const Vector3& orther)
{
	x -= orther.x;
	y -= orther.y;
}
void	Vector2::operator+=	(const Vector3& orther)
{
	x += orther.x;
	y += orther.y;
}

#pragma endregion
#pragma endregion

#pragma region Vector3

Vector3 Vector3::normalized()
{
	float length = magnitude();
	return Vector3(x / length, y / length, z / length);
}
float Vector3::magnitude()
{
	return sqrt((x * x) + (y * y) + (z * z));
}
float Vector3::sqrMagnitude()
{
	return (x * x) + (y * y) + (z * z);
}

//Vector3_Vector3
float Vector3::operator[](int idx)
{
	try
	{
		if (idx < 0 || idx>2) { throw false; }
		switch (idx)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}
	catch (bool e)
	{
		//오류 발생
		//없는 IDX 참조
	}
	return true;
}
void Vector3::operator= (const Vector3& orther)
{
	x = orther.x;
	y = orther.y;
	z = orther.z;
}

Vector3 Vector3::operator+ (const Vector3& orther)
{
	return Vector3(x + orther.x, y + orther.y, z + orther.z);
}
Vector3 Vector3::operator- (const Vector3& orther)
{
	return Vector3(x - orther.x, y - orther.y, z - orther.z);
}
Vector3 Vector3::operator* (const Vector3& orther)
{
	return Vector3(x * orther.x, y * orther.y, z * orther.z);
}
Vector3 Vector3::operator/ (const Vector3& orther)
{
	return Vector3(x / orther.x, y / orther.y, z / orther.z);
}

void Vector3::operator+= (const Vector3& orther)
{
	x += orther.x;
	y += orther.y;
	z += orther.z;
}
void Vector3::operator-= (const Vector3& orther)
{
	x -= orther.x;
	y -= orther.y;
	z -= orther.z;
}

bool Vector3::operator== (const Vector3& orther)
{
	return (x == orther.x) && (y == orther.y) && (z == orther.z);
}
bool Vector3::operator!= (const Vector3& orther)
{
	return !(*this == orther);
}

//Vector3_Scala

Vector3 Vector3::operator* (const float& scala)
{
	return Vector3(x * scala, y * scala, z * scala);
}
Vector3 Vector3::operator/ (const float& scala)
{
	return Vector3(x / scala, y / scala, z / scala);
}
void Vector3::operator*= (const float& scala)
{
	x *= scala;
	y *= scala;
}
void Vector3::operator/= (const float& scala)
{
	x /= scala;
	y /= scala;
}

#pragma region Vec3_Vec2

void Vector3::operator= (const Vector2& orther)
{
	x = orther.x;
	y = orther.y;
}

Vector3 Vector3::operator+ (const Vector2& orther)
{
	return Vector3(x + orther.x, y + orther.y, z);
}
Vector3 Vector3::operator- (const Vector2& orther)
{
	return Vector3(x - orther.x, y - orther.y, z);
}
Vector3 Vector3::operator* (const Vector2& orther)
{
	return Vector3(x * orther.x, y * orther.y, z);
}
Vector3 Vector3::operator/ (const Vector2& orther)
{
	return Vector3(x / orther.x, y / orther.y, z);
}

void Vector3::operator+= (const Vector2& orther)
{
	x += orther.x;
	y += orther.y;
}
void Vector3::operator-= (const Vector2& orther)
{
	x -= orther.x;
	y -= orther.y;
}

#pragma endregion

#pragma endregion

#pragma region GameObject

#pragma endregion


int Sprite::GetWidth()
{
	return SrcRect.right - SrcRect.left;
}

int Sprite::GetHeight()
{
	return SrcRect.bottom - SrcRect.top;
}


D2D1_MATRIX_3X2_F Transform::CreateTransMatrix()
{
	D2D1_MATRIX_3X2_F _translateMatrix;

	_translateMatrix._11 = 1.0f;
	_translateMatrix._12 = 0.0f;

	_translateMatrix._21 = 0.0f;
	_translateMatrix._22 = 1.0f;


	_translateMatrix._31 = -mPosition.x;
	_translateMatrix._32 = -mPosition.y;
	
	return _translateMatrix;
}
D2D1_MATRIX_3X2_F Transform::CreateRotationMatrix()
{
	float _radianAngle = DEGREETORADIAN(mRotationAngle);

	D2D1_MATRIX_3X2_F _rotationMatrix;

	_rotationMatrix._11 = cosf(_radianAngle);
	_rotationMatrix._12 = sinf(_radianAngle);
	_rotationMatrix._21 = -sinf(_radianAngle);
	_rotationMatrix._22 = cosf(_radianAngle);
	_rotationMatrix._31 = 0.0f;
	_rotationMatrix._32 = 0.0f;

	return _rotationMatrix;

}


Vector3 GameObject::GetPosition()
{
	return ptransform->mPosition;
}

Vector3 GameObject::GetRotation()
{
	return ptransform->mRotation;
}

Vector3 GameObject::GetScale()
{
	return ptransform->mScale;
}

void GameObject::SetPosition(Vector2 Pos)
{
	ptransform->mPosition.x = Pos.x;
	ptransform->mPosition.y = Pos.y;
}

void GameObject::SetPosition(Vector3 Pos)
{
	ptransform->mPosition.x = Pos.x;
	ptransform->mPosition.y = Pos.y;
	ptransform->mPosition.z = Pos.z;
}

//void GameObject::SetPosition(float x, float y)
//{
//	ptransform->mPosition.x = x;
//	ptransform->mPosition.y = y;
//}


void GameObject::SetRotation(Vector2 Pos)
{
	ptransform->mRotation.x = Pos.x;
	ptransform->mRotation.y = Pos.y;
}

void GameObject::SetRotation(Vector3 Pos)
{
	ptransform->mRotation.x = Pos.x;
	ptransform->mRotation.y = Pos.y; 
	ptransform->mRotation.z = Pos.z;
}

void GameObject::SetScale(Vector2 Pos)
{
	ptransform->mScale.x = Pos.x;
	ptransform->mScale.y = Pos.y;
}

void GameObject::SetScale(Vector3 Pos)
{
	ptransform->mScale.x = Pos.x;
	ptransform->mScale.y = Pos.y;
	ptransform->mScale.z = Pos.z;
}

void GameObject::Move(Vector2 Pos)
{
	Vector2 _pos(GetPosition().x, GetPosition().y);
	SetPosition(Pos+ _pos);
}
