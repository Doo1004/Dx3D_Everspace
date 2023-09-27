#include "pch.h"
#include "CMonsterScript.h"
#include "CExplosionScript.h"
#include "CBulletScript.h"
#include "CHPBarScript.h"
#include <Engine\CSound.h>


CMonsterScript::CMonsterScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
	, m_iHP(100)
	, m_iMaxHP(100)
	, m_fAttackDelayDT(0.f)
	//, m_iYdir(1)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iHP, "HP");
	AddScriptParam(SCRIPT_PARAM::BOOL, &m_eStatus, "Attack");
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRandomAttack, "RandomAttack");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fAttackDT, "AttackDT");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fHPRatio, "HPRatio");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fVolume, "Volume");

	srand(time(NULL));
}

CMonsterScript::~CMonsterScript()
{
	if (m_pMark && m_pMarkDecal)
	{
		DestroyObject(m_pMark);
		DestroyObject(m_pMarkDecal);
	}
	if (m_pHPGauge)
		DestroyObject(m_pHPGauge);

	if (m_pBulletParticle)
		DestroyObject(m_pBulletParticle);
}

void CMonsterScript::begin()
{
	GetObjData();			// 오브젝트와 카메라 정보 가져오기
	SetBeginData();			// 몬스터 초기 설정

	//m_fPosY = Transform()->GetRelativePos().y;

	if (GetOwner()->GetName() == L"UFO_2" || GetOwner()->GetName() == L"BOSS")
		CreateHPGauge();		// 몬스터 체력 바 생성
}

void CMonsterScript::tick()
{
	SetMonsterData();			// 몬스터 스크립트에서 사용될 기본 변수 정의

	if (GetOwner()->GetName() == L"UFO_2")
		ActiveMonster();		// 몬스터의 행동
	else if (GetOwner()->GetName() == L"BOSS")
		ActiveBossMonster();
}

void CMonsterScript::BeginOverlap(CCollider3D* _Other)
{
	m_iHP -= 10;

	if (GetOwner()->GetName() == L"UFO_2")
	{
		if (m_iHP <= 0)
		{
			CreateExplosionObj();
			m_eStatus = eSTATUS::DEAD;
			Destroy();
		}
	}
	else if (GetOwner()->GetName() == L"BOSS")
	{
		if (m_iHP <= 0)
		{
			CreateExplosionObj();
			m_eStatus = eSTATUS::DEAD;
			Destroy();
		}
	}
}

void CMonsterScript::CreateHPGauge()
{
	m_pHPGauge = new CGameObject;
	m_pHPGauge->AddComponent(new CTransform);
	m_pHPGauge->AddComponent(new CMeshRender);
	m_pHPGauge->AddComponent(new CHPBarScript);
	m_pHPGauge->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	m_pHPGauge->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\HPGauge.mtrl"), 0);

	SpawnGameObject(m_pHPGauge, Vec3(0, 0, 0), 0);
}

void CMonsterScript::CreateExplosionObj()
{
	CGameObject* pParticle = new CGameObject;
	pParticle->SetName(L"Explosion");

	pParticle->AddComponent(new CTransform);
	pParticle->AddComponent(new CParticleSystem);
	pParticle->AddComponent(new CExplosionScript);
	pParticle->AddComponent(new CLight3D);
	pParticle->GetScript<CExplosionScript>()->SetLifeTime(m_fExLifeTime);		// 1.2f
	pParticle->GetScript<CExplosionScript>()->SetScale(m_fExScale);				// 500.f
	pParticle->GetScript<CExplosionScript>()->SetPlayerDist(min(1, m_fPlayerDistance / 400));

	SpawnGameObject(pParticle, m_vCurPos, 0);
}

void CMonsterScript::SetMonsterData()
{
	if (m_eStatus != eSTATUS::DEAD)
	{
		m_vCurPos = Transform()->GetRelativePos();					// 현재 위치
		m_vPlayerPos = m_pPlayer->Transform()->GetWorldPos();		// 플레이어의 위치
		m_fPlayerDistance = CalculDist(m_vCurPos, m_vPlayerPos);	// 몬스터와 플레이어와의 거리
		m_vPlayerDir = (m_vPlayerPos - m_vCurPos).Normalize();		// 몬스터에서 플레이어까지의 방향
		m_fBulletDT = min(10.f, m_fBulletDT += DT);					// 총알 딜레이
		m_fHPRatio = (float)m_iHP / (float)m_iMaxHP;				// 몬스터 체력 비율 계산
		m_fVolume = CalculateVolume(m_fPlayerDistance, 300.0f, 1400.f);

		if (GetOwner()->GetName() == L"UFO_2" || GetOwner()->GetName() == L"BOSS")
		{
			m_pHPGauge->GetScript<CHPBarScript>()->SetHPRatio(m_fHPRatio);
			m_pHPGauge->GetScript<CHPBarScript>()->SetPos(m_vCurPos);
		}
	}
}

