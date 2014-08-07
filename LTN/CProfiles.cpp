// ================== CoD4: Multiplayer - http://github.com/vorhon/cod4-mp/ ==================
//
// File:		CProfiles.cpp
// Description:		Complete removal of the profiles system.
// Start date:		July 30th, 2014
//
// Author(s):		vorhon (vorhon@outlook.com)
//
// =========================================================================================

#include "stdafx.h"

DWORD orig_Menus_FindByName = 0x54C236;
DWORD orig_Cmd_ExecFromDisk = 0x4F9395;
DWORD orig_Com_WriteConfigToFile = 0x4FFAB5;

// -------------------------------------------------

/*

const char* GetProfilePath_Hook(const char* filename)
{
	CGame::Printf(NULL, filename);

	return filename;
}

__declspec(naked) void GetProfilePath_Stub()
{
	__asm
	{
		mov eax, [esp + 8h];
		push eax;
		call GetProfilePath_Hook;
		add esp, 4h;

		test eax, eax;
		retn;
	}
}

*/

// -------------------------------------------------

void ProfileWarning_Hook()
{
	CGame::Printf(NULL, "The profiles system was removed and can't be used any longer.\n");
}

// -------------------------------------------------

bool Menus_FindByName_Hook(const char* p)
{
	if (strstr(GetCommandLineA(), "-menudebug"))
		CGame::Printf(NULL, "Menu: %s\n", p);

	// Profile menus don't exist ... any longer :)
	if (_stricmp(p, "player_profile") == NULL ||
		_stricmp(p, "profile_create_popmenu") == NULL ||
		_stricmp(p, "profile_must_create_popmenu") == NULL)
	{
		return false;
	}

	return true;
}

// -------------------------------------------------

__declspec(naked) void Menus_FindByName_Stub()
{
	__asm
	{
		mov eax, [esp + 8h];
		push eax;
		call Menus_FindByName_Hook;
		add esp, 4h;

		test al, al;
		jnz jumpBack;

		retn;

	jumpBack:
		push ebx;
		push ebp;
		mov ebp, [esp + 8h + 4h];
		jmp orig_Menus_FindByName;
	}
}

// -------------------------------------------------

const char* Cmd_ExecFromDisk_Hook(const char* filename)
{
	if (strstr(filename, "profiles"))
	{
		return "config_mp.cfg";
	}

	return filename;
}

// -------------------------------------------------

__declspec(naked) void Cmd_ExecFromDisk_Stub()
{
	__asm
	{
		push edi;
		call Cmd_ExecFromDisk_Hook;
		add esp, 4h;

		test eax, eax;
		mov edi, eax;

		push ecx;
		lea eax, [esp + 4h + -4h];
		push esi;
		jmp orig_Cmd_ExecFromDisk;
	}
}

// -------------------------------------------------

const char* Com_WriteConfigToFile_Hook(const char* filename)
{
	if (strstr(filename, "profiles"))
	{
		return "config_mp.cfg";
	}

	return filename;
}

// -------------------------------------------------

__declspec(naked) void Com_WriteConfigToFile_Stub()
{
	__asm
	{
		push ecx;
		call Com_WriteConfigToFile_Hook;
		add esp, 4h;

		test eax, eax;
		mov ecx, eax;

		mov eax, 2004h;
		jmp orig_Com_WriteConfigToFile;
	}
}

// -------------------------------------------------

void CProfiles::StartHooks()
{
	// Read/write 'config_mp.cfg' to 'players', not 'players/profiles/...'
	DetourFunction((PBYTE)COffsets::FUNC_Cmd_ExecFromDisk, (PBYTE)Cmd_ExecFromDisk_Stub, 5);			// 'Cmd_ExecFromDisk'
	DetourFunction((PBYTE)COffsets::FUNC_Com_WriteConfigToFile, (PBYTE)Com_WriteConfigToFile_Stub, 5);	// 'Com_WriteConfigToFile'

	// Implant our [s]bomb[/s] warning in there
	DetourFunction((PBYTE)COffsets::FUNC_CL_AddPlayerProfile, (PBYTE)ProfileWarning_Hook, 5);			// 'CL_AddPlayerProfile'
	DetourFunction((PBYTE)COffsets::FUNC_CL_SortPlayerProfiles, (PBYTE)ProfileWarning_Hook, 5);			// 'CL_SortPlayerProfiles'
	DetourFunction((PBYTE)COffsets::FUNC_CL_CreatePlayerProfile, (PBYTE)ProfileWarning_Hook, 5);		// 'CL_CreatePlayerProfile'
	DetourFunction((PBYTE)COffsets::FUNC_CL_DeletePlayerProfile, (PBYTE)ProfileWarning_Hook, 5);		// 'CL_DeletePlayerProfile'
	DetourFunction((PBYTE)COffsets::FUNC_CL_GetPlayerProfile, (PBYTE)ProfileWarning_Hook, 5);			// 'CL_GetPlayerProfile'
	DetourFunction((PBYTE)COffsets::FUNC_CL_SelectPlayerProfile, (PBYTE)ProfileWarning_Hook, 5);		// 'CL_SelectPlayerProfile'
	DetourFunction((PBYTE)COffsets::FUNC_CL_LoadPlayerProfile, (PBYTE)ProfileWarning_Hook, 5);			// 'CL_LoadPlayerProfile'

	// Prevent the game from opening any menu related to profiles
	DetourFunction((PBYTE)COffsets::FUNC_Menus_FindByName, (PBYTE)Menus_FindByName_Stub, 5);			// 'Menus_FindByName'
}

// -------------------------------------------------
