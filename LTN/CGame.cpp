// ================== CoD4: Multiplayer - http://github.com/vorhon/cod4-mp/ ==================
//
// File:		CGame.cpp
// Description:		The game stuff.
// Start date:		July 30th, 2014
//
// Author(s):		vorhon (vorhon@outlook.com)
//
// =========================================================================================

#include "stdafx.h"

int i = 0;
DWORD orig_FS_Startup = 0x55E676;

// -------------------------------------------------

void Cmd_HelloWorld_f()
{
	CGame::Printf(NULL, "Hello world!\n");
}

// -------------------------------------------------

void CGame::PreInitialization(void)
{
	// Customize and create the developer console
	CConsole* pConsole = new CConsole();
	//pConsole->ToggleItalic();
	//pConsole->ToggleUnderline();
	pConsole->SetFontName("Courier Normal");
	pConsole->SetLoadImage("codlogo.bmp");
	pConsole->CreateConsole();
	pConsole->StartHook();
	
	// Wait until the console is created
	while (!pConsole->Wait());

	// Prints our welcome message at the very top of the console
	Printf(NULL, "Welcome to *********.\n");

	// Custom UI translate strings
	CUIStrings* pUIStrings = new CUIStrings();
	pUIStrings->AddTranslation("MENU_JOIN_SERVER_CAP", "SERVER BROWSER");
	pUIStrings->AddTranslation("MENU_JOIN_GAME", "Server Browser");
	pUIStrings->AddTranslation("MENU_START_NEW_SERVER", "Private Match");
	pUIStrings->AddTranslation("MENU_GAME_EXPERIENCE_MAY_CHANGE", "Welcome to *********.");
	pUIStrings->StartHook();

	CUIStringsSEH* pUIStringsSEH = new CUIStringsSEH();
	pUIStringsSEH->StartHook();

	// Additional commands
	CCommands* pCommands = new CCommands();
	pCommands->AddCommand("helloworld", Cmd_HelloWorld_f);

	CFastFiles* pFastFiles = new CFastFiles();
	pFastFiles->StartHook();

	CExperiments* pExperiments = new CExperiments();
	pExperiments->StartOpenMenusHook();

	CProfiles* pProfiles = new CProfiles();
	pProfiles->StartHooks();
}

// -------------------------------------------------

__declspec(naked) void FS_Startup_Stub()
{
	// Call it only once
	if (!i++)
	{
		CGame::PreInitialization();
	}

	__asm
	{
		; Go back to the original function

		push ecx
		push ebx
		mov ebx, dword ptr[esp + 8 + 4]
		jmp orig_FS_Startup
	}
}

// -------------------------------------------------
// Everything we need to patch starts here

void CGame::StartGame()
{
	if (!COffsets::m_bInitialized)
	{
		MessageBoxA(NULL, "LTN-#0003: COffsets must be initialized before starting the game.", "Error", MB_OK | MB_ICONERROR);
		_exit(0xBABE0003);
	}

	// Unprotect the whole memory of the game
	this->UnprotectMemory();

	// Game's window title & class name
	strcpy((PCHAR)COffsets::VAR_GameClassName, "LTN");
	strcpy((PCHAR)COffsets::VAR_GameWindowTitle, "LTN-client");

	// Console's window title & class name
	strcpy((PCHAR)COffsets::VAR_ConsoleClassName, "LtnConsole");
	strcpy((PCHAR)COffsets::VAR_ConsoleWindowTitle, "LTN Console");

	// Disable splash screen, so it won't cover the whole console up anymore
	memset((LPVOID)COffsets::CALL_CreateSplashScreenWind, 0x90, 5);

	// Tiring punkbuster removal
	*(BYTE *)COffsets::JNZ_Punkbuster_1 = 0xEB; // 'Unable to initialize punkbuster. Punkbuster is disabled'
	*(BYTE *)COffsets::JNZ_Punkbuster_2 = 0xEB; // 'Unable to initialize punkbuster. Punkbuster is disabled'
	*(BYTE *)COffsets::JNZ_Punkbuster_3 = 0xEB; // 'Unable to initialize punkbuster. Punkbuster is disabled'

	// CD key requirement removal
	*(DWORD *)COffsets::FUNC_CL_VerifyCDKey = 0x90C301B0; // always return true

	// Redirect 'cod4master.activision.com' to our master server address
	strcpy((PCHAR)COffsets::VAR_MasterServer, "127.0.0.1");

	// Game pre-initialization
	*(BYTE *)(COffsets::FUNC_FS_Startup + 5) = 0x90;
	DetourFunction((PBYTE)COffsets::FUNC_FS_Startup, (PBYTE)FS_Startup_Stub, 5);

	// Bypass write/cheat protection on dvars
	// (I'm tired, will organize the addresses later)
	*(BYTE *)0x56B358 = 0xEB;
	*(BYTE *)0x56B386 = 0xEB;
}

// -------------------------------------------------

void CGame::UnprotectMemory()
{
	HMODULE hModule = GetModuleHandleA(NULL);

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hModule;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((DWORD)hModule + pDosHeader->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNtHeaders->OptionalHeader;
	
	VirtualProtect((LPVOID)hModule, pOptionalHeader->SizeOfImage, PAGE_EXECUTE_READWRITE, new DWORD);
}

// -------------------------------------------------

void CGame::SpawnBots(int n)
{
	if (!n || n >= 18)
	{
		PrintWarning(14, "The number of bots to be spawned cannot be null or higher than 17.\n");
		return;
	}
	
	Printf(NULL, "Spawning %d bots...\n", n);

	for (int i = 0; i < n; i++)
	{
		DWORD dwFunc = COffsets::FUNC_SV_AddTestClient;
		__asm call dwFunc;
	}
}

// -------------------------------------------------

void CGame::Printf(int level, const char* fmt, ...)
{
	DWORD dwFunc = COffsets::FUNC_Com_Printf;

	char vaBuffer[0x1000];

	va_list va;
	va_start(va, fmt);
	_vsnprintf(vaBuffer, sizeof(vaBuffer), fmt, va);
	va_end(va);

	printf(vaBuffer);
	((void(*)(int, const char*, int))(dwFunc))(level, vaBuffer, 0);
}

// -------------------------------------------------

void CGame::PrintWarning(int level, const char* fmt, ...)
{
	DWORD dwFunc = COffsets::FUNC_Com_Printf;

	char vaBuffer[4095];

	va_list va;
	va_start(va, fmt);
	strncpy(vaBuffer, "^3", 4095);

	char* v2, v3;

	v2 = vaBuffer;

	do
	{
		v3 = *v2++;
	}
	while (v3);

	_vsnprintf(&vaBuffer[v2 - &vaBuffer[1]], 0x1000 - (v2 - &vaBuffer[1]), fmt, va);

	__asm call dwFunc;
}

// -------------------------------------------------