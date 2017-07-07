#include "C_Application.h"
#include "graphics.h"
#include "time.h"


static const float k_PI = 3.1415926536f;


C_Application::C_Application(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
	, m_CannonX(m_ScreenWidth/2)
	, m_CannonY(m_ScreenHeight/2)
{

}


C_Application::~C_Application()
{

}


void C_Application::Tick(T_PressedKey pressedKeys)
{
	// Sample tick

	// Clear screen on cannon position

	FillRect(m_CannonX-10, m_CannonY, 21, 31, GetRGB(0, 0, 0));

	// Key processing

	if(pressedKeys & s_KeyLeft)
	{
		m_CannonX = max(0, m_CannonX-4);
	}

	if(pressedKeys & s_KeyRight)
	{
		m_CannonX = min(m_ScreenWidth, m_CannonX+4);
	}

	if(pressedKeys & s_KeyUp)
	{
		m_CannonY = max(0, m_CannonY-4);
	}

	if(pressedKeys & s_KeyDown)
	{
		m_CannonY = min(m_ScreenHeight, m_CannonY+4);
	}

	if(pressedKeys & s_KeySpace)
	{
	}

	// Draw cannon

	DrawLine(m_CannonX,    m_CannonY,    m_CannonX-10, m_CannonY+30, GetRGB(255,   0,   0));
	DrawLine(m_CannonX,    m_CannonY,    m_CannonX+10, m_CannonY+30, GetRGB(  0, 255,   0));
	DrawLine(m_CannonX-10, m_CannonY+30, m_CannonX+10, m_CannonY+30, GetRGB(  0,   0, 255));
}
