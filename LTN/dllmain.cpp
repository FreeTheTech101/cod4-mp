#include "stdafx.h"

struct ltnSettings_s
{
	bool bDebug;
	bool bOnline;
	bool bWindowedMode;
} ltnSettings;

void LTN_InitSettings()
{
	PCHAR szCmdLine = GetCommandLineA();
	memset(&ltnSettings, NULL, sizeof(struct ltnSettings_s));
	
	// Parse the command line
	while (*szCmdLine)
	{
		if (*szCmdLine == '-' || *szCmdLine == '/')
		{
			szCmdLine++;

			switch (*szCmdLine)
			{
			case 'd':
			case 'D':
				ltnSettings.bDebug = true;
				break;

			case 'o':
			case 'O':
				ltnSettings.bOnline = true;
				break;

			case 'w':
			case 'W':
				ltnSettings.bWindowedMode = true;
				break;
			}
		}

		szCmdLine++;
	}
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		// Disable thread calls
		DisableThreadLibraryCalls(hInst);

		if (!AllocConsole())
		{
			MessageBoxA(NULL, "LTN-#0002: Unable to allocate console.", "Error", MB_OK | MB_ICONERROR);
			_exit(0xBABE0002);
		}
		
		freopen("CON", "w", stdout);

		// Set default settings
		ltnSettings.bDebug = false;
		ltnSettings.bOnline = true;
		ltnSettings.bWindowedMode = true;

		// Now initialize settings
		LTN_InitSettings();

		COffsets::Initialize();

		CGame* pGame = new CGame();
		pGame->StartGame();

		break;
	}

	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}