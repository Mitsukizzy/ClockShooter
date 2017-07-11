#pragma once
#ifndef TEST_VECTOR2_H
#define TEST_VECTOR2_H

#include <cmath>

/*
	My own quick Vector2 implementation.
	Only added functions needed for the test.
*/

class Vector2
{
public:
	float x;
	float y;

	// Default constructor
	Vector2():x(0.0f), y(0.0f)
	{}

	Vector2( float newX, float newY ):x(newX), y(newY)
	{}

	float LengthSq()
	{
		return ( x * x + y * y );
	}

	float Length()
	{
		return sqrtf( LengthSq() );
	}

	void Normalize()
	{
		float len = Length();
		x /= len;
		y /= len;
	}

	float Dot(const Vector2 b)
	{
		return ( x * b.x + y * b.y );
	}

	// OPERATOR OVERRIDES
	friend Vector2 operator&=( const Vector2 a, const Vector2 b )
	{
		return Vector2( b.x, b.y );
	}

	friend Vector2 operator+( const Vector2 a, const Vector2 b )
	{
		return Vector2( a.x + b.x, a.y + b.y );
	}

	friend Vector2 operator-( const Vector2 a, const Vector2 b )
	{
		return Vector2( a.x - b.x, a.y - b.y);
	}

	friend Vector2 operator*( const Vector2 a, const float b )
	{
		return Vector2(a.x * b, a.y * b);
	}

}; 

#endif // #ifndef TEST_VECTOR2_H
#pragma once
