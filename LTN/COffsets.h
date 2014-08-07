#ifndef __COFFSETS_H__
#define __COFFSETS_H__


class COffsets
{
public:
	static bool m_bInitialized;
	static void Initialize();

	// Variables
	static DWORD VAR_GameClassName;
	static DWORD VAR_GameWindowTitle;
	static DWORD VAR_ConsoleClassName;
	static DWORD VAR_ConsoleWindowTitle;
	static DWORD VAR_ConsoleLoadImage;
	static DWORD VAR_ConsoleFontName;
	static DWORD VAR_ConsoleItalic;
	static DWORD VAR_ConsoleUnderline;
	static DWORD VAR_MasterServer;
	static DWORD VAR_cmd_functions;

	// Functions
	static DWORD FUNC_Sys_CreateConsole;
	static DWORD FUNC_SV_AddTestClient;
	static DWORD FUNC_Com_PrintWarning;
	static DWORD FUNC_Com_Printf;
	static DWORD FUNC_UI_SafeTranslateString;
	static DWORD FUNC_CL_VerifyCDKey;
	static DWORD FUNC_FS_Startup;
	static DWORD FUNC_Cmd_FindCommand;
	static DWORD FUNC_GetConsoleInput;
	static DWORD FUNC_CL_AddPlayerProfile;
	static DWORD FUNC_CL_SortPlayerProfiles;
	static DWORD FUNC_CL_CreatePlayerProfile;
	static DWORD FUNC_CL_DeletePlayerProfile;
	static DWORD FUNC_CL_GetPlayerProfile;
	static DWORD FUNC_CL_SelectPlayerProfile;
	static DWORD FUNC_CL_LoadPlayerProfile;
	static DWORD FUNC_Menus_FindByName;
	static DWORD FUNC_Cmd_ExecFromDisk;
	static DWORD FUNC_Com_WriteConfigToFile;

	// Calls
	static DWORD CALL_CreateSplashScreenWind;

	// Jumps
	static DWORD JNZ_Punkbuster_1;
	static DWORD JNZ_Punkbuster_2;
	static DWORD JNZ_Punkbuster_3;
	static DWORD JZ_ConsolePostQuit_1;
	static DWORD JZ_ConsolePostQuit_2;
};


#endif /* __COFFSETS_H__ */