void CMonsterScript::ActiveBossMonster()
{
	m_pHPGauge->GetScript<CHPBarScript>()->SetBossEnable(true);

	if (m_fPlayerDistance > m_iShootDist)
		m_eStatus = eSTATUS::MOVE;
	else
		m_eStatus = eSTATUS::ATTACK;
	switch (m_eStatus)
	{
		case eSTATUS::MOVE:
		{

		}
		break;

		case eSTATUS::ATTACK:
		{
			if (!m_bAttack)
				m_iRandomAttack = rand() % 3;

			if (m_iRandomAttack == 0)			// Bullet Razer
			{
				if (m_fAttackDelayDT == 0.f)
				{
					Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\BossSkill1.mp3");
					pSound->Play(1, CalculateVolume(m_fPlayerDistance, 300.0f, 3000.f), true);
					CreateBossParticle();
				}

				m_bAttack = true;
				m_fAttackDelay = 7.f;
				m_fAttackDelayDT += DT;

				if (m_fAttackDelayDT >= 2.f)
				{
					if (m_fBulletDT >= m_fBulletDelay)
					{
						Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\BossFire.mp3");
						pSound->Play(1, CalculateVolume(m_fPlayerDistance, 300.0f, 3000.f), true);

						BulletFire((m_vPlayerPos - m_vBulletParticlePos).Normalize());
						m_fBulletDT = 0.f;
					}
				}
				m_fAttackDT += DT;
			}
			else if (m_iRandomAttack == 1)		// Bullet Pattern
			{
				if (m_fAttackDelayDT == 0.f)
				{
					Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\BossSkill1.mp3");
					pSound->Play(1, CalculateVolume(m_fPlayerDistance, 300.0f, 3000.f), true);
					CreateBossParticle();
				}

				m_bAttack = true;
				m_fAttackDelay = 7.f;
				m_fAttackDelayDT += DT;

				if (m_fAttackDelayDT >= 2.f)
				{
					// 누적 시간이 3초가 넘었는지 확인
					if (m_fAttackDelayDT >= 3.0f)
					{
						Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\BossFire.mp3");
						pSound->Play(1, CalculateVolume(m_fPlayerDistance, 300.0f, 3000.f), true);

						int iNumBullets = 16;			// 원형 패턴에 있는 총알의 수

						float angle = 0.f;				// 시작 각도
						float angleIncrement = XM_2PI / iNumBullets;

						for (int i = 0; i < iNumBullets; ++i)
						{
							float fRandomy = ((rand() % 2001) - 1000) / 1000.0f;
							Vec3 bulletDir = Vec3(cos(angle), fRandomy, sin(angle)).Normalize();
							BulletFire(bulletDir);
							angle += angleIncrement;
						}
						// 누적 시간을 1초 감소
						m_fAttackDelayDT -= 1.0f;
					}
				}
				m_fAttackDT += DT;
			}
			else if (m_iRandomAttack == 2)				// Summon
			{
				if (m_fAttackDelayDT == 0.f)
				{
					Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\BossSkill2.mp3");
					pSound->Play(1, CalculateVolume(m_fPlayerDistance, 300.0f, 3000.f), true);
					CreateBossSummonMark();
				}

				m_bAttack = true;
				m_fAttackDelay = 5.f;
				m_fAttackDelayDT += DT;

				if (m_pMark && m_pMarkDecal)				// 회전
				{
					m_fSummonMarkRot += DT * 30.f;
					m_pMark->Transform()->SetRelativeRot(ConvertToRadians(Vec3(90.f, m_fSummonMarkRot, 0.f)));
					m_pMarkDecal->Transform()->SetRelativeRot(ConvertToRadians(Vec3(0.f, -m_fSummonMarkRot, 0.f)));
				}

				if (m_fAttackDelayDT >= 2.f)
				{
					if (m_fAttackDelayDT >= 3.5f)			// 누적 시간이 3.5초가 넘었는지 확인
					{
						Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\BossSummon.mp3");
						pSound->Play(1, CalculateVolume(m_fPlayerDistance, 300.0f, 3000.f), true);
						SummonMonster();
						m_fAttackDelayDT -= 1.5f;			// 누적 시간을 1.5초 감소
					}
				}
				m_fAttackDT += DT;
			}
		}
		break;
	}

	if (m_fAttackDT >= m_fAttackDelay)
	{
		m_fAttackDT = 0.f;
		m_bAttack = false;
		m_fAttackDelayDT = 0.f;
		m_fSummonMarkRot = 0.f;
		if (m_pMark && m_pMarkDecal)
		{
			DestroyObject(m_pMark);
			DestroyObject(m_pMarkDecal);
		}
	}
}

