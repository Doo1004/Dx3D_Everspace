#include "pch.h"
#include "TestLevel.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CFontMgr.h>
#include <Engine\CCollisionMgr.h>

#include <Script\CPlayerScript.h>
#include <Script\CMonsterScript.h>

#include "CLevelSaveLoad.h"



void CreateTestLevel()
{
	//return;	

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Player");
	pCurLevel->GetLayer(2)->SetName(L"Monster");
	pCurLevel->GetLayer(3)->SetName(L"NavObj");
	pCurLevel->GetLayer(4)->SetName(L"PlayerProjectile");
	pCurLevel->GetLayer(5)->SetName(L"MonsterProjectile");
	pCurLevel->GetLayer(6)->SetName(L"MapObject");

	pCurLevel->GetLayer(31)->SetName(L"ViewPort UI");

	// Main Camera Object 생성
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);

	pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
	pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
	pMainCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.

	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 0);

	// UI camera
	CGameObject* pUICam = new CGameObject;
	pUICam->SetName(L"UICamera");

	pUICam->AddComponent(new CTransform);
	pUICam->AddComponent(new CCamera);

	pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pUICam->Camera()->SetCameraIndex(1);
	pUICam->Camera()->SetLayerMask(31, true);

	SpawnGameObject(pUICam, Vec3(0.f, 0.f, 0.f), 0);

	
	// 광원 추가
	CGameObject* pLightObj = new CGameObject;
	pLightObj->SetName(L"Directional Light");

	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight3D);
	
	pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObj->Light3D()->SetLightDirection(Vec3(1.f, -1.f, 1.f));

	pLightObj->Light3D()->SetLightDiffuse(Vec3(1.f, 1.f, 1.f));
	pLightObj->Light3D()->SetLightSpecular(Vec3(0.3f, 0.3f, 0.3f));
	pLightObj->Light3D()->SetLightAmbient(Vec3(0.15f, 0.15f, 0.15f));	
	pLightObj->Light3D()->SetRadius(400.f);

	SpawnGameObject(pLightObj, -pLightObj->Light3D()->GetLightDirection() * 1000.f, 0);

	// SkyBox
	CGameObject* pSkyBox  = new CGameObject;
	pSkyBox->SetName(L"SkyBox");
	
	pSkyBox->AddComponent(new CTransform);
	pSkyBox->AddComponent(new CSkyBox);
	
	pSkyBox->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
	pSkyBox->Transform()->SetRelativeRot(Vec3(0.f, XM_PI / 2.f, 0.f));
	
	pSkyBox->SkyBox()->SetType(SKYBOX_TYPE::SPHERE);
	pSkyBox->SkyBox()->SetSkyTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\Sky02.jpg"));	
	
	SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), 0);


	CGameObject* pParticle = new CGameObject;
	pParticle->SetName(L"Bullet_BOSS");

	pParticle->AddComponent(new CTransform);
	pParticle->AddComponent(new CParticleSystem);
	pParticle->AddComponent(new CCollider3D);

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
	pParticle->ParticleSystem()->SetMinLifeTime(0.5f);
	pParticle->ParticleSystem()->SetMaxLifeTime(0.5f);
	pParticle->ParticleSystem()->SetColorChangeEnable(true);				// SetColor
	pParticle->ParticleSystem()->SetStartColor(Vec4(1.f, 0.f, 0.f, 1.f));
	pParticle->ParticleSystem()->SetEndColor(Vec4(1.f, 1.f, 0.f, 0.f));
	pParticle->ParticleSystem()->SetAddVelocityEnable(true);				// AddVelocity
	pParticle->ParticleSystem()->SetAddVelocityType(0);
	pParticle->ParticleSystem()->SetScaleChangeEnable(true);
	pParticle->ParticleSystem()->SetStartScale(1.f);
	pParticle->ParticleSystem()->SetEndScale(0.5f);
	pParticle->ParticleSystem()->SetSpeed(100.f);
	pParticle->ParticleSystem()->SetDragEnable(false);						// SetDrag
	pParticle->ParticleSystem()->SetRenderEnable(false);					// Render

	SpawnGameObject(pParticle, Vec3(0, 0, 0), 0);

	//CGameObject* pObject = new CGameObject;
	//pParticle->SetName(L"Test");
	//
	//pParticle->AddComponent(new CTransform);
	//pParticle->AddComponent(new CMeshRender);
	//
	//pParticle->MeshRender()->SetMaterial()

	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"Test");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\GreenAim.mtrl"), 0);

	SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);



	// ============
	// FBX Loading
	// ============	
	{
		//Ptr<CMeshData> pHouseMesh = nullptr;
		//CGameObject* pHouse = nullptr;
		////pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\house.fbx");
		//pHouseMesh = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\rock.mdat");
		//pHouse = pHouseMesh->Instantiate();
		//pHouse->SetName(L"Rock");
		//
		//SpawnGameObject(pHouse, Vec3(0.f, 500.f, 0.f), 0);
	
	
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Player_7.fbx");
		//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\UFO_2.mdat");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"UFO_2");
		pObj->Transform()->SetRelativeScale(Vec3(30.f, 30.0f, 30.0f));
		pObj->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));
		
		SpawnGameObject(pObj, Vec3(1000.f, 500.f, 0.f), 0);
	}

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"NavObj");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"MapObject");
	CCollisionMgr::GetInst()->LayerCheck(L"PlayerProjectile", L"MapObject");
	CCollisionMgr::GetInst()->LayerCheck(L"PlayerProjectile", L"Monster");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"MonsterProjectile");
}
