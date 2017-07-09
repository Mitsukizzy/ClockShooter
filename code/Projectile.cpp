#include "Projectile.h"
#include "graphics.h"
#include "time.h"
#include <math.h> // for cos and sin
#include <iostream>


Projectile::Projectile(int locX, int locY, float rotAngle)
	: m_LaserX(locX)
	, m_LaserY(locY-10)
	, m_Angle(rotAngle)
{
}


Projectile::~Projectile()
{

}

void Projectile::Update()
{
	// Clear previous projectile line draw from screen
	FillRect( m_LaserX - 10, m_LaserY - 15, 21, 31, GetRGB( 0, 0, 0 ) );
	//m_LaserX -= 1;
	m_LaserY -= 10;

	std::cout << m_LaserX << ", " << m_LaserY << std::endl;
	DrawLine( m_LaserX, m_LaserY, m_LaserX, m_LaserY - 30, GetRGB( 255, 255, 255 ) );
}