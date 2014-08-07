// ================== CoD4: Multiplayer - http://github.com/vorhon/cod4-mp/ ==================
//
// File:		CConsole.cpp
// Description:		Unlocks & fixes the console and makes it customizable.
// Start date:		July 30th, 2014
//
// Author(s):		vorhon (vorhon@outlook.com)
//
// =========================================================================================

#include "stdafx.h"
#include <process.h>

CConsole* CConsole::m_pInstance;

// -------------------------------------------------

CConsole::CConsole()
{
	m_pInstance = this;
	m_bRunning = false;
	m_bStopProcess = false;
}

// -------------------------------------------------

bool CConsole::Wait()
{
	return m_bRunning;
}

// -------------------------------------------------

void CConsole::Process(LPVOID lpParam)
{
	MSG Msg;
	DWORD dwFunc = (DWORD)lpParam;
	
	assert(dwFunc);

	__asm call dwFunc;

	while (true)
	{
		if (m_pInstance->m_bStopProcess)
		{
			m_pInstance->m_bRunning = false;
			_endthread();
		}

		if (GetMessageA(&Msg, NULL, NULL, NULL))
		{
			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
		}

		m_pInstance->m_bRunning = true;
	}
}

// -------------------------------------------------

void CConsole::CreateConsole()
{
	DWORD dwFunc = COffsets::FUNC_Sys_CreateConsole;

	m_bStopProcess = false;
	_beginthread(CConsole::Process, NULL, (LPVOID)dwFunc);
}

// -------------------------------------------------

const char* CConsole::GetConsoleInput_Hook(const char* input)
{
	char* input_backup = new char[strlen(input)];
	strcpy(input_backup, input);

	// If there's no '\n' then add one
	if (input[strlen(input) - 1] != '\n')
	{
		strcat((char*)input, "\n");
	}

	// Finally print it
	CGame::Printf(NULL, "]%s", input);

	return input_backup;
}

// -------------------------------------------------

__declspec(naked) void GetConsoleInput_Stub()
{
	__asm
	{
		mov eax, dword ptr[0xCC1B1AC];
		push eax;
		call CConsole::GetConsoleInput_Hook;
		add esp, 4h;

		test eax, eax;
		retn;
	}
}

// -------------------------------------------------

void CConsole::StartHook()
{
	// Hack to make console output the user's input
	DetourFunction((PBYTE)COffsets::FUNC_GetConsoleInput, (PBYTE)GetConsoleInput_Stub, 5);

	// Make console closable even if not a dedicated server
	*(WORD*)COffsets::JZ_ConsolePostQuit_1 = 0x9090;
	*(WORD*)COffsets::JZ_ConsolePostQuit_2 = 0x9090;
}

// -------------------------------------------------

void CConsole::SetLoadImage(const char* image)
{
	strcpy((char*)COffsets::VAR_ConsoleLoadImage, image);
}

// -------------------------------------------------

void CConsole::SetFontName(const char* fontName)
{
	strcpy((char*)COffsets::VAR_ConsoleFontName, fontName);
}

// -------------------------------------------------

void CConsole::ToggleItalic()
{
	m_bItalicEnabled = !m_bItalicEnabled;

	*(char *)COffsets::VAR_ConsoleItalic = (char)m_bItalicEnabled;
}

// -------------------------------------------------

void CConsole::ToggleUnderline()
{
	m_bUnderlineEnabled = !m_bUnderlineEnabled;

	*(char *)COffsets::VAR_ConsoleUnderline = (char)m_bUnderlineEnabled;
}

// -------------------------------------------------
