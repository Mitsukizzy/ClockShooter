#include "Projectile.h"
#include "graphics.h"	// for DrawLine

#define LENGTH 5

Projectile::Projectile(int locX, int locY, float rotAngle)
{
	// Set laser spawn position in vectors
	m_Head.x = locX;
	m_Head.y = locY + 30;
	m_Tail = m_Head;

	// Set laser direction vector
	m_Dir.x = sin(rotAngle);
	m_Dir.y = -cos(rotAngle);

	// Have the projectile come out at the head of the cannon
	m_Head = m_Head + m_Dir * 30;
}

Projectile::~Projectile(){}

void Projectile::Update()
{
	ClearDraw();

	// Move spawn upwards
	m_Tail = m_Head;
	m_Head = m_Tail + m_Dir * LENGTH;

	// Draw the projectile
	DrawLine(m_Tail.x, m_Tail.y, m_Head.x, m_Head.y, GetRGB(255, 255, 255));
}

void Projectile::ClearDraw()
{
	// Clear previous projectile line draw from screen
	DrawLine(m_Tail.x, m_Tail.y, m_Head.x, m_Head.y, GetRGB( 0, 0, 0 ));
}

bool Projectile::CheckOffscreen(const int screenWidth, const int screenHeight)
{
	return (m_Tail.x < 0 || m_Tail.x > screenWidth || m_Tail.y < 0 || m_Tail.y > screenHeight);
}