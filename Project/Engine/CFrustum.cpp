#include "pch.h"
#include "CFrustum.h"
#include "CTransform.h"
#include "CCamera.h"

CFrustum::CFrustum(CCamera* _pOwner)
	: m_pOwner(_pOwner)
	, m_arrFace{}
{
	// 투영공간 좌표
	//     4 ------ 5
	//     |        |  Far
	//   / |        |
	//	/  7 ------ 6	
	// /      /
	// 0 -- 1     /
	// |    |    / Near
	// 3 -- 2
	m_arrProj[0] = Vec3(-1.f, 1.f, 0.f);
	m_arrProj[1] = Vec3(1.f, 1.f, 0.f);
	m_arrProj[2] = Vec3(1.f, -1.f, 0.f);
	m_arrProj[3] = Vec3(-1.f, -1.f, 0.f);

	m_arrProj[4] = Vec3(-1.f, 1.f, 1.f);
	m_arrProj[5] = Vec3(1.f, 1.f, 1.f);
	m_arrProj[6] = Vec3(1.f, -1.f, 1.f);
	m_arrProj[7] = Vec3(-1.f, -1.f, 1.f);
}

CFrustum::~CFrustum()
{
}

void CFrustum::finaltick()
{
	Vec3 vWorldPos[8] = {};

	Matrix matInv = m_pOwner->GetProjMatInv() * m_pOwner->GetViewMatInv();

	for (int i = 0; i < 8; ++i)
	{
		vWorldPos[i] = XMVector3TransformCoord(m_arrProj[i], matInv);
	}

	m_arrFace[FT_NEAR] = XMPlaneFromPoints(vWorldPos[0], vWorldPos[1], vWorldPos[2]);
	m_arrFace[FT_FAR] = XMPlaneFromPoints(vWorldPos[7], vWorldPos[6], vWorldPos[5]);
	m_arrFace[FT_LEFT] = XMPlaneFromPoints(vWorldPos[4], vWorldPos[0], vWorldPos[7]);
	m_arrFace[FT_RIGHT] = XMPlaneFromPoints(vWorldPos[1], vWorldPos[5], vWorldPos[6]);
	m_arrFace[FT_TOP] = XMPlaneFromPoints(vWorldPos[4], vWorldPos[5], vWorldPos[1]);
	m_arrFace[FT_BOT] = XMPlaneFromPoints(vWorldPos[2], vWorldPos[6], vWorldPos[7]);

	Matrix scaleMatrix = XMMatrixScaling(m_CameraDebugScale, m_CameraDebugScale, m_CameraDebugScale);
	Matrix transformedMatrix = scaleMatrix * matInv;
	if (m_bShowCameraDebugShape)
		DrawDebugCube(transformedMatrix, Vec4(0.f, 1.f, 0.f, 1.f), 0.f);
}

bool CFrustum::FrustumCheckByPoint(Vec3 _vWorldPos)
{
	for (int i = 0; i < FT_END; ++i)
	{
		// 임의의 점과 해당 평면의 법선벡터와 내적
		Vec3 vNormal = m_arrFace[i];
		vNormal.Normalize();
		float fDot = vNormal.Dot(_vWorldPos);

		// 내적한 값과 원점에서 해당 평면까지의 최단거리(D) 와 비교
		if (fDot + m_arrFace[i].w > 0)
			return false;
	}

	return true;
}

bool CFrustum::FrustumCheckBySphere(Vec3 _vWorldPos, float _fRadius, bool _bDebugUse)
{
	for (int i = 0; i < FT_END; ++i)
	{
		// 임의의 점과 해당 평면의 법선벡터와 내적
		Vec3 vNormal = m_arrFace[i];
		vNormal.Normalize();
		float fDot = vNormal.Dot(_vWorldPos);

		// 내적한 값과 원점에서 해당 평면까지의 최단거리(D) 와 비교
		if (fDot + m_arrFace[i].w > _fRadius)
			return false;
	}

	if (_bDebugUse)
		DrawDebugCircle(_vWorldPos, _fRadius, Vec4(0.f, 1.f, 0.f, 1.f), m_pOwner->Transform()->GetRelativeRot(), 0.f);

	return true;
}
