#include "pch.h"
#include "CNavObjScript.h"
#include "CMonsterScript.h"
#include <Engine/CSound.h>

CNavObjScript::CNavObjScript()
	: CScript((UINT)SCRIPT_TYPE::NAVOBJSCRIPT)
	, m_iDir(1)
	, m_fTimer(1.5f)
	, m_vCalculPos(0.f, 0.1f, 0.f)
	, m_iScale(1)
	, m_bStageOn(false)
	, m_bTextOn(true)

{
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vCurScale, "Scale");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fDistance, "Distance");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fDistanceDesired, "Desired");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fDT, "DT");
}

CNavObjScript::~CNavObjScript()
{
}

void CNavObjScript::begin()
{
	GetPlayerData();
	CreateNaviText();
	m_vCurScale = Transform()->GetRelativeScale();
}

void CNavObjScript::tick()
{
	m_vCurPos = Transform()->GetRelativePos();
	Vec3 vPlayerPos = m_pPlayerObject->Transform()->GetRelativePos();
	m_fDistance = CalculDist(m_vCurPos, vPlayerPos);
	m_fDistanceDesired = m_fDistance / 2000.f;
	Vec3 vCurRot = Transform()->GetRelativeRot();
	m_iMonster = m_pCurLevel->GetLayer(2)->GetParentObject().size();

	SetTextData();					// 텍스트 관련

	m_fTimer -= DT;					// 위 아래로 무빙
	if (m_fTimer <= 0.f)
	{
		m_vCalculPos.y *= -1;
		m_fTimer = 1.5f;
	}

	Transform()->SetRelativePos(m_vCurPos + m_vCalculPos);
	Transform()->SetRelativeRot(vCurRot + m_vCalculPos * 0.1f);
	Transform()->SetRelativeScale(m_vCurScale * m_fDistanceDesired * m_iScale);

	if (GetOwner()->GetName() == L"NavObj_1")
	{
		if (m_bStageOn && m_iMonster == 0)
		{
			DestroyObject(m_pNaviText);
			CreateNextNavi();
			Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\NavObjActive.mp3");
			pSound->Play(1, 0.5, true);
			Destroy();
			m_bStageOn = false;
		}
	}

	else if (GetOwner()->GetName() == L"NavObj_2")
	{
		if (m_bStageOn && m_iMonster == 0)
		{
			DestroyObject(m_pNaviText);
			Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\NavObjActive.mp3");
			pSound->Play(1, 0.5, true);
			Destroy();
		}
	}
}

void CNavObjScript::BeginOverlap(CCollider3D* _Other)
{
	m_iScale = 0;					// 오브젝트가 사라지되 삭제는 되지 않도록
	m_bStageOn = true;
	Collider3D()->SetAbsolute(false);


	if (GetOwner()->GetName() == L"NavObj_1")
	{
		for (int i = 0; i < 3; ++i)
			CreateMonster(1);
	}
	else if (GetOwner()->GetName() == L"NavObj_2")
	{
		CreateMonster(0);
	}
}

void CNavObjScript::GetPlayerData()
{
	m_pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	vector<CGameObject*> vecObject = m_pCurLevel->GetLayer(1)->GetParentObject();
	if (vecObject.size() != 0)
	{
		m_pPlayerObject = vecObject[0];
	}
}

void CNavObjScript::CreateNaviText()
{
	m_pNaviText = new CGameObject;
	m_pNaviText->SetName(L"NaviText");

	m_pNaviText->AddComponent(new CTransform);
	m_pNaviText->AddComponent(new CFont);
	m_pNaviText->Font()->SetInputData(true);

	SpawnGameObject(m_pNaviText, Vec3(0.f, 0.f, 0.f), 0);
}

void CNavObjScript::CreateMonster(int _MobNum)
{
	if (_MobNum == 0)
	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pMonster = nullptr;

		pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\UFO_3.mdat");
		pMonster = pMeshData->Instantiate();
		pMonster->SetName(L"BOSS");
		pMonster->AddComponent(new CCollider3D);
		pMonster->AddComponent(new CMonsterScript);

		pMonster->Transform()->SetRelativeScale(Vec3(20, 30, 20));

		pMonster->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
		pMonster->Collider3D()->SetAbsolute(true);
		pMonster->Collider3D()->SetOffsetPos(Vec3(0, 49, 0));
		pMonster->Collider3D()->SetOffsetScale(Vec3(500, 200, 1500));

		Vec3 vBossPos = Vec3(m_vCurPos.x - 1000, m_vCurPos.y - 1000, m_vCurPos.z - 2000);

		SpawnGameObject(pMonster, vBossPos, 2);
	}

	else if (_MobNum == 1)
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

		SpawnGameObject(pMonster, Vec3(m_vCurPos), 2);
	}
}

void CNavObjScript::CreateNextNavi()
{
	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* pNavi = nullptr;

	pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\NaviObj.mdat");
	pNavi = pMeshData->Instantiate();
	pNavi->SetName(L"NavObj_2");
	pNavi->AddComponent(new CCollider3D);
	pNavi->AddComponent(new CNavObjScript);

	pNavi->Transform()->SetRelativeScale(Vec3(80, 80, 80));

	pNavi->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pNavi->Collider3D()->SetAbsolute(true);
	pNavi->Collider3D()->SetOffsetScale(Vec3(300, 300, 300));

	SpawnGameObject(pNavi, Vec3(1000, 1000, 3000), 3);
}

void CNavObjScript::SetTextData()
{
	if (m_bTextOn)
	{
		if (m_bStageOn)
		{
			m_pNaviText->Font()->SetString(L" %d Enemy Remained");
			m_pNaviText->Font()->SetColor(Vec4(255.f, 0.f, 0.f, 255.f));
			m_pNaviText->Font()->SetScale(20.f);
			m_pNaviText->Font()->SetPos(Vec2(35.f, 700.f));
			m_pNaviText->Font()->SetData(m_iMonster);
		}
		else if (!m_bStageOn)
		{
			m_pNaviText->Font()->SetString(L"Next Target : %dm");
			m_pNaviText->Font()->SetColor(Vec4(255.f, 255.f, 255.f, 255.f));
			m_pNaviText->Font()->SetScale(20.f);
			m_pNaviText->Font()->SetPos(Vec2(35.f, 700.f));
			m_pNaviText->Font()->SetData((UINT)(m_fDistance - 100));
		}
	}
}
