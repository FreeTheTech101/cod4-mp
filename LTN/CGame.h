// ================== CoD4: Multiplayer - http://github.com/vorhon/cod4-mp/ ==================
//
// File:		CGame.h
// Description:		The game stuff.
// Start date:		July 30th, 2014
//
// Author(s):		vorhon (vorhon@outlook.com)
//
// =========================================================================================

#ifndef __CGAME_H__
#define __CGAME_H__


class CGame
{
public:
	static void PreInitialization(void);
	void StartGame();
	void UnprotectMemory();

	static void SpawnBots(int n);
	static void Printf(int level, const char* fmt, ...);
	static void PrintWarning(int level, const char* fmt, ...);
};


#endif /* __CGAME_H__ */