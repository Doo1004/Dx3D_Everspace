#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"

class CBackFireScript :
    public CScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

private:
    CGameObject*        m_PlayerObject;
    CPlayerScript*      m_PlayerScript;

    float               m_fPlayerSpeed;         // 플레이어 스피드
    float               m_fParticleLife;        // 파티클 라이프 테스트 
    float               m_fPlayerMaxSpeed;

private:
    void GetPlayerData();
    void GetPlayerState();

private:
    CLONE(CBackFireScript);
public:
    CBackFireScript();
    ~CBackFireScript();
};

