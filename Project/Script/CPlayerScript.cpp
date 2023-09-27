#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>
#include <Engine\CSound.h>

#include "CMuzzleScript.h"
#include "CMissileScript.h"


CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_fMaxSpeed(250.f)
	, m_DefaultRot(90.f, 180.f, 0.f)
	, m_iHP(5000)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fMaxSpeed, "MaxSpeed");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fSpeed, "Speed");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fAccel, "Accel");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fBreak, "Break");
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vAxis, "Axis");
	AddScriptParam(SCRIPT_PARAM::BOOL, &m_bDamage, "Damage");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fBulletDelay, "BulletDelay");
}

CPlayerScript::~CPlayerScript()
{
	if(m_sBGM)
		m_sBGM->Stop();
}

void CPlayerScript::begin()
{
	GetMuzzleData();

	m_sBGM = (CResMgr::GetInst()->FindRes<CSound>(L"Sound\\Title.mp3")).Get();
	m_sBGM->Play(0, 0.3f, true);

	m_sEngineSound = (CResMgr::GetInst()->FindRes<CSound>(L"Sound\\Moving.mp3")).Get();
	m_sEngineSound->Play(0, m_fPlayerSpeed, true);

	Transform()->SetRelativeRot(ConvertToRadians(Vec3(90.f, 180.f, 0.f)));
}

void CPlayerScript::tick()
{
	PlayerMove();
	PlayerAccel();
	PlayerRotation();
	PlayerFunction();

	m_sEngineSound->SetVolume(m_fPlayerSpeed * 0.5f, 30);
}

void CPlayerScript::BeginOverlap(CCollider3D* _Other)
{

	if (_Other->GetOwner()->GetLayerIndex() == 5)		// 몬스터 총알에 맞았을 때
	{
		if (!m_bDamage)									// 카메라를 통한 피격 효과
		{
			m_bDamage = true;
			m_fDamageDT = 0.5f;
		}
		else
			m_fDamageDT = 0.5f;
	}
}

void CPlayerScript::PlayerMove()
{
	Vec3 vMovePos(0, 0, 0);
	m_PrevPos = m_CurPos;
	m_CurPos = Transform()->GetRelativePos();
	m_AccelEnable = false;
	m_BreakEnable = false;

	if (KEY_PRESSED(KEY::W))
		m_AccelEnable = true;

	if (KEY_PRESSED(KEY::S))
		m_BreakEnable = true;

	Vec3 vAxis = Transform()->GetWorldRotation().Down();
	m_vAxis = vAxis.Normalize();
	vMovePos = m_vAxis * m_fSpeed * DT;
	m_CurPos = Transform()->GetWorldPos() + vMovePos;
	Transform()->SetRelativePos(m_CurPos);
	m_MoveDir = m_CurPos - m_PrevPos;					// 플레이어 방향 
}

void CPlayerScript::PlayerAccel()
{
	if (m_AccelEnable && m_fSpeed < m_fMaxSpeed)
		m_fAccel += DT * m_fMaxSpeed / 400.f;

	else if (!m_AccelEnable)
		m_fAccel -= (DT * m_fMaxSpeed / 800.f) + m_fBreak;
		m_fAccel = max(0.f, m_fAccel);

	if (m_BreakEnable && m_fSpeed > 0.f)
		m_fBreak += DT * m_fMaxSpeed / 50000.f; // 브레이크가 활성화되면 m_fBreak 값을 증가시킴

	if (m_fBreak > 0.f && m_fSpeed <= 0.f)
	{
		m_fBreak = max(0.f, m_fBreak - DT * 0.002f);
	}

	m_fSpeed = min(m_fMaxSpeed, m_fMaxSpeed * m_fAccel * m_fAccel * 2.f);
	m_fSpeed = max(0.f, m_fSpeed); // 속도는 0 이상이어야 함
}

