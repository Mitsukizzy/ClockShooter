#include "Projectile.h"
#include "graphics.h"	// for DrawLine
#include <math.h>		// for cos and sin
#include <iostream>	//REMOVE

#define LENGTH 50


Projectile::Projectile(int locX, int locY, float rotAngle)
	: m_AnchorX(locX)
	, m_AnchorY(locY+15)
	, m_Angle(rotAngle)
{
	// Set laser spawn position
	m_SpawnY = m_AnchorY - 16;
}


Projectile::~Projectile()
{
	// Clear projectile line draw when destroyed
	DrawLine(m_X1, m_Y1, m_X2, m_Y2, GetRGB( 0, 0, 0 ));
}

void Projectile::Update()
{
	// Clear previous projectile line draw from screen
	DrawLine(m_X1, m_Y1, m_X2, m_Y2, GetRGB( 0, 0, 0 ));

	// Move spawn upwards
	m_SpawnY -= 0.05f;

	int anchoredX = 0;
	int anchoredY1 = m_SpawnY - m_AnchorY;
	int anchoredY2 = (m_SpawnY - LENGTH) - m_AnchorY;

	// Precalculate the sin and cos of the angle
	float sinAngle = sin(m_Angle);
	float cosAngle = cos(m_Angle);
	
	// Rotate each point and add back the corresponding anchor
	m_X1 = (anchoredX * cosAngle) - (anchoredY1 * sinAngle) + m_AnchorX;
	m_Y1 = (anchoredX * sinAngle) + (anchoredY1 * cosAngle) + m_AnchorY;
	m_X2 = (anchoredX * cosAngle) - (anchoredY2 * sinAngle) + m_AnchorX;
	m_Y2 = (anchoredX * sinAngle) + (anchoredY2 * cosAngle) + m_AnchorY;

	// Draw the projectile
	DrawLine(m_X1, m_Y1, m_X2, m_Y2, GetRGB( 255, 255, 255 ));
	//std::cout << m_X1 << ", " << m_Y1 << " | " << m_X2 << " , " << m_Y2  << std::endl;
}

bool Projectile::CheckOffscreen(const int screenWidth, const int screenHeight)
{
	return ( m_X2 < 0 || m_X1 > screenWidth || m_Y2 < 0 || m_Y1 > screenHeight );
}