#pragma once
#include <Engine\CScript.h>

class CMapObjectScript :
    public CScript
{
private:
    CGameObject*        m_pPlayer;

    Vec3                m_vOffsetPos;
    Vec3                m_vRotPos;


    bool                m_bDistant;
    bool                m_bRotation;

    void GetPlayerData();

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CMapObjectScript);

public:
    CMapObjectScript();
    ~CMapObjectScript();
};

