#pragma once
#include "CRenderComponent.h"

#include "ptr.h"
#include "CParticleUpdateShader.h"

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer*          m_ParticleBuffer;
    CStructuredBuffer*          m_RWBuffer;
    CStructuredBuffer*          m_ModuleDataBuffer;

    tParticleModule             m_ModuleData;
    Ptr<CParticleUpdateShader>  m_UpdateCS;

    float                       m_AccTime;
    bool                        m_bShowDebugShape;

public:
    bool    IsShowDebugShape() { return m_bShowDebugShape; }
    void    SetShowDebugShape(bool _bShow) { m_bShowDebugShape = _bShow; }


    void    SetSpawnEnable(bool _Enable) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = _Enable; }
    void    SetColorChangeEnable(bool _Enable) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE] = _Enable; }
    void    SetScaleChangeEnable(bool _Enable) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE] = _Enable; }
    void    SetAddVelocityEnable(bool _Enable) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = _Enable; }
    void    SetDragEnable(bool _Enable) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::DRAG] = _Enable; }
    void    SetNoiseForceEnable(bool _Enable) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = _Enable; }
    void    SetRenderEnable(bool _Enable) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = _Enable; }

    bool    GetSpawnEnable() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN]; }
    bool    GetColorChangeEnable() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE]; }
    bool    GetScaleChangeEnable() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE]; }
    bool    GetAddVelocityEnable() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY]; }
    bool    GetDragEnable() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::DRAG]; }
    bool    GetNoiseForceEnable() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE]; }
    bool    GetRenderEnable() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER]; }

    /////////////////////////////////////////////////////////////////////////////////////

    void    SetMaxParticle(int _MaxParticle) { m_ModuleData.iMaxParticleCount = _MaxParticle; }
    void    SetSpawnRate(int _SpawnRate) { m_ModuleData.SpawnRate = _SpawnRate; }
    void    SetSpawnColor(Vec4 _SpawnColor) { m_ModuleData.vSpawnColor = _SpawnColor; }
    void    SetSpawnScaleMin(Vec3 _ScaleMin) { m_ModuleData.vSpawnScaleMin = _ScaleMin; }
    void    SetSpawnScaleMax(Vec3 _ScaleMax) { m_ModuleData.vSpawnScaleMax = _ScaleMax; }
    void    SetShapeType(int _ShapeType) { m_ModuleData.SpawnShapeType = _ShapeType; }
    void    SetShapeScale(Vec3 _ShapeScale) { m_ModuleData.vBoxShapeScale = _ShapeScale; }
    void    SetMinLifeTime(float _MinLifeTime) { m_ModuleData.MinLifeTime = _MinLifeTime; }
    void    SetMaxLifeTime(float _MaxLifeTime) { m_ModuleData.MaxLifeTime = _MaxLifeTime; }
    void    SetStartScale(float _StartScale) { m_ModuleData.StartScale = _StartScale; }
    void    SetEndScale(float _EndScale) { m_ModuleData.EndScale = _EndScale; }
    void    SetStartColor(Vec4 _StartColor) { m_ModuleData.vStartColor = _StartColor; }
    void    SetEndColor(Vec4 _EndColor) { m_ModuleData.vEndColor = _EndColor; }
    void    SetAddVelocityType(int _Type) { m_ModuleData.AddVelocityType = _Type; }
    void    SetSpeed(float _Speed) { m_ModuleData.Speed = _Speed; }
    void    SetVelocityDir(Vec3 _Dir) { m_ModuleData.vVelocityDir = _Dir; }
    void    SetOffsetAngle(float _Angle) { m_ModuleData.OffsetAngle = _Angle; }
    void    SetStartDrag(float _StartDrag) { m_ModuleData.StartDrag = _StartDrag; }
    void    SetEndDrag(float _EndDrag) { m_ModuleData.EndDrag = _EndDrag; }
    void    SetNoiseTerm(float _Term) { m_ModuleData.fNoiseTerm = _Term; }
    void    SetNoiseForce(float _Force) { m_ModuleData.fNoiseForce = _Force; }
    void    SetVelocityAlignment(bool _Set) { m_ModuleData.VelocityAlignment = _Set; }
    void    SetVelocityScale(bool _Set) { m_ModuleData.VelocityScale = _Set; }
    void    SetMaxVelocityScale(Vec3 _Scale) { m_ModuleData.vMaxVelocityScale = _Scale; }
    void    SetMaxSpeed(float _Speed) { m_ModuleData.vMaxSpeed = _Speed; }

    int     GetMaxParticle() { return m_ModuleData.iMaxParticleCount; }
    int     GetSpawnRate() { return m_ModuleData.SpawnRate; }
    Vec4    GetSpawnColor() { return m_ModuleData.vSpawnColor; }
    Vec3    GetSpawnScaleMin() { return m_ModuleData.vSpawnScaleMin; }
    Vec3    GetSpawnScaleMax() { return m_ModuleData.vSpawnScaleMax; }
    int     GetShapeType() { return m_ModuleData.SpawnShapeType; }
    Vec3    GetShapeScale() { return m_ModuleData.vBoxShapeScale; }
    float   GetMinLifeTime() { return m_ModuleData.MinLifeTime; }
    float   GetMaxLifeTime() { return m_ModuleData.MaxLifeTime; }
    float   GetStartScale() { return m_ModuleData.StartScale; }
    float   GetEndScale() { return m_ModuleData.EndScale; }
    Vec4    GetStartColor() { return m_ModuleData.vStartColor; }
    Vec4    GetEndColor() { return m_ModuleData.vEndColor; }
    int     GetAddVelocityType() { return m_ModuleData.AddVelocityType; }
    float   GetSpeed() { return m_ModuleData.Speed; }
    Vec3    GetVelocityDir() { return m_ModuleData.vVelocityDir; }
    float   GetOffsetAngle() { return m_ModuleData.OffsetAngle; }
    float   GetStartDrag() { return m_ModuleData.StartDrag; }
    float   GetEndDrag() { return m_ModuleData.EndDrag; }
    float   GetNoiseTerm() { return m_ModuleData.fNoiseTerm; }
    float   GetNoiseForce() { return m_ModuleData.fNoiseForce; }
    bool    GetVelocityAlignment() { return m_ModuleData.VelocityAlignment; }
    bool    GetVelocityScale() { return m_ModuleData.VelocityScale; }
    Vec3    GetMaxVelocityScale() { return m_ModuleData.vMaxVelocityScale; }
    float   GetMaxSpeed() { return m_ModuleData.vMaxSpeed; }


public:
    virtual void finaltick() override;
    virtual void render() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CParticleSystem);
public:
    CParticleSystem();
    ~CParticleSystem();
};

