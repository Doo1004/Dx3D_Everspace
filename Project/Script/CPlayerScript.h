#pragma once
#include <Engine\CScript.h>
#include "CMuzzleScript.h"

class CPlayerScript :
    public CScript
{
    enum class PLAYER_PITCH
    {
        IDLE,
        UP,
        DOWN,
    };

    enum class PLAYER_ROLL
    {
        IDLE,
        LEFT,
        RIGHT,
    };

    enum class PLAYER_YAW
    {
        IDLE,
        LEFT,
        RIGHT,
    };

private:
    float               m_fMaxSpeed;            // �ְ� �ӷ�
    float               m_fSpeed;               // ���� �ӵ�
    float               m_fPlayerSpeed;         // �ְ� �ӷ°� ���� �ӵ��� ����
    float               m_fAccel;
    float               m_fBreak;
    float               m_fPitch;
    float               m_fRoll;
    float               m_fYaw;
    float               m_fBulletDelay;         // Attack ������

    bool                m_AccelEnable;          // �÷��̾� ����
    bool                m_BreakEnable;          // �÷��̾� �극��ũ

    int                 m_iHP;                  // �÷��̾� ü��

    PLAYER_PITCH        m_ePitch;               // �÷��̾� ��ü ��� & �ϰ�
    PLAYER_ROLL         m_eRoll;                // �÷��̾� ��ü ��� & �ϰ�
    PLAYER_YAW          m_eYaw;                 // �÷��̾� ���� ��ȯ

    Vec3                m_CurPos;
    Vec3                m_PrevPos;
    Vec3                m_MoveDir;              // �÷��̾��� ������ ����
    Vec3                m_DefaultRot;           // �÷��̾��� �⺻ ȸ����

    Vec3                m_vAxis;                // �÷��̾� ����

    Vec3                m_vNoisePos;            // �������� ���� ī�޶� ���� ����


    //=====================CameraView================//
    bool                m_bBackView;            // �÷��̾� �þ� ��ȯ
    bool                m_bBoost;               // �÷��̾� �ν�Ʈ
    bool                m_bDamage;              // �÷��̾� ������ 
    float               m_fDamageDT;            // �÷��̾� ī�޶� ��鸮�� �ð�

    //=====================Attack===================//
    CGameObject*        m_MuzzleObj_1;          // 1�� �ѱ�
    CGameObject*        m_MuzzleObj_2;          // 2�� �ѱ�
    CMuzzleScript*      m_MuzzleScript_1;
    CMuzzleScript*      m_MuzzleScript_2;

    //======================Text====================//
    CGameObject*        m_NaviText;             // ��ġ ǥ��
    CSound*             m_sEngineSound;
    CSound*             m_sBGM;

    UINT			    m_iCallCount;
    float			    m_fDeltaTime;
    float			    m_fTime;

public:
    bool IsBackView() { return m_bBackView; }
    bool IsBoost() { return m_bBoost; }
    bool IsDamage() { return m_bDamage; }
    float GetDamageTime() { return m_fDamageDT; }
    float GetPlayerSpeed() { return m_fPlayerSpeed; }
    float GetPlayerMaxSpeed() { return m_fMaxSpeed; }
    float GetPlayerBreak() { return m_fBreak; }
    Vec3 GetAxis() { return m_vAxis; }
    Vec3 GetPitchRollYaw() { return Vec3( -m_fPitch * 10, m_fRoll * 10, m_fYaw * 10); }
    Vec3 GetDamageCameraPos() { return m_vNoisePos; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;

private:
    void PlayerMove();
    void PlayerAccel();
    void PlayerRotation();
    void PlayerFunction();
    void CreateText();

    //void CreateAim();
    void GetMuzzleData();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CPlayerScript);

public:
    CPlayerScript();
    ~CPlayerScript();
};

