#include "pch.h"
#include "CMuzzleScript.h"
#include "CBulletScript.h"

CMuzzleScript::CMuzzleScript()
	: CScript((UINT)SCRIPT_TYPE::MUZZLESCRIPT)
{
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vMuzzlePos, "Pos");
}

CMuzzleScript::~CMuzzleScript()
{
}

void CMuzzleScript::begin()
{

}

void CMuzzleScript::tick()
{
	m_vMuzzlePos = Transform()->GetWorldPos();
}

void CMuzzleScript::CreateBullet()
{
	CGameObject* pParticle = new CGameObject;
	pParticle->SetName(L"Bullet");

	pParticle->AddComponent(new CTransform);
	pParticle->AddComponent(new CParticleSystem);
	pParticle->AddComponent(new CCollider3D);
	pParticle->AddComponent(new CBulletScript);

	pParticle->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pParticle->Collider3D()->SetAbsolute(true);
	pParticle->Collider3D()->SetOffsetScale(Vec3(3.f, 3.f, 3.f));

	pParticle->Transform()->SetRelativeScale(Vec3(3.f, 3.f, 3.f));

	pParticle->ParticleSystem()->SetSpawnEnable(true);						// SetSpawn
	pParticle->ParticleSystem()->SetMaxParticle(600);
	pParticle->ParticleSystem()->SetSpawnRate(300);
	pParticle->ParticleSystem()->SetSpawnColor(Vec4(1.f, 1.f, 1.f, 1.f));
	pParticle->ParticleSystem()->SetSpawnScaleMin(Vec3(2.f, 2.f, 2.f));
	pParticle->ParticleSystem()->SetSpawnScaleMax(Vec3(1.f, 1.f, 1.f));
	pParticle->ParticleSystem()->SetShapeType(2);
	pParticle->ParticleSystem()->SetShapeScale(Vec3(0.1f, 0.1f, 0.1f));
	pParticle->ParticleSystem()->SetMinLifeTime(0.1f);
	pParticle->ParticleSystem()->SetMaxLifeTime(0.1f);
	pParticle->ParticleSystem()->SetColorChangeEnable(true);				// SetColor
	pParticle->ParticleSystem()->SetStartColor(Vec4(1.f, 1.f, 0.f, 1.f));
	pParticle->ParticleSystem()->SetEndColor(Vec4(1.f, 0.1f, 0.f, 0.f));
	pParticle->ParticleSystem()->SetAddVelocityEnable(true);				// AddVelocity
	pParticle->ParticleSystem()->SetAddVelocityType(2);
	pParticle->ParticleSystem()->SetSpeed(0.f);
	pParticle->ParticleSystem()->SetDragEnable(false);						// SetDrag
	pParticle->ParticleSystem()->SetRenderEnable(false);					// Render

	SpawnGameObject(pParticle, m_vMuzzlePos, 4);
}