void CMonsterScript::SummonMonster()
{
	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* pMonster = nullptr;

	pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\UFO_2.mdat");
	pMonster = pMeshData->Instantiate();
	pMonster->SetName(L"UFO_2");
	pMonster->AddComponent(new CCollider3D);
	pMonster->AddComponent(new CMonsterScript);

	pMonster->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pMonster->Collider3D()->SetAbsolute(true);
	pMonster->Collider3D()->SetOffsetPos(Vec3(-25.f, -5.f, 67.f));
	pMonster->Collider3D()->SetOffsetScale(Vec3(180.f, 40.f, 180.f));

	SpawnGameObject(pMonster, Vec3(m_pMark->Transform()->GetWorldPos()), 2);
}

void CMonsterScript::ActiveMonster()
{
	Transform()->SetQuaternionRotY(0.f);
	m_pHPGauge->GetScript<CHPBarScript>()->SetBossEnable(false);

	if (m_fPlayerDistance > m_iShootDist && !m_bRandomMove)
		m_eStatus = eSTATUS::MOVE;
	else
		m_eStatus = eSTATUS::ATTACK;

	switch (m_eStatus)
	{
		case eSTATUS::MOVE:
		{
			Transform()->SetQuaternionRotY(0.005f);
			Vec3 vMovePos = m_vPlayerDir * m_fSpeed * DT;
			m_vCurPos += vMovePos;
			Transform()->SetRelativePos(m_vCurPos);
		}
			break;

		case eSTATUS::ATTACK:
		{
			if (m_fMoveDT < 1.5f && m_bIncreaseCoolTime)
			{
				if (!m_bRandomMove)
				{
					float fRandomx = ((rand() % 2001) - 1000) / 1000.0f;
					float fRandomy = ((rand() % 2001) - 1000) / 1000.0f;
					float fRandomz = ((rand() % 2001) - 1000) / 1000.0f;

					m_vRandomDir = Vec3(fRandomx, fRandomy, fRandomz);
					m_bRandomMove = true;
				}

				Transform()->SetQuaternionRotY(0.005f);
				Vec3 vMovePos = m_vRandomDir * m_fSpeed * DT;
				m_vCurPos += vMovePos;
				Transform()->SetRelativePos(m_vCurPos);

				m_fMoveDT += DT;

				if (m_fMoveDT >= 1.5f)
					m_bIncreaseCoolTime = false;
			}
			else
			{
				m_fMoveDT -= DT;
				m_bRandomMove = false;

				if (m_fMoveDT <= 0.f)
				{
					m_fMoveDT = 0.0f;
					m_bIncreaseCoolTime = true;
				}
			}

			if (m_fBulletDT >= m_fBulletDelay && !m_bRandomMove)
			{
				Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\MonsterFire.mp3");
				pSound->Play(1, m_fVolume * 0.5, true);
				BulletFire((m_vPlayerPos - m_vMobBulletPos).Normalize());
				m_fBulletDT = 0.f;
			}
		}
			break;
	}
}

