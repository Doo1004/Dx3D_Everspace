#pragma once
#include <Engine\CScript.h>

class CDistantScript :
    public CScript
{
private:
    CGameObject*        m_pPlayer;
    Vec3                m_vOffsetPos;

    void GetSkyBoxData();

public:
    virtual void tick() override;
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CDistantScript);
public:
    CDistantScript();
    ~CDistantScript();
};

