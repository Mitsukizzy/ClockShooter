#pragma once
#ifndef TEST_PROJECTILE_H
#define TEST_PROJECTILE_H

class Projectile
{
public:

	Projectile(int locX, int locY, float rotAngle);
	~Projectile();

	void Update();
	bool CheckOffscreen(const int screenWidth, const int screenHeight);

private:
	
	int m_AnchorX;
	int m_AnchorY;
	float m_Angle;

	float m_SpawnY;

	float m_X1;
	float m_Y1;
	float m_X2;
	float m_Y2;
};

#endif // #ifndef TEST_PROJECTILE_H