void CPlayerScript::PlayerRotation()
{
	m_ePitch = PLAYER_PITCH::IDLE;
	m_eRoll = PLAYER_ROLL::IDLE;
	m_eYaw = PLAYER_YAW::IDLE;

	if (KEY_PRESSED(KEY::A))
		m_eYaw = PLAYER_YAW::LEFT;

	if (KEY_PRESSED(KEY::D))
		m_eYaw = PLAYER_YAW::RIGHT;

	if (KEY_PRESSED(KEY::UP))
		m_ePitch = PLAYER_PITCH::UP;

	if (KEY_PRESSED(KEY::DOWN))
		m_ePitch = PLAYER_PITCH::DOWN;

	if (KEY_PRESSED(KEY::LEFT))
		m_eRoll = PLAYER_ROLL::LEFT;

	if (KEY_PRESSED(KEY::RIGHT))
		m_eRoll = PLAYER_ROLL::RIGHT;


	m_fPlayerSpeed = m_fSpeed / m_fMaxSpeed;

	// 기체 상 하 회전 m_fPitch
	// 기체 좌 우 회전 m_fRoll

	switch (m_ePitch)
	{
		case PLAYER_PITCH::UP:
			m_fPitch -= DT * 0.5f;
			m_fPitch = max(-0.4f, m_fPitch);
			break;
		case PLAYER_PITCH::DOWN:
			m_fPitch += DT * 0.5f;
			m_fPitch = min(0.4f, m_fPitch);
			break;
		case PLAYER_PITCH::IDLE:
			if (m_fPitch > 0.f)
			{
				m_fPitch -= DT * 0.4f;
				m_fPitch = max(0.f, m_fPitch);
			}
			else if (m_fPitch < 0.f)
			{
				m_fPitch += DT * 0.4f;
				m_fPitch = min(0.f, m_fPitch);
			}
			else
				m_fPitch = 0.f;
			break;
	}

	switch (m_eRoll)
	{
		case PLAYER_ROLL::LEFT:
			m_fRoll -= DT * 0.5f;
			m_fRoll = max(-0.4f, m_fRoll);
			break;
		case PLAYER_ROLL::RIGHT:
			m_fRoll += DT * 0.5f;
			m_fRoll = min(0.4f, m_fRoll);
			break;
		case PLAYER_ROLL::IDLE:
			if (m_fRoll > 0.f)
			{
				m_fRoll -= DT * 0.4f;
				m_fRoll = max(0.f, m_fRoll);
			}
			else if (m_fRoll < 0.f)
			{
				m_fRoll += DT * 0.4f;
				m_fRoll = min(0.f, m_fRoll);
			}
			else
				m_fRoll = 0.f;
			break;
	}

	switch (m_eYaw)
	{
		case PLAYER_YAW::LEFT:
			m_fYaw += DT * 0.5f;
			m_fYaw = min(0.3f, m_fYaw);
			break;
		case PLAYER_YAW::RIGHT:
			m_fYaw -= DT * 0.5f;
			m_fYaw = max(-0.3f, m_fYaw);
			break;
		case PLAYER_YAW::IDLE:
			if (m_fYaw > 0.f)
			{
				m_fYaw -= DT * 0.4f;
				m_fYaw = max(0.f, m_fYaw);
			}
			else if (m_fYaw < 0.f)
			{
				m_fYaw += DT * 0.4f;
				m_fYaw = min(0.f, m_fYaw);
			}
			else
				m_fYaw = 0.f;
			break;
	}

	float rX = ((rand() % 3) - 1) * 0.03;
	float rY = ((rand() % 3) - 1) * 0.03;
	float rZ = ((rand() % 3) - 1) * 0.03;

	m_vNoisePos = Vec3(rX, rY, rZ);

	Vec3 vFinalRot = Vec3(m_fPitch + rX * m_fPlayerSpeed, m_fRoll + rY * m_fPlayerSpeed, m_fYaw + rZ * m_fPlayerSpeed);
	Transform()->SetQuaternionRot(ConvertToRadians(vFinalRot));
}

void CPlayerScript::PlayerFunction()
{
	m_fBulletDelay = min(0.5f, m_fBulletDelay += DT);

	if (m_fDamageDT >= 0.f)
	{
		m_fDamageDT -= DT;
		m_fDamageDT = max(0.f, m_fDamageDT);
	}

	if (m_bDamage && m_fDamageDT == 0.f)
		m_bDamage = false;

	if (KEY_TAP(KEY::F))				// BackView
	{
		if (!m_bBackView)
			m_bBackView = true;
		else
			m_bBackView = false;
	}

	if (KEY_PRESSED(KEY::SPACE))		// Gun Attack
	{
		if (m_fBulletDelay >= 0.2f)		// CoolTime
		{
			Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\Fire.mp3");
			pSound->Play(1, 0.3f, true);

			m_MuzzleScript_1->CreateBullet();
			m_MuzzleScript_2->CreateBullet();

			m_fBulletDelay = 0.f;
		}
	}

	if (KEY_TAP(KEY::LCTRL))
	{
		
	}
}

//void CPlayerScript::CreateAim()
//{
//	m_pAim = new CGameObject;
//	m_pAim->SetName(L"Player_Aim");
//	m_pAim->AddComponent(new CTransform);
//	m_pAim->AddComponent(new CMeshRender);
//	m_pAim->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));
//	m_pAim->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
//	m_pAim->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\GreenAim.mtrl"), 0);
//
//	SpawnGameObject(m_pAim, Vec3(0.f, 0.f, 0.f), 0);
//}

void CPlayerScript::GetMuzzleData()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

	vector<CGameObject*> vecObject = CurLevel->GetLayer(1)->GetObjects();
	if (vecObject.size() != 0)
	{
		for (CGameObject* obj : vecObject)
		{
			if (obj->GetName() == "Muzzle_01")
			{
				m_MuzzleObj_1 = obj;
				m_MuzzleScript_1 = m_MuzzleObj_1->GetScript<CMuzzleScript>();
			}
			else if (obj->GetName() == "Muzzle_02")
			{
				m_MuzzleObj_2 = obj;
				m_MuzzleScript_2 = m_MuzzleObj_2->GetScript<CMuzzleScript>();
			}
		}
	}
}

void CPlayerScript::CreateText()
{
	m_NaviText = new CGameObject;
	m_NaviText->SetName(L"NaviText");

	m_NaviText->AddComponent(new CTransform);
	m_NaviText->AddComponent(new CFont);

	m_NaviText->Font()->SetString(L"Player");
	m_NaviText->Font()->SetColor(Vec4(255.f, 255.f, 255.f, 255.f));
	m_NaviText->Font()->SetScale(30.f);
	m_NaviText->Font()->SetPos(Vec2(30.f, 720.f));

	SpawnGameObject(m_NaviText, Vec3(0.f, 0.f, 0.f), 0);
}

void CPlayerScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
}