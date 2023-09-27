#include "pch.h"
#include "CHPBarScript.h"

CHPBarScript::CHPBarScript()
	: CScript((UINT)SCRIPT_TYPE::HPBARSCRIPT)
{
}

CHPBarScript::~CHPBarScript()
{

}

void CHPBarScript::begin()
{
	GetCameraObj();
}

void CHPBarScript::tick()
{
	Vec3 vDir = m_pCamera->Transform()->GetWorldPos() - Transform()->GetWorldPos();
	Matrix matRotation = XMMatrixLookAtLH(m_vCurPos, m_vCurPos + vDir, Vec3(0, 1, 0));
	Vec3 vFinalRot = ExtractEulerAngles(matRotation);

	float fCurrentWidth = Transform()->GetRelativeScale().x;
	float fDiff = (100.f - fCurrentWidth) / 2;

	if (m_bBoss)
	{
		Vec3 vFinalPos = Vec3(m_vCurPos.x - fDiff, m_vCurPos.y + 300.f, m_vCurPos.z);
		Vec3 vFinalScale = Vec3(500.f * m_fHPRatio, 20.f, 0.f);

		Transform()->SetRelativeRot(vFinalRot);
		Transform()->SetRelativePos(vFinalPos);
		Transform()->SetRelativeScale(vFinalScale);
	}
	else
	{
		Vec3 vFinalPos = Vec3(m_vCurPos.x - fDiff, m_vCurPos.y + 50.f , m_vCurPos.z);
		Vec3 vFinalScale = Vec3(100.f * m_fHPRatio, 10.f, 0.f);

		Transform()->SetRelativeRot(vFinalRot);
		Transform()->SetRelativePos(vFinalPos);
		Transform()->SetRelativeScale(vFinalScale);
	}
}

void CHPBarScript::GetCameraObj()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

	vector<CGameObject*> vecObject = CurLevel->GetLayer(1)->GetObjects();
	if (vecObject.size() != 0)
	{
		for (CGameObject* obj : vecObject)
		{
			if (obj->GetName() == "MainCamera")
				m_pCamera = obj;
		}
	}
}