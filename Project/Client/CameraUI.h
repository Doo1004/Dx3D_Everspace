#pragma once
#include "ComponentUI.h"
class CameraUI :
    public ComponentUI
{

public:
    virtual int render_update() override;

private:
    bool        m_UseCameraDebugShape;
    float       m_CameraDebugScale;

    int         m_iLayer;
    bool        m_bLayerCheck;

    int         m_iIndex;

    UINT        m_iProjType;

public:
    CameraUI();
    ~CameraUI();
};

