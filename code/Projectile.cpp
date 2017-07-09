#include "Projectile.h"
#include "graphics.h"
#include "time.h"
#include <math.h> // for cos and sin
#include <iostream>


Projectile::Projectile(int locX, int locY, double rotAngle)
	: m_AnchorX(locX)
	, m_AnchorY(locY+15)
	, m_Angle(rotAngle)
{
	// Set laser spawn position
	m_LaserX = m_AnchorX;
	m_LaserY = m_AnchorY - 50;
}


Projectile::~Projectile()
{

}

void Projectile::Update()
{
	// Clear previous projectile line draw from screen
	FillRect( m_LaserX - 10, m_LaserY-50, 21, 51, GetRGB( 0, 0, 0 ) );
	//m_LaserX -= 1;
	m_LaserY -= 1;

	std::cout << m_LaserX << ", " << m_LaserY << std::endl;

	double anchoredX1 = m_LaserX - m_AnchorX;
	double anchoredY1 = m_LaserY - m_AnchorY;
	double anchoredX2 = m_LaserX - m_AnchorX;
	double anchoredY2 = (m_LaserY-50) - m_AnchorY;
	
	double x1 = (anchoredX1 * cos(m_Angle)) - ((anchoredY1) * sin(m_Angle));
	double y1 = (anchoredX1 * sin(m_Angle)) + ((anchoredY1)* cos(m_Angle));
	double x2 = ((anchoredX2) * cos(m_Angle)) - ((anchoredY2) * sin(m_Angle));
	double y2 = ((anchoredX2) * sin(m_Angle)) + ((anchoredY2) * cos(m_Angle));
	DrawLine(m_AnchorX + x1, m_AnchorY + y1, m_AnchorX + x2, m_AnchorY + y2, GetRGB( 255, 255, 255 ));
	//DrawLine( m_LaserX, m_LaserY-20, m_LaserX, m_LaserY+20, GetRGB( 255, 255, 255 ) );
}

bool Projectile::CheckOffscreen(const int screenWidth, const int screenHeight)
{
	return ( m_LaserX < 0 || m_LaserX > screenWidth || m_LaserY < -30 || m_LaserY > screenHeight );
}