#include "pch.h"
#include "CBulletScript.h"
#include "CPlayerScript.h"


CBulletScript::CBulletScript()
	: CScript((UINT)SCRIPT_TYPE::BULLETSCRIPT)
{
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vBulletDir, "Dir");
}

CBulletScript::~CBulletScript()
{
}

void CBulletScript::begin()
{
	if (GetOwner()->GetName() == L"Bullet")
	{
		GetPlayerData();
		m_vAxis = m_PlayerScript->GetAxis();		// 총알이 생성될 때 한 번만 방향을 얻어옴
	}
}

void CBulletScript::tick()
{
	// 0 0 0 일 때 Dir = 0 0 1
	m_vCurPos = Transform()->GetRelativePos();

	if (GetOwner()->GetName() == L"Bullet")
	{
		Vec3 vCurRot = m_PlayerObject->Transform()->GetRelativeRot();
		//=================================BulletMove

		m_fBulletSpeed = 0.f;

		if (!m_bBulletHit)			// 총알이 충돌하지 않았을 때
			m_fBulletSpeed += DT * 1500.f;

		else if (m_bBulletHit)
			m_fBulletSpeed = 0.f;

		//Vec3 vFinalPos = m_vCurPos + Vec3(m_fBulletSpeed, m_fBulletSpeed, m_fBulletSpeed) * m_vAxis;
		Vec3 vFinalPos = m_vCurPos + m_vAxis * m_fBulletSpeed;
		Vec3 vFinalRot = ConvertToRadians(vCurRot);

		Transform()->SetRelativePos(vFinalPos);
		Transform()->SetRelativeRot(vFinalRot);

		//=================================LifeTime
		SetLifeSpan(1.f);
	}
	else if (GetOwner()->GetName() == L"Bullet_UFO2")
	{
		if (!m_bBulletHit)
		{
			Vec3 vMovePos = m_vBulletDir * 600.f * DT;
			m_vCurPos += vMovePos;
			Transform()->SetRelativePos(m_vCurPos);
			m_vCurBulletPos = m_vCurPos;
		}
		else
		{
			Transform()->SetRelativePos(m_vCurBulletPos);
			SetLifeSpan(0.2f);
		}

	}
	else if (GetOwner()->GetName() == L"Bullet_BOSS")
	{
		if (!m_bBulletHit)
		{
			Vec3 vMovePos = m_vBulletDir * 1000.f * DT;
			m_vCurPos += vMovePos;
			Transform()->SetRelativePos(m_vCurPos);
			m_vCurBulletPos = m_vCurPos;
		}
		else
		{
			Transform()->SetRelativePos(m_vCurBulletPos);
			SetLifeSpan(0.2f);
		}
	}
}

void CBulletScript::BeginOverlap(CCollider3D* _Other)
{
	if (GetOwner()->GetName() == L"Bullet")
	{	
		// 총알이 부딪치게 되면 총알의 속도가 멈추고, 피격 이펙트를 연출하고, 0.2초의 시간 이후 Destroy
		m_bBulletHit = true;
		SetLifeSpan(0.2f);
		//int iSpawnRate = ParticleSystem()->GetSpawnRate();

		ParticleSystem()->SetMinLifeTime(0.2f);
		ParticleSystem()->SetMaxLifeTime(0.2f);
		//ParticleSystem()->SetSpawnRate();
		ParticleSystem()->SetAddVelocityType(0);
	}
	else
	{
		m_bBulletHit = true;

		Vec3 vScale = ParticleSystem()->GetSpawnScaleMax();
		ParticleSystem()->SetSpeed(100.f);
		ParticleSystem()->SetMinLifeTime(0.5f);
		ParticleSystem()->SetMaxLifeTime(0.5f);
		ParticleSystem()->SetAddVelocityType(0);
		ParticleSystem()->SetSpawnScaleMin(vScale / 3);
		ParticleSystem()->SetSpawnScaleMax(vScale / 3);
	}


}

void CBulletScript::GetPlayerData()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

	vector<CGameObject*> vecObject = CurLevel->GetLayer(1)->GetParentObject();
	if (vecObject.size() != 0)
	{
		m_PlayerObject = vecObject[0];
		m_PlayerScript = m_PlayerObject->GetScript<CPlayerScript>();
	}
}

