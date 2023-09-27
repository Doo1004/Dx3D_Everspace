#include "pch.h"
#include "LandScapeUI.h"
#include "TreeUI.h"
#include <Engine\CLandScape.h>

LandScapeUI::LandScapeUI()
    : ComponentUI("##LandScape", COMPONENT_TYPE::LANDSCAPE)
    , m_EditMod(0)
{
    SetName("LandScape");
}

LandScapeUI::~LandScapeUI()
{
}


int LandScapeUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                                         // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                                         // Lower-right
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);                           // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);                         // 50% opaque white
    ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);                             // Black background
    if (nullptr == m_BrushTexture)
        if (GetTarget()->LandScape()->GetBrushTex().Get())
            m_BrushTexture = GetTarget()->LandScape()->GetBrushTex();
    if (nullptr == m_TileTexture)
        if (GetTarget()->LandScape()->GetTileTex().Get())
            m_TileTexture = GetTarget()->LandScape()->GetTileTex();
    m_bShowWireFrame = GetTarget()->LandScape()->IsUseShowWire();
    if (m_BrushScale[0] <= 0.f)
    {
        m_BrushScale[0] = GetTarget()->LandScape()->GetBrushScale().x;
        m_BrushScale[1] = GetTarget()->LandScape()->GetBrushScale().y;
    }

    //======================================WireFrame===========================================//
    ImGui::Text("ShowWireFrame ");
    ImGui::SameLine(100);
    ImGui::Checkbox("##ShowWireFrame", &m_bShowWireFrame);
    GetTarget()->LandScape()->SetShowWire(m_bShowWireFrame);
    //======================================EditMod============================================//
    SetBtnColor();

    ImGui::Text("EditLandScape ");
    ImGui::SameLine(100);
    UIColorButton(m_HeightBtnColor);
    if (ImGui::Button("HeightMap", ImVec2(100.f, 18.f)))
    {
        if (m_EditMod == 1)
            m_EditMod = 0;
        else
            m_EditMod = 1;
    }
    ImGui::PopStyleColor(3);
    ImGui::PopID();

    ImGui::SameLine();

    UIColorButton(m_SplatBtnColor);
    if (ImGui::Button("Splat", ImVec2(100.f, 18.f)))
    {
        if (m_EditMod == 2)
            m_EditMod = 0;
        else
            m_EditMod = 2;
    }
    ImGui::PopStyleColor(3);
    ImGui::PopID();

    GetTarget()->LandScape()->SetEditMod(m_EditMod);
    //=======================================Brush============================================//
    ImGui::Text("Set Brush");
    ImGui::SameLine();
    ImGui::Checkbox("##Brush", &m_bBrushSetMode);

    if (m_bBrushSetMode)
    {
        ImGui::SameLine(100);
        ImGui::Text("BrushTex");
        ImGui::SameLine(170);
        ImGui::Image(m_BrushPreviewTexture, ImVec2(m_BrushTexWidth, m_BrushTexHeight), uv_min, uv_max, tint_col, border_col);
        ChangeTexture(m_BrushPreviewTexture, m_BrushTexture, m_BrushTexWidth, m_BrushTexHeight);
        if (m_BrushTexWidth >= 100.f)
        {
            m_BrushTexHeight = m_BrushTexHeight / (m_BrushTexWidth / 100.f);
            m_BrushTexWidth = 100.f;
        }
        ImGui::SameLine(280);
        if (ImGui::Button("Set##1"))
            GetTarget()->LandScape()->SetBrushTex(m_BrushTexture);

        ImGui::Text(" ");
        ImGui::SameLine(100);
        ImGui::Text("BrushSize");
        ImGui::SameLine(170);
        ImGui::SetNextItemWidth(100);
        ImGui::InputFloat2("##BrushScale", m_BrushScale);
        ImGui::SameLine(280);
        if (ImGui::Button("Set##2"))
            GetTarget()->LandScape()->SetBrushScale(Vec2(m_BrushScale[0], m_BrushScale[1]));

        ImGui::Text(" ");
        ImGui::SameLine(100);
        ImGui::Text("TileTex");
        ImGui::SameLine(170);
        ImGui::Image(m_TilePreviewTexture, ImVec2(m_TileTexWidth, m_TileTexHeight), uv_min, uv_max, tint_col, border_col);
        ChangeTexture(m_TilePreviewTexture, m_TileTexture, m_TileTexWidth, m_TileTexHeight);
        if (m_TileTexWidth >= 100.f)
        {
            m_TileTexHeight = m_TileTexHeight / (m_TileTexWidth / 100.f);
            m_TileTexWidth = 100.f;
        }
        ImGui::SameLine(280);
        if (ImGui::Button("Set##3"))
            GetTarget()->LandScape()->SetTileTex(m_TileTexture);

    }
    return TRUE;
}

void LandScapeUI::SetBtnColor()
{
    if (m_EditMod == 1)
        m_HeightBtnColor = Vec3(0.4f, 1.f, 0.4f);
    else if (m_EditMod != 1)
        m_HeightBtnColor = Vec3(1.f, 0.6f, 1.f);

    if (m_EditMod == 2)
        m_SplatBtnColor = Vec3(0.4f, 1.f, 0.4f);
    else if (m_EditMod != 2)
        m_SplatBtnColor = Vec3(1.f, 0.6f, 1.f);
}

void LandScapeUI::ChangeTexture(ID3D11ShaderResourceView*& _PrevTex, Ptr<CTexture>& _Tex, float& _Width, float& _Height)
{
    if (ImGui::BeginDragDropTarget())
    {
        const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
        if (pPayLoad)
        {
            TreeNode* pNode = (TreeNode*)pPayLoad->Data;
            CRes* pRes = (CRes*)pNode->GetData();
            if (RES_TYPE::TEXTURE == pRes->GetType())
            {
                _Tex = (CTexture*)pRes;
            }
        }
        ImGui::EndDragDropTarget();
    }

    if (nullptr != _Tex)
    {
        _PrevTex = _Tex->GetSRV().Get();
        _Width = _Tex->Width();
        _Height = _Tex->Height();
    }
}