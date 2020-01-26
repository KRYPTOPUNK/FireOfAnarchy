#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <Psapi.h>

#include "imconfig.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"

#include <d3d9.h>

#pragma comment(lib,"d3d9.lib")


//typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

class MemoryConfigurator
{
protected:
	MODULEINFO modInfo = { 0 };
	HMODULE hModule = NULL;
	DWORD FinalAddress = 0;
public:
	MemoryConfigurator();
	void MsgBoxAddy(DWORD addr);
	MODULEINFO GetModuleInfo(char* szModule);
	void WriteToMemoryBytes(uintptr_t addressToWrite, char* valueToWrite, int byteNum);
	DWORD FindPattern(char* moduleName, char* pattern, char* mask);
	bool Hook(void* toHook, void* ourFunct, int len);
	DWORD GetModuleAddress(char* moduleName);

	DWORD jmpBackAddr = 0;

	~MemoryConfigurator();
};

/*class DirectXHookingUtilities
{
protected:
	HWND hWnd;
	HMODULE hD3DX;
	PRESENT9 g_D3DX_Present = 0;
	BYTE g_codeFragment_p9[5] = { 0,0,0,0,0 };
	BYTE g_jmp_p9[5] = { 0,0,0,0,0 };
	DWORD g_savedProtection_p9 = 0;
	DWORD present9 = 0;
	D3DRECT rec = { 10,10,120,30 };
	ID3DXFont *m_font = 0;
	RECT fontRect = { 10,15,120,120 };
	D3DCOLOR bkgColor = 0;
	D3DCOLOR fontColor = 0;
	DIRECT3DCREATE9 Direct3DCreate9 = 0;
	IDirect3D9* d3d = 0;
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	IDirect3DDevice9* d3dDevice = 0;
	DWORD* vTablePtr;
	DWORD addr;
	BYTE* codeDest;
	DWORD res;
public:
	bool indicate;
	void GetDevice9Methods();
	long __stdcall HookedPresent9(IDirect3DDevice9* self, const RECT* src, const RECT* dest, HWND hWnd, void* unused);
	void HookDevice9Methods();
	
	void DrawIndicator(void* self, bool indicate);
	
	
}; */


//            _______ _________            _______  _______  _             _______  _        _______  _______  _______ 
//  |\     /|(       )\__   __/  |\     /|(  ___  )(  ___  )| \    /\     (  ____ \( \      (  ___  )(  ____ \(  ____ \
//  | )   ( || () () |   ) (     | )   ( || (   ) || (   ) ||  \  / /     | (    \/| (      | (   ) || (    \/| (    \/
//  | |   | || || || |   | |     | (___) || |   | || |   | ||  (_/ /      | |      | |      | (___) || (_____ | (_____ 
//  ( (   ) )| |(_)| |   | |     |  ___  || |   | || |   | ||   _ (       | |      | |      |  ___  |(_____  )(_____  )
//   \ \_/ / | |   | |   | |     | (   ) || |   | || |   | ||  ( \ \      | |      | |      | (   ) |      ) |      ) |
//    \   /  | )   ( |   | |     | )   ( || (___) || (___) ||  /  \ \     | (____/\| (____/\| )   ( |/\____) |/\____) |
//     \_/   |/     \|   )_(_____|/     \|(_______)(_______)|_/    \/_____(_______/(_______/|/     \|\_______)\_______)
//                         (_____)                                  (_____)                                            

class VMTHookManager
{
public:
	VMTHookManager(void** vTable); //constructor
	~VMTHookManager(); //destructor
	void* GetFunctionAddyByIndex(unsigned short index);// getting the address of a function in the vtable by index
	void* Hook(unsigned short index, void* ourFunction); // hooking the virtual function by index
	bool Unhook(unsigned short index); // unhooking the virtual function by index
	void UnhookAll(); //unhook all the functions

private:
	//member variables
	void** m_vTable; // the vtable of some object 
	unsigned short m_numberFuncs; // number of virtual functions
	void** m_originalFuncs = nullptr; // we'll save the original addresses here

	unsigned short GetNumberOfFunctions(); //get the number of virtual functions
	bool toHook(unsigned short index, bool hook = false, void* ourFunction = nullptr, uintptr_t* bufferOriginalFunc = nullptr); //function used to hook/unhook 
};


static HWND window;

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);

HWND GetProcessWindow();

bool GetD3D9Device(void** pTable, size_t Size);



bool Hook(char* src, char* dst, int len);

char* TrampHook(char* src, char* dst, unsigned int len);

