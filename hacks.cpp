#include <iostream>
#include <Windows.h>


#include "csgo.h"
#include "SDK.h"
#include "hacks.h"

struct Vector3;

//#include "CSGOClasses.h"
//float GlowColorsTeammate[4] = { 0.f,0.5f,1.f,1.7f };																		//массив цветов дл€ тиммейтов
//float GlowColorsEnemy[4] = { 1.f, 0.1f, 0.f, 1.7f };																		//массив цветов дл€ врагов

void GlowHack(ptrdiff_t pEntityList, ptrdiff_t pGlowObjectManager, ptrdiff_t pLocalPlayer)									// GlowHack
{
	ptrdiff_t LocalPlayer = *reinterpret_cast<ptrdiff_t*>(pLocalPlayer);													// получаем Ћокалѕлеера
	ptrdiff_t GlowObjectManager = *reinterpret_cast<ptrdiff_t*>(pGlowObjectManager);										// получаем √ловќбжектћенеджер
	ptrdiff_t EntityList = *reinterpret_cast<ptrdiff_t*>(pEntityList);														// получаем ≈нтитиЋист



	if (LocalPlayer != NULL && GlowObjectManager != NULL && EntityList != NULL)											// условие на !NULL
	{
		int LocalPlayerTeam = *(int*)(LocalPlayer + hazedumper::netvars::m_iTeamNum);									// получаем номер команды игрока
		for (short i = 0; i < 64; i++)																					// цикл дл§ перебора ентити
		{
			ptrdiff_t CurrEntity = *reinterpret_cast<ptrdiff_t*>(pEntityList + i * 0x10);								// текущий ≈нтити
			if (CurrEntity == NULL)																						// проверка на NULL
			{
				continue;
			}
			int CurrEntityGlowIndex = *reinterpret_cast<int*>(CurrEntity + hazedumper::netvars::m_iGlowIndex);			// получаем индекс подсветки энтити
			int CurrEntityTeamNum = *reinterpret_cast<int*>(CurrEntity + hazedumper::netvars::m_iTeamNum);				// получаем индекс команды энтити
			if (LocalPlayerTeam == CurrEntityTeamNum)																	//если команда энтити совпадает с командой игрока
			{
				glow_t* CurrEntityGlowTeammate = reinterpret_cast<glow_t*>((GlowObjectManager)+((CurrEntityGlowIndex * 0x38) + 0x4)); //подсвечиваем одним цветом
				CurrEntityGlowTeammate->r = GlowColorsTeammate[0];
				CurrEntityGlowTeammate->g = GlowColorsTeammate[1];
				CurrEntityGlowTeammate->b = GlowColorsTeammate[2];
				CurrEntityGlowTeammate->a = GlowColorsTeammate[3];
				CurrEntityGlowTeammate->RenderWhenOccluded = true;
				CurrEntityGlowTeammate->RenderWhenUnoccluded = false;

			}
			else																													//если не совпадает
			{
				glow_t* CurrEntityGlowEnemy = reinterpret_cast<glow_t*>((GlowObjectManager)+((CurrEntityGlowIndex * 0x38) + 0x4));	// то другим
				CurrEntityGlowEnemy->r = GlowColorsEnemy[0];
				CurrEntityGlowEnemy->g = GlowColorsEnemy[1];
				CurrEntityGlowEnemy->b = GlowColorsEnemy[2];
				CurrEntityGlowEnemy->a = GlowColorsEnemy[3];
				CurrEntityGlowEnemy->RenderWhenOccluded = true;
				CurrEntityGlowEnemy->RenderWhenUnoccluded = false;
			}
		}
	}
}
void RadarHack(ptrdiff_t client, ptrdiff_t pEntityList)
{
	ptrdiff_t EntityList = *reinterpret_cast<ptrdiff_t*>(pEntityList);
	CBaseEntity* CurrEntity = nullptr;
	if (EntityList != NULL)
	{
		ptrdiff_t pEntity = NULL;
		for (short unsigned i = 0; i < 64; i++)
		{
			pEntity = *reinterpret_cast<ptrdiff_t*>(client + (hazedumper::signatures::dwEntityList + i * 0x10));
			if (pEntity == NULL) continue;
			CurrEntity = reinterpret_cast<CBaseEntity*>(pEntity);
			if (CurrEntity->IsDormant) continue;
			else if (CurrEntity->TeamNum != 2 && CurrEntity->TeamNum != 3) continue;
			else if (CurrEntity->Health <= 0) continue;
			CurrEntity->Spotted = true;
			CurrEntity->SpottedByMask = true;
		}
	}

}
void NoFlashHack(ptrdiff_t pLocalPlayer)
{
	ptrdiff_t LocalPlayer = *reinterpret_cast<ptrdiff_t*>(pLocalPlayer);
	if (LocalPlayer == NULL) return;
	int FlashDuration = *reinterpret_cast<int*>(LocalPlayer + hazedumper::netvars::m_flFlashDuration);

	if (FlashDuration > 0)
	{
		*reinterpret_cast<int*>(LocalPlayer + hazedumper::netvars::m_flFlashDuration) = 0;
	}

}
bool PlayerIsMoving(ptrdiff_t LocalPlayer)
{
	Vector3 playerVel = *reinterpret_cast<Vector3*>(LocalPlayer + hazedumper::netvars::m_vecVelocity);
	int vel = playerVel.x + playerVel.y + playerVel.z;
	if (vel != 0)
	{
		return true;
	}
	else return false;
}
void BunnyHopHack(ptrdiff_t client, ptrdiff_t pLocalPlayer)																	// через некоторое врем€ после работы вылетает игра
{
	ptrdiff_t LocalPlayer = *reinterpret_cast<ptrdiff_t*>(pLocalPlayer);
	if (LocalPlayer == NULL)
	{
		while (LocalPlayer == NULL)
		{
			LocalPlayer = *reinterpret_cast<ptrdiff_t*>(pLocalPlayer);
		}
	}
	BYTE LP_Flag = *reinterpret_cast<BYTE*>(LocalPlayer + hazedumper::netvars::m_fFlags);
	if (PlayerIsMoving(LocalPlayer))
	{
		if (GetAsyncKeyState(VK_SPACE) && LP_Flag & (1 << 0))
		{
			*reinterpret_cast<int*>(client + hazedumper::signatures::dwForceJump) = 6;
		}
	}

}
void RecoilControlSystem(ptrdiff_t client, ptrdiff_t engine, ptrdiff_t pLocalPlayer)
{
	ptrdiff_t exitKey = VK_F4;
	ptrdiff_t LocalPlayer = *reinterpret_cast<ptrdiff_t*>(pLocalPlayer);
	Vector3* viewAngles = (Vector3*)(*(ptrdiff_t*)(engine + hazedumper::signatures::dwClientState) + hazedumper::signatures::dwClientState_ViewAngles);
	int* iShotFired = (int*)(LocalPlayer + hazedumper::netvars::m_iShotsFired);
	Vector3* aimPunchAngle = (Vector3*)(LocalPlayer + hazedumper::netvars::m_aimPunchAngle);
	Vector3 oldPunch{ 0,0,0 };
	while (!GetAsyncKeyState(VK_F4))
	{
		Vector3 punchAngle = *aimPunchAngle * 2;
		if (*iShotFired > 1)
		{
			Vector3 newAngle = *viewAngles + oldPunch - punchAngle;
			newAngle.Normalize();
			*viewAngles = newAngle;

		}
		oldPunch = punchAngle;
	}


}