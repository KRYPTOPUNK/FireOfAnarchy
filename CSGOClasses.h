#pragma once


class LocalPlayers
{
private:
	int Health;
	int TeamNum;
	int Flags;
	int FlashDuration;
public:
	static LocalPlayers* Get();
	int* GetHealth();
	int* GetTeam();
	int* GetFlags();
	int* GetFlashDuration();

};

class Player
{
private:
	char padding_0000[236];
	bool IsDormant;
	char padding_0002[6];
	int32_t TeamNum;
	char padding_0003[8];
	int32_t Health;
	int32_t Flags;
	char padding_0004[48];
	Vector VecOrigin;
	char padding_0005[2041];
	bool Spotted;
	char padding_0006[66];
	bool SpottedByMask;
	char padding_0007[4355];
	int32_t CompetitiveRanking;
	char padding_0008[256];
	int32_t CompetitiveWins;
	char padding_0009[2844];
	unsigned BoneMatrix;
	char padding_000A[236];
	Matrix_3x4_t Abdomen;
	Matrix_3x4_t Stomach;
	Matrix_3x4_t Neck;
	Matrix_3x4_t Head;
	char padding_000E[1904];
	int32_t AccountId;
	char padding_000F[84];
	Vector ViewPunchAngle;
	Vector AimPunchAngle;
	char padding_0010[524];
	int32_t Clip1;
	char padding_0012[200];
	float AccuracyPenalty;
	char padding_0013[1532];
	bool IsScoped;
	char padding_0015[7];
	bool IsDefusing;
	char padding_0016[19];
	bool GunGameImmunity;
	char padding_0017[27359];
	int32_t GlowIndex;
	char padding_0018[3876];
	bool HasHelmet;
	char padding_0019[11];
	int32_t ArmorValue;
	char padding_001A[12];
	bool HasDefuser;
	
public:
	static int* GetMaxPlayer();
	static Player* GetPlayer(int index);
	//int* GetHealth();
	//int* GetTeam();
	//int* GetGlowIndex();
	//bool* GetSpotted();
	//bool* GetSpottedByMask();
	int GetTeam();
	int GetGlowIndex();
	//bool* bGetDormant();
	

};