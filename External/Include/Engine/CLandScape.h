#pragma once
#include "CRenderComponent.h"

#include "ptr.h"
#include "CHeightMapShader.h"
#include "CRaycastShader.h"
#include "CWeightMapShader.h"

class CLandScape :
    public CRenderComponent
{
private:
    UINT                    m_iFaceX;
    UINT                    m_iFaceZ;

    Ptr<CTexture>           m_HeightMap;

    Vec2                    m_vBrushScale;      // �귯�� ũ��(��ü ������� ũ�� ������)
    Ptr<CTexture>           m_pBrushTex;        // �귯���� �ؽ���

    Ptr<CRaycastShader>     m_pCSRaycast;       // ��ŷ ���̴�
    CStructuredBuffer*      m_pCrossBuffer;	    // ���콺 ��ŷ�Ǵ� ���� ���� �޴� ����

    Ptr<CHeightMapShader>   m_pCSHeightMap;     // ���̸� ���̴�
    Ptr<CTexture>           m_pHeightMap;       // ���̸� �ؽ���

    Ptr<CWeightMapShader>   m_pCSWeightMap;     // ����ġ ���̴�
    CStructuredBuffer*      m_pWeightMapBuffer; // ����ġ ���� ����
    UINT					m_iWeightWidth;		// ����ġ ���� ���μ��� ��� ��
    UINT					m_iWeightHeight;	// ����ġ ���� ���μ��� ��� ��
    UINT                    m_iWeightIdx;		// ���� ��ų ����ġ ����

    LANDSCAPE_MOD           m_eMod; 	        // ���� ����忡�� ���°�

    Ptr<CTexture>           m_pTileArrTex;      // Ÿ�� �迭 �ؽ���

    bool                    m_bShowWire;
    UINT                    m_EditMod;

public:
    void SetFace(UINT _iFaceX, UINT _iFaceZ);
    void SetHeightMap(Ptr<CTexture> _HeightMap) { m_HeightMap = _HeightMap; }

    void SetShowWire(bool _bShow) { m_bShowWire = _bShow; }
    bool IsUseShowWire() { return m_bShowWire; }

    void SetEditMod(UINT _iMod) { m_EditMod = _iMod; }

    void SetBrushTex(Ptr<CTexture> _Tex) { m_pBrushTex = _Tex; }
    Ptr<CTexture> GetBrushTex() { return m_pBrushTex; }

    void SetBrushScale(Vec2 _Scale) { m_vBrushScale = _Scale; }
    Vec2 GetBrushScale() { return m_vBrushScale; }

    void SetTileTex(Ptr<CTexture> _Tex) { m_pTileArrTex = _Tex; }
    Ptr<CTexture> GetTileTex() { return m_pTileArrTex; }

    virtual void finaltick() override;
    virtual void render() override;
    virtual void render_depthmap() override;

private:
    void init();
    void CreateMesh();
    void CreateComputeShader();
    void CreateTexture();

    void Raycasting();

    CLONE(CLandScape);
public:
    CLandScape();
    ~CLandScape();
};

