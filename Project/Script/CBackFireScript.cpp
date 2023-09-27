#include "pch.h"
#include "CBackFireScript.h"
#include "CPlayerScript.h"

CBackFireScript::CBackFireScript()
	: CScript((UINT)SCRIPT_TYPE::BACKFIRESCRIPT)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fParticleLife, "ParticleLife");
}

CBackFireScript::~CBackFireScript()
{
}


void CBackFireScript::begin()
{
	GetPlayerData();
}

void CBackFireScript::tick()
{
	GetPlayerState();

	// �÷��̾� ���ǵ带 ���Ͽ� �Ҳ��� ���� ����
	int iSpawnRate = (int)(100 * m_fPlayerSpeed);

	ParticleSystem()->SetSpawnRate(7 * iSpawnRate);


	// �÷��̾��� ���ǵ忡 ���� ��ƼŬ�� ���� �ð� ����
	m_fParticleLife = m_fPlayerMaxSpeed / 200.0f;

	ParticleSystem()->SetMinLifeTime(0.11f / m_fParticleLife);
	ParticleSystem()->SetMaxLifeTime(0.11f / m_fParticleLife);
}

void CBackFireScript::GetPlayerData()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

	vector<CGameObject*> vecObject = CurLevel->GetLayer(1)->GetParentObject();
	if (vecObject.size() != 0)
	{
		m_PlayerObject = vecObject[0];
		m_PlayerScript = m_PlayerObject->GetScript<CPlayerScript>();
	}
}

void CBackFireScript::GetPlayerState()
{
	m_fPlayerSpeed = m_PlayerScript->GetPlayerSpeed();
	m_fPlayerMaxSpeed = m_PlayerScript->GetPlayerMaxSpeed();
}


