#include "stdafx.h"

// Variables
DWORD COffsets::VAR_GameClassName;
DWORD COffsets::VAR_GameWindowTitle;
DWORD COffsets::VAR_ConsoleClassName;
DWORD COffsets::VAR_ConsoleWindowTitle;
DWORD COffsets::VAR_ConsoleLoadImage;
DWORD COffsets::VAR_ConsoleFontName;
DWORD COffsets::VAR_ConsoleItalic;
DWORD COffsets::VAR_ConsoleUnderline;
DWORD COffsets::VAR_MasterServer;
DWORD COffsets::VAR_cmd_functions;

// Functions
DWORD COffsets::FUNC_Sys_CreateConsole;
DWORD COffsets::FUNC_SV_AddTestClient;
DWORD COffsets::FUNC_Com_PrintWarning;
DWORD COffsets::FUNC_Com_Printf;
DWORD COffsets::FUNC_UI_SafeTranslateString;
DWORD COffsets::FUNC_CL_VerifyCDKey;
DWORD COffsets::FUNC_FS_Startup;
DWORD COffsets::FUNC_Cmd_FindCommand;
DWORD COffsets::FUNC_GetConsoleInput;
DWORD COffsets::FUNC_CL_AddPlayerProfile;
DWORD COffsets::FUNC_CL_SortPlayerProfiles;
DWORD COffsets::FUNC_CL_CreatePlayerProfile;
DWORD COffsets::FUNC_CL_DeletePlayerProfile;
DWORD COffsets::FUNC_CL_GetPlayerProfile;
DWORD COffsets::FUNC_CL_SelectPlayerProfile;
DWORD COffsets::FUNC_CL_LoadPlayerProfile;
DWORD COffsets::FUNC_Menus_FindByName;
DWORD COffsets::FUNC_Cmd_ExecFromDisk;
DWORD COffsets::FUNC_Com_WriteConfigToFile;

// Calls
DWORD COffsets::CALL_CreateSplashScreenWind;

// Jumps
DWORD COffsets::JNZ_Punkbuster_1;
DWORD COffsets::JNZ_Punkbuster_2;
DWORD COffsets::JNZ_Punkbuster_3;
DWORD COffsets::JZ_ConsolePostQuit_1;
DWORD COffsets::JZ_ConsolePostQuit_2;

bool COffsets::m_bInitialized;

// -------------------------------------------------

void COffsets::Initialize()
{
	VAR_GameClassName			= 0x6F5248;
	VAR_GameWindowTitle			= 0x6D7A9C;
	VAR_ConsoleClassName		= 0x6F5E10;
	VAR_ConsoleWindowTitle		= 0x6F5E20;
	VAR_ConsoleLoadImage		= 0x6F5E3C;
	VAR_ConsoleFontName			= 0x6F5E30;
	VAR_ConsoleItalic			= (0x57A5C5 + 0x01);
	VAR_ConsoleUnderline		= (0x57A5C3 + 0x01);
	VAR_MasterServer			= 0x6D0554;
	VAR_cmd_functions			= 0x1410B3C;

	FUNC_Sys_CreateConsole		= 0x57A730;
	FUNC_SV_AddTestClient		= 0x52D370;
	FUNC_Com_PrintWarning		= 0x4FCD30;
	FUNC_Com_Printf				= 0x4FCA50;
	FUNC_UI_SafeTranslateString = 0x54ACA0;
	FUNC_CL_VerifyCDKey			= 0x4712E0;
	FUNC_FS_Startup				= 0x55E670;
	FUNC_Cmd_FindCommand		= 0x4F9950;
	FUNC_GetConsoleInput		= 0x57A7A6;
	FUNC_CL_AddPlayerProfile	= 0x5450C0;
	FUNC_CL_SortPlayerProfiles	= 0x545070;
	FUNC_CL_CreatePlayerProfile = 0x545210;
	FUNC_CL_DeletePlayerProfile = 0x5453B0;
	FUNC_CL_GetPlayerProfile	= 0x544F80;
	FUNC_CL_SelectPlayerProfile = 0x545020;
	FUNC_CL_LoadPlayerProfile	= 0x4FAD00;
	FUNC_Menus_FindByName		= 0x54C230;
	FUNC_Cmd_ExecFromDisk		= 0x4F9390;
	FUNC_Com_WriteConfigToFile	= 0x4FFAB0;

	CALL_CreateSplashScreenWind = 0x57761C;

	JNZ_Punkbuster_1			= 0x5776B8;
	JNZ_Punkbuster_2			= 0x5776D6;
	JNZ_Punkbuster_3			= 0x5776C3;
	JZ_ConsolePostQuit_1		= 0x57A1D7;
	JZ_ConsolePostQuit_2		= 0x57A1DF;

	m_bInitialized = true;
}

// -------------------------------------------------