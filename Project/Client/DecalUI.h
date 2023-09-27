#pragma once
#include "ComponentUI.h"
class DecalUI :
    public ComponentUI
{

public:
    virtual int render_update() override;

private:
    bool                        m_AsLight;
    bool                        m_DebugEnable;
    bool                        m_DebugColorEnable;
    Ptr<CTexture>               m_DecalTexture;
    Ptr<CGraphicsShader>        m_DecalShader;
    ID3D11ShaderResourceView* m_PreviewTexture;
    float                       m_TextureWidth;
    float                       m_TextureHeight;
    Vec4                        m_DecalColor;


private:
    void ChangeTexture();

public:
    DecalUI();
    ~DecalUI();
};

