#pragma once
#ifndef TEST_PROJECTILE_H
#define TEST_PROJECTILE_H

class Projectile
{
public:

	typedef unsigned int T_PressedKey;

	Projectile(int locX, int locY, float rotAngle);
	~Projectile();

	void Update();

private:

	//const int	m_ScreenWidth;
	//const int	m_ScreenHeight;

	// Members for sample tick
	int			m_LaserX;
	int			m_LaserY;

	float m_Angle;

};

#endif // #ifndef TEST_PROJECTILE_H
