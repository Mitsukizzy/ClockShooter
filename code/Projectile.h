#pragma once
#ifndef TEST_PROJECTILE_H
#define TEST_PROJECTILE_H

#include "Utils.h"

class Projectile
{
public:

	Projectile(int locX, int locY, float rotAngle);
	~Projectile();

	void Update();
	bool CheckOffscreen(const int screenWidth, const int screenHeight);
	Vector2 GetHead() { return m_Head; };
	Vector2 GetTail() { return m_Tail; };

private:

	Vector2 m_Dir;
	Vector2 m_Head;
	Vector2 m_Tail;
};

#endif // #ifndef TEST_PROJECTILE_H