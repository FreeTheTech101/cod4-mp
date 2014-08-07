// ================== CoD4: Multiplayer - http://github.com/vorhon/cod4-mp/ ==================
//
// File:		CUIStrings.cpp
// Description:		Custom UI EXE localized strings.
// Start date:		July 30th, 2014
//
// Author(s):		vorhon (vorhon@outlook.com)
//
// =========================================================================================

#include "stdafx.h"

CUIStringsSEH* CUIStringsSEH::m_pInstance;
std::map<const char*, const char*> CUIStringsSEH::m_UIStringsSEH;

DWORD orig_SEH_SafeTranslateString = 0x538B65;

// -------------------------------------------------

CUIStringsSEH::CUIStringsSEH()
{
	m_pInstance = this;
}

// -------------------------------------------------

bool CUIStringsSEH::FindTranslation(const char* key)
{
	return m_UIStringsSEH.find(key) != m_UIStringsSEH.end();
}

// -------------------------------------------------

bool CUIStringsSEH::FindTranslation(const char* key, m_UIStringsSEHItr* out_itr)
{
	return (*out_itr = m_UIStringsSEH.find(key)) != m_UIStringsSEH.end();
}

// -------------------------------------------------

bool CUIStringsSEH::AddTranslation(const char* key, const char* value)
{
	if (FindTranslation(key))
	{
		CGame::PrintWarning(14, "Translation for '%s' already existed.\n", key);
		return false;
	}

	m_UIStringsSEH.insert(std::make_pair(key, value));

	CGame::Printf(NULL, "Added UI SEH string { key: \"%s\"; value: \"%s\" }.\n",
		key, value);

	return true;
}

// -------------------------------------------------

bool CUIStringsSEH::RemoveTranslation(const char* key)
{
	m_UIStringsSEHItr itr;

	if (FindTranslation(key, &itr))
	{
		m_UIStringsSEH.erase(itr);

		CGame::Printf(NULL, "Removed UI SEH string { key: \"%s\"; last value: \"%s\" }.\n",
			key, itr->second);

		return true;
	}

	CGame::PrintWarning(14, "UI SEH string \"%s\" does not exist in our list of custom UI strings, and thus cannot be removed.\n", key);

	return true;
}

// -------------------------------------------------

const char* CUIStringsSEH::SEH_SafeTranslateString_Hook(const char* pszReference)
{
	if (strstr(GetCommandLineA(), "-uidebug"))
	{
		return pszReference;
	}

	m_UIStringsSEHItr itr;

	for (itr = m_pInstance->m_UIStringsSEH.begin();
		itr != m_pInstance->m_UIStringsSEH.end(); itr++)
	{
		if (strcmp(itr->first, pszReference) == NULL)
		{
			return itr->second;
		}
	}

	return NULL;
}

// -------------------------------------------------

__declspec(naked) void SEH_SafeTranslateString_Stub()
{
	__asm
	{
		push esi;
		call CUIStringsSEH::SEH_SafeTranslateString_Hook;
		add esp, 4h;

		test eax, eax;
		jz jumpBack;

		retn;

	jumpBack:
		mov eax, dword ptr[0xCAE4C34];
		jmp orig_SEH_SafeTranslateString;
	}
}

// -------------------------------------------------

void CUIStringsSEH::StartHook()
{
	DetourFunction((PBYTE)0x538B60, (PBYTE)SEH_SafeTranslateString_Stub, 5);
}

// -------------------------------------------------