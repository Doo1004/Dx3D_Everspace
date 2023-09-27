#pragma once
#include "UI.h"


class MenuUI :
    public UI
{
private:
    string          m_ObjectName;
    string          m_LevelName;
    string          m_MtrlName;

    int             m_Layer;

    bool            m_Std2D;
    bool            m_Std3D;
    bool            m_Std3DUI;
    bool            m_Distortion;

public:
    virtual void finaltick() override;
    virtual int render_update() override;


private:
    void CreateEmptyObject(const wstring& _ObjName, int _layer);
    void AddComponent(COMPONENT_TYPE _type);
    void AddScript(const wstring& _strScriptName);

public:
    MenuUI();
    ~MenuUI();
};

