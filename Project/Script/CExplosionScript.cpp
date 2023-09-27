#include "pch.h"
#include "CExplosionScript.h"
#include <Engine\CSound.h>

CExplosionScript::CExplosionScript()
	: CScript((UINT)SCRIPT_TYPE::EXPLOSIONSCRIPT)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fMaxLifeTime, "MaxLifeTime");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fCurLifeTime, "CurLifeTime");
}

CExplosionScript::~CExplosionScript()
{
}
void CExplosionScript::begin()
{
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\Explosion.mp3");
	pSound->Play(1, 1 - m_fDistance / 1400, true);
}
void CExplosionScript::tick()
{
	SetParticle();
	SetLight();	

	m_iSpawnRate = (int)((1 - (m_fCurLifeTime / m_fMaxLifeTime)) * (m_fScale / 2));

	ParticleSystem()->SetSpawnRate(m_iSpawnRate);

	m_fCurLifeTime += DT;
	if (m_fCurLifeTime >= m_fMaxLifeTime * 1.5f)			// 폭파 파티클이 자연스럽게 사라질 수 있도록 라이프타임에 여유를 줌
		Destroy();
}

void CExplosionScript::SetParticle()
{
	Vec3 vParticleScale = Vec3(m_fScale, m_fScale, m_fScale);
	float fScaleMax = m_fScale * 0.3f;
	float fScaleMin = m_fScale * 0.05f;

	ParticleSystem()->SetSpawnEnable(true);					// SetSpawn
	ParticleSystem()->SetMaxParticle(m_fScale);
	ParticleSystem()->SetSpawnRate(m_iSpawnRate);
	ParticleSystem()->SetSpawnColor(Vec4(1.f, 1.f, 1.f, 1.f));
	ParticleSystem()->SetSpawnScaleMin(Vec3(fScaleMax, fScaleMax, fScaleMax));
	ParticleSystem()->SetSpawnScaleMax(Vec3(fScaleMin, fScaleMin, fScaleMin));
	ParticleSystem()->SetShapeType(2);						// Cube
	ParticleSystem()->SetShapeScale(vParticleScale);
	ParticleSystem()->SetMinLifeTime(1.f);
	ParticleSystem()->SetMaxLifeTime(1.f);
	ParticleSystem()->SetColorChangeEnable(true);			// SetColor
	ParticleSystem()->SetStartColor(Vec4(1.f, 1.f, 0.f, 1.f));
	ParticleSystem()->SetEndColor(Vec4(1.f, 0.1f, 0.f, 0.f));
	ParticleSystem()->SetAddVelocityEnable(true);			// AddVelocity
	ParticleSystem()->SetAddVelocityType(0);
	ParticleSystem()->SetSpeed(60.f);
	ParticleSystem()->SetDragEnable(false);					// SetDrag
	ParticleSystem()->SetNoiseForceEnable(false);			// NoiseForce
	//ParticleSystem()->SetNoiseForce(100.f);
	//ParticleSystem()->SetNoiseTerm(0.1f);
	ParticleSystem()->SetRenderEnable(true);				// Render
	ParticleSystem()->SetVelocityAlignment(true);
	ParticleSystem()->SetScaleChangeEnable(true);
}

void CExplosionScript::SetLight()
{
	Light3D()->SetLightType(LIGHT_TYPE::POINT);
	Light3D()->SetRadius(m_iSpawnRate * 7);
	Light3D()->SetLightDiffuse(Vec3(1, 0, 0));
	Light3D()->SetLightSpecular(Vec3(1, 0.5, 0));
	Light3D()->SetLightAmbient(Vec3(1, 0, 0));
}
