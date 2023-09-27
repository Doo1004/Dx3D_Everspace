#include "pch.h"
#include "CSkyBox.h"

#include "CResMgr.h"
#include "CTransform.h"

CSkyBox::CSkyBox()
	: CRenderComponent(COMPONENT_TYPE::SKYBOX)
	, m_Type(SKYBOX_TYPE::SPHERE)
{	
	SetType(m_Type);
	SetFrustumCheck(false);
}

CSkyBox::~CSkyBox()
{
}

void CSkyBox::finaltick()
{

}

void CSkyBox::render()
{
	if (nullptr == GetMesh() || nullptr == GetMaterial(0))
		return;

	Transform()->UpdateData();


	if (SKYBOX_TYPE::SPHERE == m_Type)
	{
		GetMaterial(0)->SetTexParam(TEX_0, m_SkyTex);
	}
	else if (SKYBOX_TYPE::CUBE == m_Type)
	{
		GetMaterial(0)->SetTexParam(TEX_CUBE_0, m_SkyTex);
	}

	GetMaterial(0)->UpdateData();

	GetMesh()->render(0);
}

void CSkyBox::SetType(SKYBOX_TYPE _Type)
{
	m_Type = _Type;

	if (SKYBOX_TYPE::SPHERE == _Type)
	{
		SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));	
	}

	else if (SKYBOX_TYPE::CUBE == m_Type)
	{
		SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));				
	}

	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkyBoxMtrl"), 0);
	GetMaterial(0)->SetScalarParam(INT_0, &m_Type);
}

void CSkyBox::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_Type, sizeof(UINT), 1, _File);
	SaveResRef(m_SkyTex.Get(), _File);
}

void CSkyBox::LoadFromLevelFile(FILE* _File)
{
	fread(&m_Type, sizeof(UINT), 1, _File);
	SetType(m_Type);

	LoadResRef(m_SkyTex, _File);
	SetSkyTexture(m_SkyTex);
}
