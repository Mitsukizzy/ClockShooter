#pragma once
#ifndef TEST_CLOCK_H
#define TEST_CLOCK_H

#include "Utils.h"

class Clock
{
public:

	Clock(int screenWidth, int screenHeight);
	~Clock();

	void Update();

	void DrawRing();
	void DrawHour(int hour);
	void DrawMinute(int min);
	void CheckCollision();

private:

	const int m_ScreenWidth;
	const int m_ScreenHeight;

	int m_LocX;
	int m_LocY;
	float m_Speed;

	Vector2 m_Pos;		// Center point of the clock
	Vector2 m_Dir;		// Direction the clock is moving

	bool m_IsSmall;
};

#endif // #ifndef TEST_CLOCK_H
