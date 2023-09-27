#pragma once
#include <Engine\CScript.h>

class CNavObjScript :
    public CScript
{
private:
    CGameObject*        m_pPlayerObject;
    CGameObject*        m_pNaviText;
    CLevel*             m_pCurLevel;

    Vec3                m_vCurPos;
    Vec3                m_vCalculPos;
    Vec3                m_vCurScale;

    int                 m_iDir;
    int                 m_iScale;

    float               m_fTimer;
    float               m_fRot;
    float               m_fDistance;
    float               m_fDistanceDesired;

    int                 m_iMonster;

    bool                m_bTextOn;
    bool                m_bStageOn;

    float               m_fDT;

    void GetPlayerData();
    void CreateNaviText();
    void CreateMonster(int _MobNum);
    void CreateNextNavi();
    void SetTextData();

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider3D* _Other) override;

    CLONE(CNavObjScript);
public:
    CNavObjScript();
    ~CNavObjScript();
};

