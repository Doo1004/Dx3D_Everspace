#pragma once
#include "ComponentUI.h"
class Light3DUI :
    public ComponentUI
{

public:
    virtual int render_update() override;

private:
    Vec4                m_Diffuse;
    Vec4                m_Specular;
    Vec4                m_Ambient;
    Vec4                m_Direction;

    LIGHT_TYPE          m_LightType;
    Vec3                m_LightDiffuse;
    float               m_LightAngle;
    Vec3                m_LightSpecular;
    Vec3                m_LightAmbient;
    float               m_LightRadius;
    Vec3                m_LightDirection;

    bool                m_ShowDebugMesh;

public:
    Light3DUI();
    ~Light3DUI();
};

