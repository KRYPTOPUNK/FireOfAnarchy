#include "CSGOClasses.h"
#include <Windows.h>

LocalPlayer* LocalPlayer::Get()
{
	static ptrdiff_t clientBase = (ptrdiff_t)GetModuleHandle(TEXT("client_panorama.dll"));
	static LocalPlayer* localPlayer = (LocalPlayer*)(clientBase + hazedumper::signatures::dwLocalPlayer);
	return localPlayer;
}

int* LocalPlayer::GetHealth()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_iHealth));
}

int* LocalPlayer::GetTeam()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_iTeamNum));
}

int* LocalPlayer::GetFlags()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_fFlags));
}
int* LocalPlayer::GetFlashDuration()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_flFlashDuration));
}
int* LocalPlayer::SetFlashDuration(int Duration)
{
	int* flashDuration = LocalPlayer::GetFlashDuration();
	flashDuration = reinterpret_cast<int*>(Duration);
	return flashDuration;

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


int* Player::GetHealth()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_iHealth));
}

int* Player::GetTeam()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_iTeamNum));
}

int* Player::GetGlowIndex()
{
	return reinterpret_cast<int*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_iGlowIndex));
}
bool* Player::GetSpotted()
{
	return reinterpret_cast<bool*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_bSpotted));
}

bool* Player::GetSpottedByMask()
{
	return reinterpret_cast<bool*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_bSpottedByMask));
}

bool Player::SetSpotted()
{
	bool Spotted = reinterpret_cast<bool*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_bSpotted));
	Spotted = true;
	return Spotted;
};
bool Player::SetSpottedByMask()
{
	bool SpottedByMask = reinterpret_cast<bool*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::netvars::m_bSpottedByMask));
	SpottedByMask = true;
	return SpottedByMask;

}
bool* Player::bGetDormant()
{
	return  reinterpret_cast<bool*>(*reinterpret_cast<ptrdiff_t*>(this + hazedumper::signatures::m_bDormant));
}