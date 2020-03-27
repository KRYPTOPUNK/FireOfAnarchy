#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include "Utilities.h"
#include "hacks.h"


typedef HRESULT(APIENTRY* tReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* ﻿pPresentationParameters);
typedef HRESULT(APIENTRY* tPresent)(LPDIRECT3DDEVICE9 pDevice);										// для удобства делаем себе нормальное название функции
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);										//для удобства делаем себе нормальное название функции (WinProc)
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);	// Экспортируем хендлер для imgui
namespace FunctionEnableFlags
{
	bool							bEspActivated			= false;																	//состояние ESP(включить\выключить)
	bool							bShowMenu				= true;																		// переменная для хранения состояния меню (показывать\не показывать)
	bool							bRadarHackActivated		= false;																	//состояние RadarHack
	bool							bNoFlashHack			= false;
	bool							bBunnyHop				= false;
	bool							bRCSenable				= false;
};
//extern float GlowColorsTeammate[4];
//extern float GlowColorsEnemy[4];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////инициализируем переменные	
bool							bInit						= false;																	// !Главная! инициализация (хук)
tPresent						oEndScene					= nullptr;																	// хук ендсцене
tReset							oReset						= nullptr;																	// хук ресета
ImGuiContext*					context						= 0;																		// контекст ImGui
DWORD							addrOfd3d9Device			= 0;																		// адрес девайса
LPDIRECT3DDEVICE9				pD3DDevice					= nullptr;																	// указатель на д3ддевайс
void*							d3d9Device[119];																						// сам Д3ДДевайс
D3DPRESENT_PARAMETERS			*﻿pPresentationParameters	= nullptr;																	//параметры презентации
bool							initialized_imgui			= false;																	// инициализация imgui
WNDPROC							oWndProc					= NULL;																		// текущий хендл процесса
HWND							window1						= NULL;																		//текущий хендл !ИГРОВОГО! окна
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



LRESULT __stdcall WndProc(const HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)	// хук WNDPROC
{
	if (FunctionEnableFlags::bShowMenu) // если вызывается хендлер
	{
		ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
	}
	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam); // если же нет, вызываем оригинальный процесс
}

void InitImGui(IDirect3DDevice9* pDevice)
{

	ImGui::CreateContext();																		// создаем оболочку ImGui
	D3DDEVICE_CREATION_PARAMETERS CP;															// структура параметров для D3D_DEVICE
	pDevice->GetCreationParameters(&CP);														// задаем pDevice'y параметры
	window1 = CP.hFocusWindow;																	// присваиваем HWND -> текущее окно
	oWndProc = (WNDPROC)SetWindowLongPtr(window1, GWL_WNDPROC, (LONG_PTR)WndProc);				// хук WNDPROC
	ImGuiIO& io = ImGui::GetIO(); (void)io;														// создание и настройка структуры ввода/вывода для imGui
	io.IniFilename = NULL;																		// ини файл == 0
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;										// в конфиге ставим, что нам так же нужна клавиатура

	//addrOfd3d9Device = reinterpret_cast<DWORD>(pDevice);
	//io.Fonts->AddFontDefault();																	// загружаем стандартный шрифт
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 16.5f, NULL, io.Fonts->GetGlyphRangesCyrillic());

	ImGui_ImplWin32_Init(window1);																// подстраиваемся под Вин32 в текущем окне
	ImGui_ImplDX9_Init(pDevice);																// подстраиваемся под ДХ9 в текущем pDevice
	initialized_imgui = true;																	// присваиваем переменной инизиализации значение истинно
	return;																						// выходим из функции
}

HRESULT WINAPI hkReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* ﻿pPresentationParameters)		// хукнутая функция ресета 
{

	ImGui_ImplDX9_Shutdown();																	//		уничтожаем контекст DX9
	ImGui_ImplWin32_Shutdown();																	//		уничтожаем контекст Win32
	ImGui::DestroyContext();																	//		уничтожаем контекст ImGui

	initialized_imgui = false;
	//pDevice->Reset(﻿pPresentationParameters);
	//pDevice->Release();


	return oReset(pDevice, ﻿pPresentationParameters);											//возвращаем оригинальную функцию
}

HRESULT APIENTRY hkPresent(IDirect3DDevice9* pDevice) // ХУК ОТРИСОВКИ, МЕНЮ ОТРИСОВЫВАТЬ ЗДЕСЬ
{

	if (!initialized_imgui) //проверка инициализации, если ложно, то ->
	{
		InitImGui(pDevice);// инициализируем
	}
	else
	{
		ImGui::CreateContext();
		ImGui_ImplDX9_NewFrame();												// новый кадр для ДХ9
		ImGui_ImplWin32_NewFrame();												// новый кадр для ВИН32	||| СОХРАНЯТЬ В ТАКОМ ПОРЯДКЕ
		ImGui::NewFrame();														// новый кадр для ImGui
		if (FunctionEnableFlags::bShowMenu)
		{

			ImGui::Begin("KRYPTOPUNK HACK", &FunctionEnableFlags::bShowMenu, ImGuiWindowFlags_MenuBar);
			//ImGui::Text("This is address of pDevice %X", addrOfd3d9Device);
			ImGui::Text(u8"Настройки чита");
			if (ImGui::TreeNode("GlowHack")) // Вкладка GlowHack
			{
				ImGui::Checkbox(u8"Включить/Выключить", &FunctionEnableFlags::bEspActivated); // чекбокс для включения или выключения гловхака
				ImGui::ColorEdit4(u8"Цвет Противников", GlowColorsEnemy, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB); // редактирование цвета противников
				ImGui::ColorEdit4(u8"Цвет Союзников", GlowColorsTeammate, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB);// редактирование цвета тиммейтов
				
				ImGui::TreePop(); // закрытие вкладки
			}
			ImGui::Checkbox(u8"Включить РадарХак", &FunctionEnableFlags::bRadarHackActivated);
			ImGui::Checkbox(u8"Включить NoFlash-Хак", &FunctionEnableFlags::bNoFlashHack);
			ImGui::Checkbox(u8"Включить распрыжку", &FunctionEnableFlags::bBunnyHop);
			ImGui::Checkbox(u8"Включить RCS", &FunctionEnableFlags::bRCSenable);



			
		
			

			ImGui::End();//закрытие меню
			
		}

		ImGui::EndFrame();														// конец кадра (общий)
		ImGui::Render();														// рендер кадра		||| СОХРАНЯТЬ В ТАКОМ ПОРЯДКЕ
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());						// берет равДату для отрисовки
	}

	return oEndScene(pDevice);													// возвращает оригинальную функцию
}
DWORD WINAPI MenuInitialization(HMODULE hMod)												// ГЛАВНАЯ ИНИЦИАЛИЗАЦИЯ
{

	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))							// хукает д3ддевайс
	{

		oEndScene = reinterpret_cast<tPresent>(TrampHook(reinterpret_cast<char*>(d3d9Device[42]), reinterpret_cast<char*>(hkPresent), 7));				// возвращает оригинальную функцию
		//oReset = reinterpret_cast<tReset>(TrampHook(reinterpret_cast<char*>(d3d9Device[16]), reinterpret_cast<char*>(hkReset), 5));

	}
	return 0;
}

