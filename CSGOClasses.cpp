#include<iostream>
#include "csgo.h"
#include "SDK.h"

#include <Windows.h>
#include "CSGOClasses.h"

LocalPlayers* LocalPlayers::Get()
{
	static ptrdiff_t clientBase = reinterpret_cast<ptrdiff_t>(GetModuleHandle(TEXT("client_panorama.dll")));
	static LocalPlayers* localPlayer = reinterpret_cast<LocalPlayers*>(clientBase + hazedumper::signatures::dwLocalPlayer);
	return localPlayer;
}

int* LocalPlayers::GetHealth()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_iHealth));
}

int* LocalPlayers::GetTeam()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_iTeamNum));
}

int* LocalPlayers::GetFlags()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_fFlags));
}
int* LocalPlayers::GetFlashDuration()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_flFlashDuration));
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Player* Player::GetPlayer(int index)
{
	static ptrdiff_t moduleBase = (ptrdiff_t)GetModuleHandle(TEXT("client_panorama.dll"));
	static ptrdiff_t entityList = moduleBase + hazedumper::signatures::dwEntityList;

	return reinterpret_cast<Player*>(entityList + index * 0x10);
}

int* Player::GetMaxPlayer()
{
	static ptrdiff_t moduleBase = (ptrdiff_t)GetModuleHandle(TEXT("engine.dll"));
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>((moduleBase + hazedumper::signatures::dwClientState) + hazedumper::signatures::dwClientState_MaxPlayer));
}


//int* Player::GetHealth()
//{
//	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_iHealth));
//}
//
//int* Player::GetTeam()
//{
//	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_iTeamNum));
//}
//
//int* Player::GetGlowIndex()
//{
//	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_iGlowIndex));
//}
//bool* Player::GetSpotted()
//{
//	return reinterpret_cast<bool*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_bSpotted));
//}
//
//bool* Player::GetSpottedByMask()
//{
//	return reinterpret_cast<bool*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_bSpottedByMask));
//}
//
//bool* Player::bGetDormant()
//{
//	return  reinterpret_cast<bool*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::signatures::m_bDormant));
//}
int Player::GetTeam()
{
	return TeamNum;
}
int Player::GetGlowIndex()
{
	return GlowIndex;
}