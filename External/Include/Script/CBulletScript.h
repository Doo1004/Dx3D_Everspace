#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"

class CBulletScript :
    public CScript
{
private:
    CGameObject*            m_PlayerObject;
    CPlayerScript*          m_PlayerScript;

    Vec3                    m_vBulletDir;
    Vec3                    m_vBulletRot;

    Vec3                    m_vCurBulletPos;

    Vec3                    m_vAxis;                // 플레이어 방향

    float                   m_fBulletSpeed;

    bool                    m_bBulletHit;

    Vec3                    m_vCurPos;

private:
    void GetPlayerData();

public:
    void SetBulletDir(Vec3 _Dir) { m_vBulletDir = _Dir; };

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider3D* _Other) override;

    CLONE(CBulletScript);
public:
    CBulletScript();
    ~CBulletScript();
};


