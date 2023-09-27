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
    float               m_fMaxSpeed;            // 최고 속력
    float               m_fSpeed;               // 현재 속도
    float               m_fPlayerSpeed;         // 최고 속력과 현재 속도의 비율
    float               m_fAccel;
    float               m_fBreak;
    float               m_fPitch;
    float               m_fRoll;
    float               m_fYaw;
    float               m_fBulletDelay;         // Attack 딜레이

    bool                m_AccelEnable;          // 플레이어 엑셀
    bool                m_BreakEnable;          // 플레이어 브레이크

    int                 m_iHP;                  // 플레이어 체력

    PLAYER_PITCH        m_ePitch;               // 플레이어 기체 상승 & 하강
    PLAYER_ROLL         m_eRoll;                // 플레이어 기체 상승 & 하강
    PLAYER_YAW          m_eYaw;                 // 플레이어 방향 전환

    Vec3                m_CurPos;
    Vec3                m_PrevPos;
    Vec3                m_MoveDir;              // 플레이어의 움직임 방향
    Vec3                m_DefaultRot;           // 플레이어의 기본 회전값

    Vec3                m_vAxis;                // 플레이어 방향

    Vec3                m_vNoisePos;            // 데미지를 받은 카메라 랜덤 난수


    //=====================CameraView================//
    bool                m_bBackView;            // 플레이어 시야 전환
    bool                m_bBoost;               // 플레이어 부스트
    bool                m_bDamage;              // 플레이어 데미지 
    float               m_fDamageDT;            // 플레이어 카메라 흔들리는 시간

    //=====================Attack===================//
    CGameObject*        m_MuzzleObj_1;          // 1번 총구
    CGameObject*        m_MuzzleObj_2;          // 2번 총구
    CMuzzleScript*      m_MuzzleScript_1;
    CMuzzleScript*      m_MuzzleScript_2;

    //======================Text====================//
    CGameObject*        m_NaviText;             // 위치 표시
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

