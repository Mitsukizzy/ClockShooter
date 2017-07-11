#pragma once
#ifndef TEST_CLOCK_H
#define TEST_CLOCK_H

#include "Vector2.h"

class Clock
{
public:
	enum TimeType { hour, min, sec };

	Clock(int screenWidth, int screenHeight, bool isSmall);
	~Clock();

	void Update();
	void ClearDraw();
	void DrawSquare();
	void DrawHand(int time, TimeType type);
	void CustomizeHands(TimeType type, float &length, float &denom, unsigned int &color);

	void CheckWallCollision();
	bool CheckHitCollision(Vector2 head, Vector2 tail);
	bool GetIsAlive() { return m_isAlive; }
	bool GetIsSmall() { return m_isSmall; }

private:

	int m_ScreenWidth;
	int m_ScreenHeight;


	Vector2 m_Pos;		// Center point of the clock
	Vector2 m_Dir;		// Direction the clock is moving

	float m_Speed;
	float m_Radius;
	bool m_isAlive;
	bool m_isSmall;
};

#endif // #ifndef TEST_CLOCK_H
