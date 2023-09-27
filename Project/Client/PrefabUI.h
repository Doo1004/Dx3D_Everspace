#pragma once
#include "ResUI.h"
class PrefabUI :
    public ResUI
{
private:
    int                     m_Layer;

    Ptr<CPrefab>            m_LoadedPrefab;

public:
    virtual int render_update() override;

public:
    PrefabUI();
    ~PrefabUI();
};

