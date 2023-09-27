#pragma once
#include "ComponentUI.h"

class ParticleDetailSetUI :
    public UI
{
public:
    virtual int render_update() override;

public:
    void Reset(const string& _strName, ImVec2 _vSize);

private:
    bool            m_ColorChangeEnable;
    bool            m_ScaleChangeEnable;
    bool            m_AddVelocityEnable;
    bool            m_DragEnable;
    bool            m_NoiseForceEnable;
    bool            m_RenderEnable;

    Vec3            m_StartColor;
    Vec3            m_EndColor;
    Vec3            m_ScaleChangeData;
    int             m_AddVelocityType;
    float           m_Speed;
    float           m_StartDrag;
    float           m_EndDrag;
    float           m_NoiseTerm;
    float           m_NoiseForce;

public:
    bool            GetDtColorChangeEnable() { return m_ColorChangeEnable; }
    bool            GetDtScaleChangeEnable() { return m_ScaleChangeEnable; }
    bool            GetDtAddVelocityEnable() { return m_AddVelocityEnable; }
    bool            GetDtDragEnable() { return m_DragEnable; }
    bool            GetDtNoiseForceEnable() { return m_NoiseForceEnable; }
    bool            GetDtRenderEnable() { return m_RenderEnable; }

    Vec3            GetDtScaleChangeData() { return m_ScaleChangeData; }
    Vec3            GetDtStartColor() { return m_StartColor; }
    Vec3            GetDtEndColor() { return m_EndColor; }
    int             GetDtAddVelocityType() { return m_AddVelocityType; }
    float           GetDtSpeed() { return m_Speed; }
    float           GetDtStartDrag() { return m_StartDrag; }
    float           GetDtEndDrag() { return m_EndDrag; }
    float           GetDtNoiseTerm() { return m_NoiseTerm; }
    float           GetDtNoiseForce() { return m_NoiseForce; }

public:
    ParticleDetailSetUI();
    ~ParticleDetailSetUI();
};

