#include "C_Application.h"
#include "graphics.h"
#include "time.h"
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
	m_RotSpeed = 1.5f;

	// Cooldown time between projectile firing
	m_Cooldown = 0.1f;

	// Set random seed
	std::srand(std::time(NULL));

	// Init two big clocks
	SpawnClocks(false);
	
	// FOR DEBUG
	AllocConsole();
	freopen("CONIN$", "r",stdin);
	freopen("CONOUT$", "w",stdout);
	freopen("CONOUT$", "w",stderr);

	m_CoolStart = std::clock();
}


C_Application::~C_Application()
{
}

void C_Application::Tick(T_PressedKey pressedKeys)
{
	// Clear screen on cannon position
	FillRect(m_CannonX-20, m_CannonY-5, 40, 50, GetRGB(0, 0, 0));

	// Key processing
	if(pressedKeys & s_KeyLeft)
	{
		m_RotAngle = max(-90.0f, m_RotAngle - m_RotSpeed);
	}

	if(pressedKeys & s_KeyRight)
	{
		m_RotAngle = min(90.0f, m_RotAngle + m_RotSpeed);
	}

	float rotInRad = (float) m_RotAngle * k_PI / 180.0;
	double duration = (std::clock() - m_CoolStart) / (double) CLOCKS_PER_SEC;

	if((pressedKeys & s_KeySpace) && (duration > m_Cooldown))
	{
		// Fire projectile
		Projectile p = Projectile(m_CannonX, m_CannonY, rotInRad);
		projectiles.push_back(p);

		// Reset cooldown timer
		m_CoolStart = std::clock();
	}

	// Draw cannon
	DrawCannonLine( m_CannonX, m_CannonY, m_CannonX-10, m_CannonY+30, rotInRad, GetRGB( 255, 0, 0 ) );
	DrawCannonLine( m_CannonX, m_CannonY, m_CannonX+10, m_CannonY+30, rotInRad, GetRGB( 0, 255, 0 ) );
	DrawCannonLine( m_CannonX-10, m_CannonY+30, m_CannonX+10, m_CannonY+30, rotInRad, GetRGB( 0, 0, 255 ) );

	Update();
}

void C_Application::Update()
{
	int lgClockHit = 0;

	auto p = projectiles.begin();
	while(p != projectiles.end())
	{
		bool hit, offScreen;

		// Update projectiles
		(*p).Update();
		
		// Check if projectile hit a clock
		for(auto &clock : clocks)
		{
			hit = clock.CheckHitCollision((*p).GetHead(), (*p).GetTail());

			if(hit && !clock.GetIsSmall()) 
			{
				lgClockHit++;
			}
		}

		offScreen = (*p).CheckOffscreen(m_ScreenWidth, m_ScreenWidth);

		// Destroy projectile if hit or off screen
		if(hit || offScreen) 
		{
			(*p).ClearDraw();
			p = projectiles.erase(p);
			continue;
		}
		p++;
	}

	for (size_t i = 0; i < clocks.size(); i++) 
	{
		// Remove any dead clocks
		if(!clocks[i].GetIsAlive())
		{
			clocks.erase(clocks.begin()+i);
			continue;
		}

		// Check for collisions with other clocks, excluding current one
		std::vector<Clock> otherClocks = clocks;
		otherClocks.erase(otherClocks.begin()+i);

		for(auto &other : otherClocks)
		{
			if (clocks[i].CheckClockCollision(other.GetPosition(), other.GetRadius()))
			{
				clocks[i].ReverseDirection();
				other.ReverseDirection();
			}
		}

		// Update alive clocks
		clocks[i].Update();
	}

	// Create two small clocks for each large hit
	for(int i = 0; i < lgClockHit; i++)
	{
		SpawnClocks(true);
	}

	// Create two large clocks if none exist
	if(clocks.size() == 0)
	{
		SpawnClocks(false);
	}
}

// Spawns two clocks in random locations
void C_Application::SpawnClocks(bool isSmall)
{
	for(int n = 0; n < 2 ; n++)
	{
		Clock c = Clock(m_ScreenWidth, m_ScreenHeight, isSmall);
		for (size_t i = 0; i < clocks.size(); i++) 
		{
			// If spawned on another clock, pick a new location
			// Set index back to 0 to ensure new location is valid
			if(clocks[i].CheckClockCollision(c.GetPosition(), c.GetRadius()))
			{
				c.FindNewSpawnPosition();
				i = 0; 
			}
		}
		clocks.push_back(c);
	}	
}

// Draws the individual lines that form the cannon based on the rotation around the cannon's midpoint
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