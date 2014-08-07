#ifndef __CUISTRINGSSEH_H__
#define __CUISTRINGSSEH_H__


class CUIStringsSEH
{
private:
	static CUIStringsSEH* m_pInstance;

	static std::map<const char*, const char*> m_UIStringsSEH;
	typedef std::map<const char*, const char*>::iterator m_UIStringsSEHItr;

public:
	CUIStringsSEH();

	bool FindTranslation(const char* key);
	bool FindTranslation(const char* key, m_UIStringsSEHItr* out_itr);
	bool AddTranslation(const char* key, const char* value);
	bool RemoveTranslation(const char* key);

	static const char* SEH_SafeTranslateString_Hook(const char* key);

	void StartHook();
};


#endif /* __CUISTRINGSSEH_H__ */