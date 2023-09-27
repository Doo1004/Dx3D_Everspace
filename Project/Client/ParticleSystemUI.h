#pragma once
#include "ComponentUI.h"
class ParticleSystemUI :
    public ComponentUI
{
public:
    virtual int render_update() override;

public:
    ParticleSystemUI();
    ~ParticleSystemUI();

private:
    bool            m_SpawnEnable;
    bool            m_ColorChangeEnable;
    bool            m_ScaleChangeEnable;
    bool            m_AddVelocityEnable;
    bool            m_DragEnable;
    bool            m_NoiseForceEnable;
    bool            m_RenderEnable;
    bool            m_ShowDebugShape;


    int             m_MaxParticle;
    int             m_SpawnRate;
    Vec4            m_SpawnColor;
    Vec3            m_ScaleMin;
    Vec3            m_ScaleMax;
    int             m_ShapeType;
    Vec3            m_ShapeScale;
    Vec3            m_LifeTime;
    Vec4            m_StartColor;
    Vec4            m_EndColor;
    Vec3            m_ScaleChangeData;
    int             m_AddVelocityType;
    float           m_Speed;
    Vec3            m_VelocityDir;
    float           m_OffsetAngle;
    float           m_StartDrag;
    float           m_EndDrag;
    float           m_NoiseTerm;
    float           m_NoiseForce;
    bool            m_VelocityAlignment;
    bool            m_VelocityScale;
    Vec3            m_MaxVelocityScale;
    float           m_MaxSpeed;


    //////////////////////////////////////////////////////////////////¹öÆ° »ö±ò
    Vec3            m_AlignmentBtnColor;
    Vec3            m_ScaleBtnColor;
    Vec3            m_BoxBtnColor;
    Vec3            m_CubeBtnColor;
    Vec3            m_FromCenterBtnColor;
    Vec3            m_ToCenterBtnColor;
    Vec3            m_DirectionBtnColor;




private:
    void GetTargetData();
    void SetTargetData();
    void SetChangeButtonColor();
};

