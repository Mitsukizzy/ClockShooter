#pragma once
#ifndef TEST_CLOCK_H
#define TEST_CLOCK_H

class Clock
{
public:

	Clock(int screenWidth, int screenHeight);
	~Clock();

	void Update();

	void DrawRing();
	void DrawHour();
	void DrawMinute();
	void CheckCollision();

private:

	const int m_ScreenWidth;
	const int m_ScreenHeight;

	int m_LocX;
	int m_LocY;
	int m_Speed;

	bool m_IsSmall;
};

#endif // #ifndef TEST_CLOCK_H