void CMonsterScript::SetBeginData()
{
	int iRot = rand() % 16;			// 0~15사이 랜덤 난수

	if (GetOwner()->GetName() == L"UFO_1")
	{
		m_iHP = 2000;
		m_iShootDist = 1500;
		m_fSpeed = 100.f;
		m_fBulletDelay = 2.f;
	}
	else if (GetOwner()->GetName() == L"UFO_2")
	{
		Vec3 vCurRot = Transform()->GetRelativeRot();
		Transform()->SetRelativeScale(Vec3(30.f, 30.f, 30.f));
		Transform()->SetRelativeRot(ConvertToRadians(Vec3(vCurRot.x, vCurRot.y, vCurRot.z + iRot)));
		m_iMaxHP = 100;
		m_iHP = 100;
		m_iShootDist = 700;
		m_fSpeed = 500.f;
		m_fBulletDelay = 1.2f;
		m_fExLifeTime = 1.4f;
		m_fExScale = 400.f;
	}
	else if (GetOwner()->GetName() == L"BOSS")
	{
		m_iMaxHP = 1000;
		m_iHP = 1000;
		m_iShootDist = 5000;
		m_fSpeed = 0.f;
		m_fBulletDelay = 0.5f;
		m_fExLifeTime = 3.f;
		m_fExScale = 1500.f;
	}
}

void CMonsterScript::BulletFire(Vec3 _Dir)
{
	if (GetOwner()->GetName() == L"UFO_2")
	{
		CGameObject* pParticle = new CGameObject;
		pParticle->SetName(L"Bullet_UFO2");

		pParticle->AddComponent(new CTransform);
		pParticle->AddComponent(new CParticleSystem);
		pParticle->AddComponent(new CCollider3D);
		//pParticle->AddComponent(new CLight3D);
		pParticle->AddComponent(new CBulletScript);

		pParticle->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
		pParticle->Collider3D()->SetAbsolute(true);
		pParticle->Collider3D()->SetOffsetScale(Vec3(3.f, 3.f, 3.f));

		pParticle->Transform()->SetRelativeScale(Vec3(3.f, 3.f, 3.f));

		pParticle->ParticleSystem()->SetSpawnEnable(true);						// SetSpawn
		pParticle->ParticleSystem()->SetMaxParticle(200);
		pParticle->ParticleSystem()->SetSpawnRate(100);
		pParticle->ParticleSystem()->SetSpawnColor(Vec4(1.f, 1.f, 1.f, 1.f));
		pParticle->ParticleSystem()->SetSpawnScaleMin(Vec3(15.f, 15.f, 15.f));
		pParticle->ParticleSystem()->SetSpawnScaleMax(Vec3(15.f, 15.f, 15.f));
		pParticle->ParticleSystem()->SetShapeType(2);
		pParticle->ParticleSystem()->SetShapeScale(Vec3(0.1f, 0.1f, 0.1f));
		pParticle->ParticleSystem()->SetMinLifeTime(0.7f);
		pParticle->ParticleSystem()->SetMaxLifeTime(0.7f);
		pParticle->ParticleSystem()->SetColorChangeEnable(true);				// SetColor
		pParticle->ParticleSystem()->SetStartColor(Vec4(0.f, 1.f, 0.85f, 1.f));
		pParticle->ParticleSystem()->SetEndColor(Vec4(1.f, 1.f, 1.f, 0.f));
		pParticle->ParticleSystem()->SetAddVelocityEnable(true);				// AddVelocity
		pParticle->ParticleSystem()->SetAddVelocityType(2);
		pParticle->ParticleSystem()->SetScaleChangeEnable(true);
		pParticle->ParticleSystem()->SetStartScale(1.f);
		pParticle->ParticleSystem()->SetEndScale(0.5f);
		pParticle->ParticleSystem()->SetSpeed(0.f);
		pParticle->ParticleSystem()->SetDragEnable(false);						// SetDrag
		pParticle->ParticleSystem()->SetRenderEnable(false);					// Render

		//pParticle->Light3D()->SetLightType(LIGHT_TYPE::POINT);
		//pParticle->Light3D()->SetRadius(100.f);
		//pParticle->Light3D()->SetLightSpecular(Vec3(0.f, 1.f, 0.85f));
		//pParticle->Light3D()->SetLightAmbient(Vec3(0.f, 1.f, 0.85f));

		m_vMobBulletPos = Vec3(m_vCurPos.x, m_vCurPos.y + 20.f, m_vCurPos.z);

		pParticle->GetScript<CBulletScript>()->SetBulletDir((m_vPlayerPos - m_vMobBulletPos).Normalize());
		pParticle->GetScript<CBulletScript>()->SetLifeSpan(2.0f);

		SpawnGameObject(pParticle, m_vMobBulletPos, 5);
	}

	else if (GetOwner()->GetName() == L"BOSS")
	{
		CGameObject* pParticle = new CGameObject;
		pParticle->SetName(L"Bullet_BOSS");

		pParticle->AddComponent(new CTransform);
		pParticle->AddComponent(new CParticleSystem);
		pParticle->AddComponent(new CCollider3D);
		//pParticle->AddComponent(new CLight3D);
		pParticle->AddComponent(new CBulletScript);

		pParticle->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
		pParticle->Collider3D()->SetAbsolute(true);
		pParticle->Collider3D()->SetOffsetScale(Vec3(20.f, 20.f, 20.f));

		pParticle->Transform()->SetRelativeScale(Vec3(3.f, 3.f, 3.f));

		pParticle->ParticleSystem()->SetSpawnEnable(true);						// SetSpawn
		pParticle->ParticleSystem()->SetMaxParticle(200);
		pParticle->ParticleSystem()->SetSpawnRate(100);
		pParticle->ParticleSystem()->SetSpawnColor(Vec4(1.f, 1.f, 1.f, 1.f));
		pParticle->ParticleSystem()->SetSpawnScaleMin(Vec3(30.f, 30.f, 30.f));
		pParticle->ParticleSystem()->SetSpawnScaleMax(Vec3(30.f, 30.f, 30.f));
		pParticle->ParticleSystem()->SetShapeType(2);
		pParticle->ParticleSystem()->SetShapeScale(Vec3(0.1f, 0.1f, 0.1f));
		pParticle->ParticleSystem()->SetMinLifeTime(1.5f);
		pParticle->ParticleSystem()->SetMaxLifeTime(1.5f);
		pParticle->ParticleSystem()->SetColorChangeEnable(true);				// SetColor
		pParticle->ParticleSystem()->SetStartColor(Vec4(1.f, 0.f, 0.f, 1.f));
		pParticle->ParticleSystem()->SetEndColor(Vec4(1.f, 1.f, 0.f, 0.f));
		pParticle->ParticleSystem()->SetAddVelocityEnable(true);				// AddVelocity
		pParticle->ParticleSystem()->SetAddVelocityType(2);
		pParticle->ParticleSystem()->SetScaleChangeEnable(true);
		pParticle->ParticleSystem()->SetStartScale(1.f);
		pParticle->ParticleSystem()->SetEndScale(0.5f);
		pParticle->ParticleSystem()->SetSpeed(0.f);
		pParticle->ParticleSystem()->SetDragEnable(false);						// SetDrag
		pParticle->ParticleSystem()->SetRenderEnable(false);					// Render

		//pParticle->Light3D()->SetLightType(LIGHT_TYPE::POINT);
		//pParticle->Light3D()->SetRadius(100.f);
		//pParticle->Light3D()->SetLightSpecular(Vec3(1.f, 0.f, 0.f));
		//pParticle->Light3D()->SetLightAmbient(Vec3(1.f, 0.f, 0.f));

		pParticle->GetScript<CBulletScript>()->SetBulletDir(_Dir);
		pParticle->GetScript<CBulletScript>()->SetLifeSpan(3.0f);

		SpawnGameObject(pParticle, m_vBulletParticlePos, 5);
	}
}

