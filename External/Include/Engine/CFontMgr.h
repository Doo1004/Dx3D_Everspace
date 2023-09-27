#pragma once
#include "CSingleton.h"
#include "CFont.h"

#include <FontEngine/FW1FontWrapper.h>
#include <FontEngine/FW1CompileSettings.h>

#ifdef _DEBUG
#pragma comment(lib, "FontEngine/FW1FontWrapper_debug")
#else
#pragma comment(lib, "FontEngine/FW1FontWrapper"))
#endif


#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24 ) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)

class CFontMgr
	: public CSingleton<CFontMgr>
{
private:
	vector<CFont*>		m_vFonts;

private:
	IFW1Factory* m_pFW1Factory;
	IFW1FontWrapper* m_pFontWrapper;

public:
	void init();
	void render();
	void DrawFont(const wchar_t* _pStr, float _fPosX, float _fPosY, float _fFontSize, UINT _Color);
	void AddFont(CFont* pFont) { m_vFonts.push_back(pFont); }
	//void RemoveFont(CFont* font) { m_vFonts.erase(remove(m_vFonts.begin(), m_vFonts.end(), font), m_vFonts.end()); }
	void RemoveFont(CFont* font)
	{
		vector<CFont*>::iterator iter = m_vFonts.begin();
		while (iter != m_vFonts.end())
		{
			if (font == *iter)
				iter = m_vFonts.erase(iter);
			else
				++iter;
		}
	}


public:
	CFontMgr();
	~CFontMgr();
};
