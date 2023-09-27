#pragma once
#include <Engine\CScript.h>

class CExplosionScript :
    public CScript
{
private:
    float       m_fMaxLifeTime;
    float       m_fCurLifeTime;

    float       m_fScale;

    float       m_fDistance;

    int         m_iSpawnRate;

    void SetParticle();
    void SetLight();

public:
    void SetPlayerDist(float _fDist) { m_fDistance = _fDist; }
    void SetLifeTime(float _fTime) { m_fMaxLifeTime = _fTime; }
    void SetScale(float _vScale) { m_fScale = _vScale; }

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CExplosionScript);
public:
    CExplosionScript();
    ~CExplosionScript();
};

