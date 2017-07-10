#pragma once
#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <cmath>

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

	// Set all, useful after instantiation
	void Set( float newX, float newY )
	{
		x = newX;
		y = newY;
	}

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

	Vector2 Normalize( const Vector2 v )
	{
		Vector2 vNorm = v;
		vNorm.Normalize();
		return vNorm;
	}


	float Dot( const Vector2 a, const Vector2 b )
	{
		return ( a.x * b.x + a.y * b.y );
	}

	// OPERATOR OVERRIDES
	// friend keyword allows non-member functions to access private and protected memobers of a class
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

	friend Vector2 operator*( const Vector2 a, const Vector2 b )
	{
		return Vector2( a.x * b.x, a.y * b.y);
	}

	friend Vector2 operator*( const Vector2 a, const int b )
	{
		return Vector2(a.x * b, a.y * b);
	}

}; // End Vector2 class

#endif // #ifndef TEST_UTILS_H
#pragma once
