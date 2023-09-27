#include "pch.h"
#include "CMapObjectScript.h"

CMapObjectScript::CMapObjectScript()
	: CScript((UINT)SCRIPT_TYPE::MAPOBJECTSCRIPT)
	, m_vOffsetPos(1000.f, 1000.f, 1000.f)
{
	AddScriptParam(SCRIPT_PARAM::BOOL, &m_bDistant, "SetDistant");
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vOffsetPos, "OffsetPos");
	AddScriptParam(SCRIPT_PARAM::BOOL, &m_bRotation, "SetRotation");
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vRotPos, "RotPos");
}

CMapObjectScript::~CMapObjectScript()
{
}

void CMapObjectScript::begin()
{
	GetPlayerData();
}

void CMapObjectScript::tick()
{
	if (m_bDistant)
	{
		Vec3 vPlayerPos = m_pPlayer->Transform()->GetWorldPos();
		Transform()->SetRelativePos(vPlayerPos + m_vOffsetPos);
	}

	if (m_bRotation)
	{
		Vec3 vPlayerRot = Transform()->GetRelativeRot();
		Vec3 vRotPos = m_vRotPos;
		vRotPos *= DT;
		Transform()->SetRelativeRot(vPlayerRot + vRotPos);
	}
}

void CMapObjectScript::GetPlayerData()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (int i = 0; i < 10; ++i)
	{
		vector<CGameObject*> vecObject = CurLevel->GetLayer(i)->GetObjects();
		if (vecObject.size() != 0)
		{
			for (CGameObject* obj : vecObject)
			{
				if (obj->GetName() == "Player")
					m_pPlayer = obj;
			}
		}
	}
}


void CMapObjectScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_bDistant, sizeof(bool), 1, _File);
	fwrite(&m_bRotation, sizeof(bool), 1, _File);
	fwrite(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fwrite(&m_vRotPos, sizeof(Vec3), 1, _File);
}

void CMapObjectScript::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_bDistant, sizeof(bool), 1, _FILE);
	fread(&m_bRotation, sizeof(bool), 1, _FILE);
	fread(&m_vOffsetPos, sizeof(Vec3), 1, _FILE);
	fread(&m_vRotPos, sizeof(Vec3), 1, _FILE);
}
