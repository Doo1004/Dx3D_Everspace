#include "pch.h"
#include "CCameraMoveScript.h"
#include "CPlayerScript.h"

#include <Engine\CTransform.h>
#include <Engine\CCamera.h>
#include <Engine\CLevelMgr.h>

CCameraMoveScript::CCameraMoveScript()
	: CScript((UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT)
	, m_fCamSpeed(60.f)
	, m_vCameraPos(Vec3(0.f, 1400.f, -700.f))
	, m_vCameraRot(Vec3(90.f, -180.f, 0.f))
{
	m_CurLevel = CLevelMgr::GetInst()->GetCurLevel();
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vCameraPos, "Pos");
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vPlayerRot, "Rot");
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vDamageRot, "DamageRot");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fBackViewPos, "BackViewPos");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fBackViewRot, "BackViewRot");
}

CCameraMoveScript::~CCameraMoveScript()
{

}

void CCameraMoveScript::begin()
{
	m_CurLevel = CLevelMgr::GetInst()->GetCurLevel();
	GetPlayerData();
}

void CCameraMoveScript::tick()
{
	if (m_CurLevel->GetState() != LEVEL_STATE::PLAY)
		CameraEditMode();
	else
	{
		CameraPlayMode();
		GetPlayerState();
	}
}

void CCameraMoveScript::CameraEditMode()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRot();

	Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);
	Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);

	float fSpeed = m_fCamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
		fSpeed *= 5.f;

	if (KEY_PRESSED(KEY::W))
		vPos += DT * vFront * fSpeed;

	if (KEY_PRESSED(KEY::S))
		vPos -= DT * vFront * fSpeed;

	if (KEY_PRESSED(KEY::A))
		vPos -= DT * vRight * fSpeed;

	if (KEY_PRESSED(KEY::D))
		vPos += DT * vRight * fSpeed;

	if (KEY_PRESSED(KEY::RBTN))
	{
		Vec2 vMouseDir = CKeyMgr::GetInst()->GetMouseDir();
		vRot.y += DT * vMouseDir.x * 5.f;
		vRot.x -= DT * vMouseDir.y * 5.f;
	}

	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRot(vRot);
}

void CCameraMoveScript::CameraPlayMode()
{
	Vec3 vPlayerPos;
	if (m_PlayerObject)
	{
		vPlayerPos = m_PlayerObject->Transform()->GetRelativePos();
		m_vPlayerRot = m_PlayerScript->GetPitchRollYaw() * 4;
		m_fDamageTime = m_PlayerScript->GetDamageTime();
		m_vDamageRot = m_PlayerScript->GetDamageCameraPos();
	}

	//=====================================FrontMove 처리
	Vec3 vFrontMovePos = Vec3(0.f, 0.f, 0.f);
	if (!m_bBackView)						// 정면을 바라보고 있을 땐 우주선이 이동할 때 카메라가 살짝 뒤로 이동 
	{
		vFrontMovePos.y = m_fPlayerSpeed * 170.f;
		vFrontMovePos.z = m_fPlayerSpeed * 50.f;
	}
	else if (m_bBackView)					// BackView가 켜져있을 땐 카메라가 앞으로 이동
	{
		vFrontMovePos.y = m_fPlayerSpeed * 170.f;
		vFrontMovePos.z = m_fPlayerSpeed * 50.f;
	}
	//=====================================BackView 처리
	Vec3 vBackPos;
	Vec3 vBackRot;

	if (!m_bBackView)
	{
		vBackPos.y = 0.f;
		vBackRot.z = 0.f;
	}
	else if (m_bBackView)
	{
		vBackPos.y = -3000.f;
		vBackRot.z = 180.f;
	}
	//=====================================Break 처리
	Vec3 vBreakPos = Vec3(0.f, m_fPlayerBreak * 5000.f, 0.f);
	//=====================================Calculate
	Vec3 vFinalPos = m_vCameraPos + m_vPlayerRot + vFrontMovePos + vBackPos + vBreakPos;
	Vec3 vFinalRot = m_vCameraRot + m_vPlayerRot + (m_vDamageRot * m_fDamageTime * 50) + vBackRot;

	Transform()->SetRelativePos(vFinalPos);
	Transform()->SetRelativeRot(ConvertToRadians(vFinalRot));
}

void CCameraMoveScript::GetPlayerState()
{
	if (m_PlayerObject)
	{
		m_bBackView = m_PlayerScript->IsBackView();
		m_bBoost = m_PlayerScript->IsBoost();
		m_bDamage = m_PlayerScript->IsDamage();
		m_fPlayerSpeed = m_PlayerScript->GetPlayerSpeed();
		m_fPlayerBreak = m_PlayerScript->GetPlayerBreak();
	}
}

void CCameraMoveScript::GetPlayerData()
{
	vector<CGameObject*> vecObject = m_CurLevel->GetLayer(1)->GetParentObject();
	if (vecObject.size() != 0)
	{
		m_PlayerObject = vecObject[0];
		m_PlayerScript = m_PlayerObject->GetScript<CPlayerScript>();
	}
}
