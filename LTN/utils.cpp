// ================== CoD4: Multiplayer - http://github.com/vorhon/cod4-mp/ ==================
//
// File:		utils.cpp
// Description:		-
// Start date:		July 30th, 2014
//
// Author(s):		vorhon (vorhon@outlook.com)
//
// =========================================================================================

#include "stdafx.h"

void* DetourFunction(BYTE *source, const BYTE *destination, const int length)
{
	BYTE *jmp = (BYTE *)malloc(length + 5);
	DWORD dwBack;

	VirtualProtect(source, length, PAGE_EXECUTE_READWRITE, &dwBack);

	memcpy(jmp, source, length);
	jmp += length;

	jmp[0] = 0xE9;
	*(DWORD *)(jmp + 1) = (DWORD)(source + length - jmp) - 5;

	source[0] = 0xE9;
	*(DWORD*)(source + 1) = (DWORD)(destination - source) - 5;

	for (int i = 5; i < length; i++)
	{
		source[i] = 0x90;
	}

	VirtualProtect(source, length, dwBack, &dwBack);

	return (jmp - length);
}