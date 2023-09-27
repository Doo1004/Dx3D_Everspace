#include "pch.h"
#include "CFont.h"
#include "CFontMgr.h"

#include "CScript.h"
#include "components.h"


CFont::CFont()
	: CRenderComponent(COMPONENT_TYPE::FONT)
	, m_bInputData(false)
	, m_vPos(0.f, 0.f)
	, m_vColor(255.f, 255.f, 255.f, 255.f)
	, m_fScale(10.f)
	, m_fDT(0.f)
{
	SetName(L"Font");
	CFontMgr::GetInst()->AddFont(this);

}

CFont::~CFont()
{
	CFontMgr::GetInst()->RemoveFont(this);
}

void CFont::finaltick()
{
}

void CFont::tick()
{
	m_fDT += DT;
}

void CFont::render()
{	
	//Transform()->UpdateData(); 여기선 딱히 필요 없을 듯
	wchar_t szBuff[256] = {};

	if (m_wString.size() >= 256)
		return;

	if(m_bInputData)
		swprintf_s(szBuff, m_wString.c_str(), m_fData);
	else if(!m_bInputData)
		wcsncpy_s(szBuff, m_wString.c_str(), m_wString.size());

	CFontMgr::GetInst()->DrawFont(szBuff, m_vPos.x, m_vPos.y, m_fScale, FONT_RGBA(m_vColor.x, m_vColor.y, m_vColor.z, m_vColor.w));
}

void CFont::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_wString, sizeof(wstring), 1, _File);
	fwrite(&m_vColor, sizeof(Vec4), 1, _File);
	fwrite(&m_vPos, sizeof(Vec2), 1, _File);
	fwrite(&m_fScale, sizeof(float), 1, _File);
}

void CFont::LoadFromLevelFile(FILE* _File)
{
	fread(&m_wString, sizeof(wstring), 1, _File);
	fread(&m_vColor, sizeof(Vec4), 1, _File);
	fread(&m_vPos, sizeof(Vec2), 1, _File);
	fread(&m_fScale, sizeof(float), 1, _File);
}