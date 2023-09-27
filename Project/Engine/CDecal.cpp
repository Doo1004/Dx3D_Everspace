#include "pch.h"
#include "CDecal.h"

#include "CTransform.h"
#include "CResMgr.h"

CDecal::CDecal()
	: CRenderComponent(COMPONENT_TYPE::DECAL)
	, m_Light(0)
{
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DecalMtrl"), 0);
	m_DecalMtrl = GetMaterial(0);
}

CDecal::~CDecal()
{
}

void CDecal::finaltick()
{
	const Matrix& matWorld = Transform()->GetWorldMat();

	if (m_DebugShapeEnable)
		DrawDebugCube(matWorld, Vec4(0.f, 1.f, 0.f, 1.f), 0.f);
}

void CDecal::render()
{
	Transform()->UpdateData();

	GetMaterial(0)->SetScalarParam(INT_0, &m_Light);
	GetMaterial(0)->SetScalarParam(INT_1, &m_DebugColorEnable);
	GetMaterial(0)->SetScalarParam(VEC4_0, &m_DecalColor);
	GetMaterial(0)->SetTexParam(TEX_0, m_DecalTex);
	GetMaterial(0)->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"PositionTargetTex"));
	GetMaterial(0)->UpdateData();

	GetMesh()->render(0);
}

void CDecal::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_Light, sizeof(UINT), 1, _File);
	fwrite(&m_DecalColor, sizeof(Vec4), 1, _File);

	SaveResRef(m_DecalTex.Get(), _File);
}

void CDecal::LoadFromLevelFile(FILE* _File)
{
	fread(&m_Light, sizeof(UINT), 1, _File);
	fread(&m_DecalColor, sizeof(Vec4), 1, _File);

	LoadResRef(m_DecalTex, _File);
	SetOutputTexture(m_DecalTex);
}
