#include "C_Application.h"
#include "graphics.h"
#include "time.h"
#include <math.h> // for cos and sin
#include <vector>
#include <iostream>

static const float k_PI = 3.1415926536f;

C_Application::C_Application(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
	, m_CannonX(m_ScreenWidth/2)
	, m_CannonY(m_ScreenHeight/2)
{
	// Position the cannon in the bottom middle of the window
	m_CannonX = m_ScreenWidth * 0.5f;
	m_CannonY = m_ScreenHeight * 0.9f;

	// Angle of rotation ranging from -90 to 90 with 0 pointing straight upwards
	m_RotAngle = 0;

	// Init two clocks
	SpawnClocks();
	
	// FOR DEBUG
	AllocConsole();
	freopen("CONIN$", "r",stdin);
	freopen("CONOUT$", "w",stdout);
	freopen("CONOUT$", "w",stderr);
}


C_Application::~C_Application()
{
	// Erase all projectiles and clocks
}


void C_Application::Tick(T_PressedKey pressedKeys)
{
	// Sample tick

	// Clear screen on cannon position
	FillRect(m_CannonX-20, m_CannonY-5, 40, 50, GetRGB(0, 0, 0));

	// Key processing
	if(pressedKeys & s_KeyLeft)
	{
		//m_CannonX = max(0, m_CannonX-4);
		m_RotAngle = max(-90.0f, m_RotAngle - m_RotSpeed);
	}

	if(pressedKeys & s_KeyRight)
	{
		//m_CannonX = min(m_ScreenWidth, m_CannonX+4);
		m_RotAngle = min(90.0f, m_RotAngle + m_RotSpeed);
	}

	if(pressedKeys & s_KeyUp)
	{
		m_CannonY = max(0, m_CannonY-4);
	}

	if(pressedKeys & s_KeyDown)
	{
		m_CannonY = min(m_ScreenHeight, m_CannonY+4);
	}

	//std::cout << "DEGRot: " << m_RotAngle << std::endl;
	float rotInRad = (float) m_RotAngle * k_PI / 180.0;

	if(pressedKeys & s_KeySpace)
	{
		// Fire projectile
		Projectile p = Projectile(m_CannonX, m_CannonY, rotInRad);
		projectiles.push_back(p);		
		//std::cout << "PROJECTILE COUNT: " << projectiles.size() << std::endl;
	}


	// Draw cannon
	DrawCannonLine( m_CannonX, m_CannonY, m_CannonX-10, m_CannonY+30, rotInRad, GetRGB( 255, 0, 0 ) );
	DrawCannonLine( m_CannonX, m_CannonY, m_CannonX+10, m_CannonY+30, rotInRad, GetRGB( 0, 255, 0 ) );
	DrawCannonLine( m_CannonX-10, m_CannonY+30, m_CannonX+10, m_CannonY+30, rotInRad, GetRGB( 0, 0, 255 ) );

	Update();
}


void C_Application::Update()
{
	// Update projectiles
	auto p = projectiles.begin();
	while(p != projectiles.end())
	{
		bool hit, offScreen;
		(*p).Update();
		
		// Check if projectile hit a clock
		for(auto &clock : clocks)
		{
			hit = clock.CheckHitCollision((*p).GetHead(), (*p).GetTail());
		}

		offScreen = (*p).CheckOffscreen(m_ScreenWidth, m_ScreenWidth);

		// Destroy projectile if hit or off screen
		if(hit || offScreen) 
		{
			p = projectiles.erase(p);
			continue;
		}
		p++;
	}

	auto c = clocks.begin();
	while (c != clocks.end())
	{
		// Remove any dead clocks
		if(!(*c).GetIsAlive())
		{
			c = clocks.erase(c);
			continue;
		}

		// Update alive clocks
		(*c).Update();
		c++;
	}

	// Create two new clocks if none exist
	if(clocks.size() == 0)
	{
		SpawnClocks();
	}
}

void C_Application::SpawnClocks()
{
	Clock c1 = Clock(m_ScreenWidth, m_ScreenHeight);
	Clock c2 = Clock(m_ScreenWidth, m_ScreenHeight);
	clocks.push_back(c1);
	clocks.push_back(c2);		
}

void C_Application::DrawCannonLine(int inX1, int inY1, int inX2, int inY2, double rot, unsigned int color)
{
	float anchorX = m_CannonX;
	float anchorY = m_CannonY+15;

	float anchoredX1 = inX1 - anchorX;
	float anchoredY1 = inY1 - anchorY;
	float anchoredX2 = inX2 - anchorX;
	float anchoredY2 = inY2 - anchorY;

	float x1 = (anchoredX1 * cos(rot)) - (anchoredY1 * sin(rot));
	float y1 = (anchoredX1 * sin(rot)) + (anchoredY1 * cos(rot));
	float x2 = ((anchoredX2) * cos(rot)) - ((anchoredY2) * sin(rot));
	float y2 = ((anchoredX2) * sin(rot)) + ((anchoredY2) * cos(rot));
	DrawLine(anchorX + x1, anchorY + y1, anchorX + x2, anchorY + y2, color);
}