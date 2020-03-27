#pragma once

struct Vector3
{
	float x;
	float y;
	float z;
	Vector3 operator+(Vector3 d)
	{
		return { x + d.x, y + d.y, z + d.z };
	}
	Vector3 operator-(Vector3 d)
	{
		return { x - d.x, y - d.y, z - d.z };
	}
	Vector3 operator*(Vector3 d)
	{

	}
	Vector3 operator*(float d)
	{
		return { x*d,y*d,z*d };
	}
	void Normalize()
	{
		while (y < -180)
		{
			y += 360;
		}
		while (y > 180)
		{
			y -= 360;
		}
		if (x > 89)
		{
			x = 89;
		}
		if (x < -89)
		{
			x = -89;
		}
	}
};
//#include "CSGOClasses.h"
 static float GlowColorsTeammate[4] = { 0.f,0.5f,1.f,1.7f };																		//массив цветов для тиммейтов
 static float GlowColorsEnemy[4] = { 1.f, 0.1f, 0.f, 1.7f };																		//массив цветов для врагов

void GlowHack(ptrdiff_t pEntityList, ptrdiff_t pGlowObjectManager, ptrdiff_t pLocalPlayer);									// GlowHack

void RadarHack(ptrdiff_t client, ptrdiff_t pEntityList);

void NoFlashHack(ptrdiff_t pLocalPlayer);

bool PlayerIsMoving(ptrdiff_t LocalPlayer);
void BunnyHopHack(ptrdiff_t client, ptrdiff_t pLocalPlayer);																	// через некоторое время после работы вылетает игра

void RecoilControlSystem(ptrdiff_t client, ptrdiff_t engine, ptrdiff_t pLocalPlayer);