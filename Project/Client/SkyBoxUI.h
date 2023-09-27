#pragma once
#include "ComponentUI.h"
class SkyBoxUI :
    public ComponentUI
{

public:
    virtual int render_update() override;

private:
    Ptr<CTexture>               m_SkyTexture;
    ID3D11ShaderResourceView* m_PreviewTexture;

    float                       m_TextureWidth;
    float                       m_TextureHeight;

    UINT                        m_BoxType;

private:
    void ChangeTexture();

public:
    SkyBoxUI();
    ~SkyBoxUI();
};

