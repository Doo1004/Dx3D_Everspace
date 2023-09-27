#pragma once
#include <Engine\CScript.h>

class CHPBarScript :
    public CScript
{
private:
    CGameObject*    m_pCamera;

    Vec3            m_vCurPos;
    float           m_fHPRatio;
    bool            m_bBoss;

    void GetCameraObj();

    Vec3 ExtractEulerAngles(const XMMATRIX& rotationMatrix)
    {
        float yaw, pitch, roll;
        // Assuming the angles are in radians.
        if (rotationMatrix.r[1].m128_f32[0] > 0.998) { // singularity at north pole
            yaw = atan2(rotationMatrix.r[0].m128_f32[2], rotationMatrix.r[2].m128_f32[2]);
            pitch = DirectX::XM_PI / 2;
            roll = 0;
        }
        else if (rotationMatrix.r[1].m128_f32[0] < -0.998) { // singularity at south pole
            yaw = atan2(rotationMatrix.r[0].m128_f32[2], rotationMatrix.r[2].m128_f32[2]);
            pitch = -DirectX::XM_PI / 2;
            roll = 0;
        }
        else
        {
            yaw = atan2(-rotationMatrix.r[2].m128_f32[0], rotationMatrix.r[0].m128_f32[0]);
            pitch = asin(rotationMatrix.r[1].m128_f32[0]);
            roll = atan2(-rotationMatrix.r[1].m128_f32[2], rotationMatrix.r[1].m128_f32[1]);
        }
        return Vec3(pitch, yaw, roll);
    }


public:
    void SetPos(Vec3 _vPos) { m_vCurPos = _vPos; }
    void SetBossEnable(bool _bBoss) { m_bBoss = _bBoss; }
    void SetHPRatio(float _fRatio) { m_fHPRatio = _fRatio; }

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CHPBarScript);
public:
    CHPBarScript();
    ~CHPBarScript();
};

