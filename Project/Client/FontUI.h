#pragma once
#include "ComponentUI.h"
class FontUI :
    public ComponentUI
{
private:
    Vec3            m_vPos;
    Vec4            m_vColor;
    float           m_fTime;
    float           m_fScale;
    string          m_sText;


public:
    virtual int render_update() override;

public:
    FontUI();
    ~FontUI();
};