void CMonsterScript::CreateBossParticle()
{
	m_pBulletParticle = new CGameObject;
	m_pBulletParticle->SetName(L"BulletParticle");

	m_pBulletParticle->AddComponent(new CTransform);
	m_pBulletParticle->AddComponent(new CParticleSystem);

	m_pBulletParticle->Transform()->SetRelativeScale(Vec3(3.f, 3.f, 3.f));

	m_pBulletParticle->ParticleSystem()->SetSpawnEnable(true);						// SetSpawn
	m_pBulletParticle->ParticleSystem()->SetMaxParticle(200);
	m_pBulletParticle->ParticleSystem()->SetSpawnRate(100);
	m_pBulletParticle->ParticleSystem()->SetSpawnColor(Vec4(1.f, 1.f, 1.f, 1.f));
	m_pBulletParticle->ParticleSystem()->SetSpawnScaleMin(Vec3(50.f, 10.f, 0.f));
	m_pBulletParticle->ParticleSystem()->SetSpawnScaleMax(Vec3(30.f, 50.f, 15.f));
	m_pBulletParticle->ParticleSystem()->SetShapeType(2);
	m_pBulletParticle->ParticleSystem()->SetShapeScale(Vec3(400.f, 400.f, 400.f));
	m_pBulletParticle->ParticleSystem()->SetMinLifeTime(0.8f);
	m_pBulletParticle->ParticleSystem()->SetMaxLifeTime(0.8f);
	m_pBulletParticle->ParticleSystem()->SetColorChangeEnable(true);				// SetColor
	m_pBulletParticle->ParticleSystem()->SetStartColor(Vec4(1.f, 0.f, 0.f, 1.f));
	m_pBulletParticle->ParticleSystem()->SetEndColor(Vec4(1.f, 1.f, 0.f, 0.f));
	m_pBulletParticle->ParticleSystem()->SetAddVelocityEnable(true);				// AddVelocity
	m_pBulletParticle->ParticleSystem()->SetAddVelocityType(1);
	m_pBulletParticle->ParticleSystem()->SetScaleChangeEnable(true);
	m_pBulletParticle->ParticleSystem()->SetStartScale(1.f);
	m_pBulletParticle->ParticleSystem()->SetEndScale(0.5f);
	m_pBulletParticle->ParticleSystem()->SetSpeed(100.f);
	m_pBulletParticle->ParticleSystem()->SetDragEnable(false);						// SetDrag
	m_pBulletParticle->ParticleSystem()->SetRenderEnable(true);						// Render
	m_pBulletParticle->ParticleSystem()->SetVelocityAlignment(true);
	m_pBulletParticle->ParticleSystem()->SetVelocityScale(true);
	m_pBulletParticle->SetLifeSpan(m_fAttackDelay + 2.f);

	m_vBulletParticlePos = Vec3(m_vCurPos.x, m_vCurPos.y + 220.f, m_vCurPos.z + 150.f);
	//m_vBulletParticlePos = Vec3(0.f, 220.f, 150.f);
	SpawnGameObject(m_pBulletParticle, m_vBulletParticlePos, 0);
}

