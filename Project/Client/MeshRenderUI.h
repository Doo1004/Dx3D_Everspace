#pragma once
#include "ComponentUI.h"

class MeshRenderUI :
    public ComponentUI
{

public:
    virtual int render_update() override;


public:
    void SelectMesh(DWORD_PTR _Key);
    void SelectMaterial(DWORD_PTR _Key);

private:
    bool        m_SetFrustum;
    bool        m_ShowDebugShape;
    float       m_Bounding;

public:
    MeshRenderUI();
    ~MeshRenderUI();
};

