#pragma once
#ifndef TEST_PROJECTILE_H
#define TEST_PROJECTILE_H

class Projectile
{
public:

	Projectile(int locX, int locY, float rotAngle);
	~Projectile();

	void Update();
	int	m_LaserX;
	int	m_LaserY;

private:

	float m_Angle;

};

#endif // #ifndef TEST_PROJECTILE_H