void CMonsterScript::CreateBossSummonMark()
{
	m_pMark = new CGameObject;
	m_pMark->AddComponent(new CTransform);
	m_pMark->AddComponent(new CMeshRender);
	m_pMark->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 0.f));
	m_pMark->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	m_pMark->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\SummonMark.mtrl"), 0);
	
	SpawnGameObject(m_pMark, m_vCurPos + Vec3(0.f, 150.f, 160.f), 0);

	m_pMarkDecal = new CGameObject;
	m_pMarkDecal->AddComponent(new CTransform);
	m_pMarkDecal->AddComponent(new CDecal);
	m_pMarkDecal->Transform()->SetRelativeScale(Vec3(300.f, 50.f, 300.f));
	m_pMarkDecal->Decal()->SetOutputTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\MagicCircle.png"));
	m_pMarkDecal->Decal()->SetAsLight(true);

	SpawnGameObject(m_pMarkDecal, m_vCurPos + Vec3(0.f, 100.f, 160.f), 0);

	CGameObject* pLight = new CGameObject;
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight3D);

	pLight->Light3D()->SetLightType(LIGHT_TYPE::POINT);
	pLight->Light3D()->SetRadius(260.f);
	pLight->Light3D()->SetLightSpecular(Vec3(1.f, 0.f, 0.f));
	pLight->Light3D()->SetLightAmbient(Vec3(1.f, 0.f, 0.f));
	pLight->SetLifeSpan(5.f);

	SpawnGameObject(pLight, m_vCurPos + Vec3(0.f, 175.f, 160.f), 0);
}

void CMonsterScript::GetObjData()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

	vector<CGameObject*> vecObject = CurLevel->GetLayer(1)->GetObjects();
	if (vecObject.size() != 0)
	{
		for (CGameObject* obj : vecObject)
		{
			if (obj->GetName() == "Player")
				m_pPlayer = obj;
		}
	}
}

void CMonsterScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fExLifeTime, sizeof(float), 1, _File);
	fwrite(&m_fExScale, sizeof(float), 1, _File);
}

void CMonsterScript::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_fExLifeTime, sizeof(float), 1, _FILE);
	fread(&m_fExScale, sizeof(float), 1, _FILE);
}
