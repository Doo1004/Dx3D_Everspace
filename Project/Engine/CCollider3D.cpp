#include "pch.h"
#include "CCollider3D.h"

#include "CScript.h"
#include "components.h"

CCollider3D::CCollider3D()
	: CComponent(COMPONENT_TYPE::COLLIDER3D)
	, m_Shape(COLLIDER3D_TYPE::CUBE)
	, m_bAbsolute(false)
	, m_iCollisionCount(0)
{
	SetName(L"Collider3D");
}

CCollider3D::~CCollider3D()
{
}

void CCollider3D::finaltick()
{
	// 충돌 회수가 음수인 경우
	assert(0 <= m_iCollisionCount);

	m_matCollider3D = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
	m_matCollider3D *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);

	const Matrix& matWorld = Transform()->GetWorldMat();

	if (m_bAbsolute)
	{
		Matrix matParentScaleInv = XMMatrixInverse(nullptr, Transform()->GetWorldScaleMat());
		m_matCollider3D = m_matCollider3D * matParentScaleInv * matWorld;
	}
	else
	{
		// 충돌체 월드 * 오브젝트 월드
		m_matCollider3D *= matWorld;
	}

	// DebugShape 요청
	Vec4 vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	if (0 < m_iCollisionCount)
		vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	if (m_bShowColliderShape)
	{
		if (COLLIDER3D_TYPE::SPHERE == m_Shape)
			DrawDebugSphere(m_matCollider3D, vColor, 0.f);
		else
			DrawDebugCube(m_matCollider3D, vColor, 0.f);
	}
}

void CCollider3D::BeginOverlap(CCollider3D* _Other)
{
	m_iCollisionCount += 1;

	// Script 호출
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->BeginOverlap(_Other);
	}
}

void CCollider3D::OnOverlap(CCollider3D* _Other)
{
	// Script 호출
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->OnOverlap(_Other);
	}
}

void CCollider3D::EndOverlap(CCollider3D* _Other)
{
	m_iCollisionCount -= 1;

	// Script 호출
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->EndOverlap(_Other);
	}
}

void CCollider3D::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fwrite(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fwrite(&m_bAbsolute, sizeof(bool), 1, _File);
	fwrite(&m_Shape, sizeof(UINT), 1, _File);
}

void CCollider3D::LoadFromLevelFile(FILE* _File)
{
	fread(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fread(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fread(&m_bAbsolute, sizeof(bool), 1, _File);
	fread(&m_Shape, sizeof(UINT), 1, _File);
}

//void CCollider3D::AddCollider3D(const Matrix& _Collider3D)
//{
//	m_vecCollider3D.push_back(_Collider3D);
//}
//
//void CCollider3D::DelCollider3D(int _Index)
//{
//	if (_Index >= 0 && _Index < m_vecCollider3D.size())
//		m_vecCollider3D.erase(m_vecCollider3D.begin() + _Index);
//}
