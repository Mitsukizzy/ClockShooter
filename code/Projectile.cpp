#include "Projectile.h"
#include "graphics.h"	// for DrawLine
//#include <math.h>		// for cos and sin
#include <iostream>	//REMOVE

#define LENGTH 50


Projectile::Projectile(int locX, int locY, float rotAngle)
{
	// Set laser spawn position in vectors
	m_Head.x = locX;
	m_Head.y = locY + 15;
	m_Tail = m_Head;

	// Set laser direction vector
	m_Dir.x = sin( rotAngle );
	m_Dir.y = -cos( rotAngle );
}


Projectile::~Projectile()
{
	// Clear projectile line draw when destroyed
	DrawLine(m_Tail.x, m_Tail.y, m_Head.x, m_Head.y, GetRGB( 0, 0, 0 ));
}

void Projectile::Update()
{
	// Clear previous projectile line draw from screen
	DrawLine(m_Tail.x, m_Tail.y, m_Head.x, m_Head.y, GetRGB( 0, 0, 0 ));

	// Move spawn upwards
	m_Tail = m_Head;
	m_Head = m_Tail + m_Dir * LENGTH;

	// Draw the projectile
	DrawLine(m_Tail.x, m_Tail.y, m_Head.x, m_Head.y, GetRGB( 255, 255, 0 ));
	//std::cout << m_X1 << ", " << m_Y1 << " | " << m_X2 << " , " << m_Y2  << std::endl;
}

bool Projectile::CheckOffscreen(const int screenWidth, const int screenHeight)
{
	return ( m_Tail.x < 0 || m_Tail.x > screenWidth || m_Tail.y < 0 || m_Tail.y > screenHeight );
}