#pragma once
#include<iostream>
#include "csgo.h"

class LocalPlayer
{
private:
	int Health;
	int TeamNum;
	int Flags;
	int FlashDuration;
public:
	static LocalPlayer* Get();
	int* GetHealth();
	int* GetTeam();
	int* GetFlags();
	int* GetFlashDuration();
	int* SetFlashDuration(int Duration);

};

class Player
{
private:
	Player();
public:
	static int* GetMaxPlayer();
	static Player* GetPlayer(int index);

	int* GetHealth();
	int* GetTeam();
	int* GetGlowIndex();
	bool* GetSpotted();
	bool* GetSpottedByMask();
	bool SetSpotted();
	bool SetSpottedByMask();
	bool* bGetDormant();


};