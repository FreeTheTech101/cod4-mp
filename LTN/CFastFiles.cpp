// ================== CoD4: Multiplayer - http://github.com/vorhon/cod4-mp/ ==================
//
// File:		CFastFiles.cpp
// Description:		Loads custom fastfiles.
// Start date:		July 30th, 2014
//
// Author(s):		vorhon (vorhon@outlook.com)
//
// =========================================================================================

#include "stdafx.h"

// THIS IS JUST MY FIRST ATTEMPT.

typedef struct fastfiles_s
{
	__int32		unknown1;
	__int32		unknown2;
	__int32		unknown3;
	__int32		unknown4;
	__int32		unknown5;
	__int32		unknown6;
	const char* fastfile_a;
	const char* fastfile_b;
	const char* fastfile_c;
	const char* fastfile_d;
	const char* fastfile_e;
	const char* fastfile_f; // our extra fastfile
	__int32		unknown7;
} fastfiles_t;

void InitRenderer()
{
	CGame::Printf(14, "----- Initializing Renderer ----\n");

	static fastfiles_t ff;

	ff.unknown1 = 1;
	ff.unknown2 = 1024;
	ff.unknown3 = 1023;
	ff.unknown4 = 1022;
	ff.unknown5 = 6;
	ff.unknown6 = 20;

	ff.fastfile_a = "code_post_gfx_mp";
	ff.fastfile_b = "ui_mp";
	ff.fastfile_c = "common_mp";
	ff.fastfile_d = "localized_code_post_gfx_mp";
	ff.fastfile_e = "localized_common_mp";
	ff.fastfile_f = "m27";

	ff.unknown7 = ((bool(*)())0x48BA10)() != false ? *(int*)0x6D0EC8 : false;

	fastfiles_s fastfiles = *(fastfiles_s*)0xCC9D110;

	memcpy(&fastfiles, &ff, sizeof(ff));

	((void(*)())0x5F55E0)();
	((void(*)(int, void*, int))0x56C900)(0, (void*)0x1435D48, 0);
}

const char* GetFastfileDirectory(int unk, const char* fastfile)
{
	printf("%s\n", fastfile);
	return "";
}

void CFastFiles::StartHook()
{
	//DetourFunction((PBYTE)0x489F20, (PBYTE)GetFastfileDirectory, 5);
	//DetourFunction((PBYTE)0x46CCB0, (PBYTE)InitRenderer, 5);
}