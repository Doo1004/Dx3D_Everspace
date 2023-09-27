#pragma once
#include "ComponentUI.h"
class Collider3DUI :
    public ComponentUI
{
public:
    virtual int render_update() override;

private:
    COLLIDER3D_TYPE     m_Type;         // 0 = Cube, 1 = Sphere

    Vec3                m_ColliderPos;
    Vec3                m_ColliderScale;

    bool                m_bShowDebugShape;
    bool                m_bAbsolute;

public:
    Collider3DUI();
    ~Collider3DUI();
};

