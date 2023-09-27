#pragma once
#include "CRenderComponent.h"

class CDecal :
    public CRenderComponent
{
private:
    Ptr<CTexture>   m_DecalTex;
    Ptr<CMaterial>  m_DecalMtrl;
    int             m_Light;
    int             m_DebugColorEnable;
    bool            m_DebugShapeEnable;
    Vec4            m_DecalColor;

public:
    void SetAsLight(bool _bLight) { m_Light = _bLight; }
    void SetOutputTexture(Ptr<CTexture> _Tex) { m_DecalTex = _Tex; }
    void SetDebugShape(bool _enable) { m_DebugShapeEnable = _enable; }
    void SetDecalColor(Vec4 _color) { m_DecalColor = _color; }
    void SetDebugColor(bool _debug) { m_DebugColorEnable = _debug; }

    bool GetAsLight() { return m_Light; }
    bool GetDebugShape() { return m_DebugShapeEnable; }
    bool GetDebugColor() { return m_DebugColorEnable; }
    Ptr<CTexture> GetOutputTexture() { return m_DecalTex; }
    Ptr<CMaterial> GetDecalMtrl() { return m_DecalMtrl; }
    Vec4 GetDecalColor() { return m_DecalColor; }

    virtual void finaltick() override;
    virtual void render() override;

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


    CLONE(CDecal);

public:
    CDecal();
    ~CDecal();
};