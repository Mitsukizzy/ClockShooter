#include "Projectile.h"
#include "graphics.h"
#include "time.h"
#include <math.h> // for cos and sin


Projectile::Projectile(int locX, int locY, float rotAngle)
	: m_LaserX(locX)
	, m_LaserY(locY)
	, m_Angle(rotAngle)
{
}


Projectile::~Projectile()
{

}

void Projectile::Update()
{
	// Clear previous projectile line draw from screen
	FillRect(m_LaserX-10, m_LaserY,		21,		-31, GetRGB(0, 0, 0));

	m_LaserY -= 100;
	m_LaserX -= 10;

	DrawLine(m_LaserX,    m_LaserY,    m_LaserX, m_LaserY-30, GetRGB(255,   0,   0));
}