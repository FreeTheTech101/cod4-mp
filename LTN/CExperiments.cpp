// ================== CoD4: Multiplayer - http://github.com/vorhon/cod4-mp/ ==================
//
// File:		CExperiments.cpp
// Description:		-
// Start date:		July 30th, 2014
//
// Author(s):		vorhon (vorhon@outlook.com)
//
// =========================================================================================

#include "stdafx.h"

void Menus_Open_Hook(const char* menu)
{
	CGame::Printf(NULL, "Opening menu: %s\n", menu);
}

__declspec(naked) void Menus_Open_Stub()
{
	__asm
	{
		push edi;
		call Menus_Open_Hook;
		add esp, 4h;

		; Go back to the original function
		push ebp;
		mov ebp, esp;
		and esp, 0FFFFFFF8h;
		mov eax, dword ptr [0x550A56];
		jmp eax;
	}
}

void CExperiments::StartOpenMenusHook()
{
	// The new 'fs_basegame' value
	*(DWORD *)0x55E4C9 = (DWORD)"raw";

	// No flash & no recoil
	*(BYTE *)0x451FB9 = 0xEB;
	*(BYTE *)0x457CCF = 0xEB;

	//*(BYTE *)0x550A55 = 0x90;
	//DetourFunction((PBYTE)0x550A50, (PBYTE)Menus_Open_Stub, 5);
}