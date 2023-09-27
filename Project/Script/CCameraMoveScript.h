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
    float               m_fPlayerSpeed;         // �÷��̾� ���ǵ�(�� ���� ī�޶� ������)
    float               m_fPlayerBreak;         // �÷��̾� �극��ũ(�� ���� ī�޶� ������)
    float               m_fPlayerFlip;          // �÷��̾� ��ü ����

    bool                m_bBackView;            // �÷��̾� �þ� ��ȯ
    bool                m_bBoost;               // �÷��̾� �ν�Ʈ
    bool                m_bDamage;              // �÷��̾� ������ 

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
