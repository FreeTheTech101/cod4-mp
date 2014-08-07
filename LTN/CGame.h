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