#pragma once
#include "CRenderComponent.h"
class CFont :
    public CRenderComponent
{
private:
    float           m_fDT;

    wstring         m_wString;
    Vec2            m_vPos;
    Vec4            m_vColor;
    float           m_fScale;

    bool            m_bInputData;
    UINT            m_fData;

public:
    virtual void finaltick() override;
    virtual void tick() override;
    virtual void render() override;

public:
    void SetString(const wstring& _str) { m_wString = _str; };
    void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
    void SetColor(Vec4 _vColor) { m_vColor = _vColor; }
    void SetScale(float _fScale) { m_fScale = _fScale; }

    void SetInputData(bool _Set) { m_bInputData = _Set; }
    void SetData(UINT _int) { m_fData = _int; }

    wstring GetString() { return m_wString; }
    Vec2 GetPos() { return m_vPos; }
    Vec4 GetColor() { return m_vColor; }
    float GetScale() { return m_fScale; }
    bool IsUsInputData() { return m_bInputData; }
    UINT GetData() { return m_fData; }

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CFont);

public:
    CFont();
    ~CFont();
};

