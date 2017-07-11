#pragma once
#ifndef TEST_CLOCK_H
#define TEST_CLOCK_H

#include "Vector2.h"

class Clock
{
public:
	enum TimeType { hour, min, sec };

	Clock(int screenWidth, int screenHeight, int livesLeft);
	~Clock();

	void Update();
	void FindNewSpawnPosition();
	void ClearDraw();
	void DrawSquare();
	void DrawHand(int time, TimeType type);
	void CustomizeHands(TimeType type, float &length, float &denom, unsigned int &color);
	void ReverseDirection();
	void CheckWallCollision();
	bool CheckClockCollision(Vector2 bPos, float bRadius);
	bool CheckHitCollision(Vector2 head, Vector2 tail);

	Vector2 GetPosition() { return m_Pos; }
	int GetLives()		  { return m_Lives; }
	float GetRadius()	  { return m_Radius; }

private:

	int m_ScreenWidth;
	int m_ScreenHeight;

	Vector2 m_Pos;		// Center point of the clock
	Vector2 m_Dir;		// Direction the clock is moving

	int m_Lives;
	float m_Speed;
	float m_Radius;
};

#endif // #ifndef TEST_CLOCK_H
