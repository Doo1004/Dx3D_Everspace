#pragma once
#include "UI.h"
class LayerUI :
    public UI
{
public:
    virtual void finaltick() override;
    virtual int render_update() override;

private:
    string              m_LayerName[32];
    string              m_LayerName1;
    string              m_LayerName2;
    int                 m_SelectedNum;
    int                 m_SelectedLayer1;
    int                 m_SelectedLayer2;
    bool                m_Layer1EditMode;
    bool                m_Layer2EditMode;

private:
    void ShowLayerList();

public:
    void Reset(const string& _strName, ImVec2 _vSize);

public:
    LayerUI();
    ~LayerUI();
};

