// ================== CoD4: Multiplayer - http://github.com/vorhon/cod4-mp/ ==================
//
// File:		CUIStrings.cpp
// Description:		Custom UI localized strings.
// Start date:		July 30th, 2014
//
// Author(s):		vorhon (vorhon@outlook.com)
//
// =========================================================================================

#include "stdafx.h"

CUIStrings* CUIStrings::m_pInstance;
std::map<const char*, const char*> CUIStrings::m_UIStrings;

const char*(*orig_UI_SafeTranslateString)(const char*);

// -------------------------------------------------

CUIStrings::CUIStrings()
{
	m_pInstance = this;
}

// -------------------------------------------------

bool CUIStrings::FindTranslation(const char* key)
{
	return m_UIStrings.find(key) != m_UIStrings.end();
}

// -------------------------------------------------

bool CUIStrings::FindTranslation(const char* key, m_UIStringsItr* out_itr)
{
	return (*out_itr = m_UIStrings.find(key)) != m_UIStrings.end();
}

// -------------------------------------------------

bool CUIStrings::AddTranslation(const char* key, const char* value)
{
	if (FindTranslation(key))
	{
		CGame::PrintWarning(14, "Translation for '%s' already existed.\n", key);
		return false;
	}

	m_UIStrings.insert(std::make_pair(key, value));

	CGame::Printf(NULL, "Added UI string { key: \"%s\"; value: \"%s\" }.\n",
		key, value);

	return true;
}

// -------------------------------------------------

bool CUIStrings::RemoveTranslation(const char* key)
{
	m_UIStringsItr itr;

	if (FindTranslation(key, &itr))
	{
		m_UIStrings.erase(itr);

		CGame::Printf(NULL, "Removed UI string { key: \"%s\"; last value: \"%s\" }.\n", 
			key, itr->second);

		return true;
	}

	CGame::PrintWarning(14, "UI string \"%s\" does not exist in our list of custom UI strings, and thus cannot be removed.\n", key);

	return true;
}

// -------------------------------------------------

const char* CUIStrings::UI_SafeTranslateString_Hook(const char* key)
{
	if (strstr(GetCommandLineA(), "-uidebug"))
	{
		return key;
	}

	m_UIStringsItr itr;

	for (itr = m_pInstance->m_UIStrings.begin();
		itr != m_pInstance->m_UIStrings.end(); itr++)
	{
		if (strcmp(itr->first, key) == NULL)
		{
			return itr->second;
		}
	}

	return orig_UI_SafeTranslateString(key);
}

// -------------------------------------------------

__declspec(naked) void UI_SafeTranslateString_Stub()
{
	__asm
	{
		push eax;
		call CUIStrings::UI_SafeTranslateString_Hook;
		add esp, 4h;

		test al, al;
		retn;
	}
}

// -------------------------------------------------

void CUIStrings::StartHook()
{
	DWORD dwFunc = COffsets::FUNC_UI_SafeTranslateString;

	// Hooks our custom function in there
	orig_UI_SafeTranslateString = (const char*(*)(const char*))
		DetourFunction((PBYTE)dwFunc, (PBYTE)UI_SafeTranslateString_Stub, 5);
}

// -------------------------------------------------