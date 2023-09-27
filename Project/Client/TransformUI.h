#pragma once
#include "ComponentUI.h"

class CGameObject;

class TransformUI :
    public ComponentUI
{
public:
    virtual int render_update() override;

private:
    string          m_ObjName;
    Vec3            m_vPos;
    Vec3            m_vScale;
    Vec3            m_vRotation;
    bool            m_bAbsolute;
    bool            m_bQuaternion;

public:
    TransformUI();
    ~TransformUI();
};

