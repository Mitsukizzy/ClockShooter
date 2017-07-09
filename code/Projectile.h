#pragma once
#ifndef TEST_PROJECTILE_H
#define TEST_PROJECTILE_H

class Projectile
{
public:

	Projectile(int locX, int locY, double rotAngle);
	~Projectile();

	void Update();
	bool CheckOffscreen(const int screenWidth, const int screenHeight);

private:
	
	int m_AnchorX;
	int m_AnchorY;
	int	m_LaserX;
	int	m_LaserY;
	float m_Angle;

};

#endif // #ifndef TEST_PROJECTILE_H
