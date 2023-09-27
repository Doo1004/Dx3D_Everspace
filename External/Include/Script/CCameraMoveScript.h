#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"

class CCameraMoveScript :
    public CScript
{
private:
    CLevel* m_CurLevel;
    CGameObject* m_PlayerObject;
    CPlayerScript* m_PlayerScript;

    float               m_fCamSpeed;
    Vec3                m_vCameraRot;
    Vec3                m_vCameraPos;;

    Vec3                m_vPlayerRot;
    Vec3                m_vDamageRot;
    float               m_fDamageTime;

    //=====================CameraView================//
    float               m_fPlayerSpeed;         // 플레이어 스피드(에 따른 카메라 움직임)
    float               m_fPlayerBreak;         // 플레이어 브레이크(에 따른 카메라 움직임)
    float               m_fPlayerFlip;          // 플레이어 기체 방향

    bool                m_bBackView;            // 플레이어 시야 전환
    bool                m_bBoost;               // 플레이어 부스트
    bool                m_bDamage;              // 플레이어 데미지 

    float               m_fBackViewPos;
    float               m_fBackViewRot;



public:
    virtual void begin() override;
    virtual void tick() override;

private:
    void CameraEditMode();
    void CameraPlayMode();
    void GetPlayerData();
    void GetPlayerState();


    CLONE(CCameraMoveScript);
public:
    CCameraMoveScript();
    ~CCameraMoveScript();
};
