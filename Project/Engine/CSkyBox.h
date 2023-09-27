#pragma once
#include "CRenderComponent.h"

enum class SKYBOX_TYPE
{
    SPHERE,
    CUBE,
};


class CSkyBox :
    public CRenderComponent
{
private:
    SKYBOX_TYPE     m_Type;
    Ptr<CTexture>   m_SkyTex;


public:
    void SetType(SKYBOX_TYPE _Type);
    void SetSkyTexture(Ptr<CTexture> _SkyTex) { m_SkyTex = _SkyTex; }

    Ptr<CTexture> GetSkyTexture() { return m_SkyTex; }

    SKYBOX_TYPE GetBoxType() { return m_Type; }

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


public:
    virtual void finaltick() override;
    virtual void render() override;

    CLONE(CSkyBox);
public:
    CSkyBox();
    ~CSkyBox();
};

