#pragma once
#include <Engine\CScript.h>

class CMuzzleScript :
    public CScript
{
private:
    Vec3            m_vMuzzlePos;     // �ѱ� ��ġ

public:
    void CreateBullet();
    Vec3 GetMuzzlePos() { return m_vMuzzlePos; };

public:
    virtual void begin() override;
    virtual void tick() override;
    CLONE(CMuzzleScript);

public:
    CMuzzleScript();
    ~CMuzzleScript();
};

