#ifndef __CUISTRINGS_H__
#define __CUISTRINGS_H__


class CUIStrings
{
private:
	static CUIStrings* m_pInstance;

	static std::map<const char*, const char*> m_UIStrings;
	typedef std::map<const char*, const char*>::iterator m_UIStringsItr;

public:
	CUIStrings();

	bool FindTranslation(const char* key);
	bool FindTranslation(const char* key, m_UIStringsItr* out_itr);
	bool AddTranslation(const char* key, const char* value);
	bool RemoveTranslation(const char* key);
	
	static const char* UI_SafeTranslateString_Hook(const char* key);

	void StartHook();
};


#endif /* __CUISTRINGS_H__ */