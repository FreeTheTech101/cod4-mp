#ifndef __CCONSOLE_H__
#define __CCONSOLE_H__


class CConsole
{
private:
	bool m_bItalicEnabled;
	bool m_bUnderlineEnabled;
	bool m_bStopProcess;
	bool m_bRunning;

	static CConsole* m_pInstance;

public:
	static void Process(LPVOID lpParam);
	static const char* GetConsoleInput_Hook(const char* input);

	CConsole();
	bool Wait();

	void CreateConsole();
	void StartHook();

	void SetLoadImage(const char* image);
	void SetFontName(const char* fontName);
	void ToggleItalic();
	void ToggleUnderline();
};


#endif /* __CCONSOLE_H__ */