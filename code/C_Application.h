#ifndef TEST_C_APPLICATION_H
#define TEST_C_APPLICATION_H
#include "Projectile.h"
#include "Clock.h"
#include <vector>
#include <ctime>	// for random clock position, clock_t type


class C_Application
{
public:
	
	typedef unsigned int T_PressedKey;

	C_Application(int screenWidth, int screenHeight);
	~C_Application();

	/// Tick is called on fix framerate (50fps)
	void Tick(T_PressedKey pressedKeys);

	void Update();
	void SpawnClocks(bool isSmall);
	void DrawCannonLine(int inX1, int inY1, int inX2, int Y2, double rot, unsigned int color);

	static const T_PressedKey s_KeyLeft  = 0x01;
	static const T_PressedKey s_KeyUp    = 0x02;
	static const T_PressedKey s_KeyRight = 0x04;
	static const T_PressedKey s_KeyDown  = 0x08;
	static const T_PressedKey s_KeySpace = 0x10;

private:

	const int	m_ScreenWidth;
	const int	m_ScreenHeight;
	
	// Members for sample tick
	int			m_CannonX;
	int			m_CannonY;

	std::vector<Projectile> projectiles;
	std::vector<Clock> clocks;

	float m_RotSpeed;
	float m_RotAngle;
	float m_Cooldown;
	clock_t m_CoolStart;

};

#endif // #ifndef TEST_C_APPLICATION_H