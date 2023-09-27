#pragma once
#include "ComponentUI.h"
class LandScapeUI :
    public ComponentUI
{

public:
    virtual int render_update() override;

private:
    bool                            m_bShowWireFrame;
    bool                            m_bSetHeightMap;
    bool                            m_bSetSplat;
    bool                            m_bBrushSetMode;

    UINT                            m_EditMod;

    ID3D11ShaderResourceView* m_BrushPreviewTexture;
    ID3D11ShaderResourceView* m_TilePreviewTexture;
    Ptr<CTexture>                   m_BrushTexture;
    Ptr<CTexture>                   m_TileTexture;

    float                           m_BrushTexWidth;
    float                           m_BrushTexHeight;
    float                           m_TileTexWidth;
    float                           m_TileTexHeight;

    Vec3                            m_HeightBtnColor;
    Vec3                            m_SplatBtnColor;

    float                           m_BrushScale[1];

private:
    void SetBtnColor();
    void ChangeTexture(ID3D11ShaderResourceView*& _PrevTex, Ptr<CTexture>& _Tex, float& _Width, float& _Height);

public:
    LandScapeUI();
    ~LandScapeUI();
};

