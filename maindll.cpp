﻿#include <Windows.h>
#include "Utilities.h"
#include "Menu.h"
extern DWORD WINAPI MenuInitialization(HMODULE hMod);
void HacksHandler() // обработчик для читов
{
	while (true)
	{
		if (FunctionEnableFlags::bEspActivated) // состояние переменной активации есп
		{
			ptrdiff_t client = (ptrdiff_t)GetModuleHandle(TEXT("client_panorama.dll")); //получаем клиент
			ptrdiff_t pLocalPlayer = (client + hazedumper::signatures::dwLocalPlayer); //получаем *локалплеера
			ptrdiff_t pGlowObjectManager = (client + hazedumper::signatures::dwGlowObjectManager);//получаем *ГловОбжектМенеджер
			ptrdiff_t pEntityList = (client + hazedumper::signatures::dwEntityList);//получаем *Энтитилист
			GlowHack(pEntityList, pGlowObjectManager, pLocalPlayer);// функция чита(ГловХак)
			Sleep(10);
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
		CreateThread(nullptr, 0, (PTHREAD_START_ROUTINE)clickHandler, hModule, 0, nullptr);

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}