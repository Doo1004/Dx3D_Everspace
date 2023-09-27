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

    float               m_fPlayerSpeed;         // �÷��̾� ���ǵ�
    float               m_fParticleLife;        // ��ƼŬ ������ �׽�Ʈ 
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

