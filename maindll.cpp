#include <Windows.h>
#include "Utilities.h"
#include "Menu.h"
extern DWORD WINAPI MenuInitialization(HMODULE hMod);
void HacksHandler() // обработчик для читов
{
	while (true)
	{
		ptrdiff_t client = (ptrdiff_t)GetModuleHandle(TEXT("client_panorama.dll")); //получаем клиент
		ptrdiff_t pLocalPlayer = (client + hazedumper::signatures::dwLocalPlayer); //получаем *локалплеера
		ptrdiff_t pGlowObjectManager = (client + hazedumper::signatures::dwGlowObjectManager);//получаем *ГловОбжектМенеджер
		ptrdiff_t pEntityList = (client + hazedumper::signatures::dwEntityList);//получаем *Энтитилист
		ptrdiff_t engine = (ptrdiff_t)GetModuleHandle(TEXT("engine.dll"));
		if (FunctionEnableFlags::bEspActivated) // состояние переменной активации есп
		{

			GlowHack(pEntityList, pGlowObjectManager, pLocalPlayer);// функция чита(ГловХак)
			Sleep(1);
		}
		if (FunctionEnableFlags::bRadarHackActivated)
		{

			RadarHack(client, pEntityList);
			Sleep(1);
		}
		if (FunctionEnableFlags::bNoFlashHack)
		{

			NoFlashHack(pLocalPlayer);
			Sleep(1);
		}
		if (FunctionEnableFlags::bBunnyHop)
		{

			BunnyHopHack(client, pLocalPlayer);
			Sleep(1);
		}
		

	}

}
void RCSHandler()
{
	while (true)
	{
		if (FunctionEnableFlags::bRCSenable)
		{
			ptrdiff_t engine = (ptrdiff_t)GetModuleHandle(TEXT("engine.dll"));
			ptrdiff_t client = (ptrdiff_t)GetModuleHandle(TEXT("client_panorama.dll")); //получаем клиент
			ptrdiff_t pLocalPlayer = (client + hazedumper::signatures::dwLocalPlayer); //получаем *локалплеера
			RecoilControlSystem(client, engine, pLocalPlayer);
			Sleep(1);
		}
	}
}

void clickHandler()// обработчик нажатий
{
	while (true)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1) // Если нажата "INSERT"
		{
			FunctionEnableFlags::bShowMenu = !FunctionEnableFlags::bShowMenu; // переключаем переменную
		}
		Sleep(10);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: 
		CreateThread(nullptr, 0, (PTHREAD_START_ROUTINE)MenuInitialization, hModule, 0, nullptr);
		CreateThread(nullptr, 0, (PTHREAD_START_ROUTINE)HacksHandler, hModule, 0, nullptr);
		CreateThread(nullptr, 0, (PTHREAD_START_ROUTINE)RCSHandler, hModule, 0, nullptr);
		CreateThread(nullptr, 0, (PTHREAD_START_ROUTINE)clickHandler, hModule, 0, nullptr);
		

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}