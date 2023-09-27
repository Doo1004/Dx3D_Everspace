#include "pch.h"
#include "DecalUI.h"
#include "TreeUI.h"
#include <Engine\CDecal.h>
#include <Engine\CMaterial.h>
#include <Engine\CGraphicsShader.h>

DecalUI::DecalUI()
    : ComponentUI("##Decal", COMPONENT_TYPE::DECAL),
    m_TextureWidth(100.f),
    m_TextureHeight(100.f)
{
    SetName("Decal");
}

DecalUI::~DecalUI()
{
}

int DecalUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                                         // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                                         // Lower-right
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);                           // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);                         // 50% opaque white
    ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);                             // Black background
    m_AsLight = GetTarget()->Decal()->GetAsLight();
    m_DebugEnable = GetTarget()->Decal()->GetDebugShape();
    if (nullptr == m_DecalTexture)
        if (GetTarget()->Decal()->GetOutputTexture().Get())
            m_DecalTexture = GetTarget()->Decal()->GetOutputTexture();
    m_DecalShader = GetTarget()->Decal()->GetDecalMtrl()->GetShader();
    m_DecalColor = GetTarget()->Decal()->GetDecalColor();
    m_DebugColorEnable = GetTarget()->Decal()->GetDebugColor();


    //==========================AsLight, ShowDebug, ColorDebug======================================
    SetLabel("AsLight", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::Checkbox("##AsLight", &m_AsLight);
    GetTarget()->Decal()->SetAsLight(m_AsLight);

    ImGui::SameLine();

    SetLabel("ShowDebugShape", 120.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::Checkbox("##ShowDebugShape", &m_DebugEnable);

    GetTarget()->Decal()->SetDebugShape(m_DebugEnable);

    ImGui::SameLine();

    SetLabel("ShowDebugColor", 120.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::Checkbox("##ShowDebugColor", &m_DebugColorEnable);
    GetTarget()->Decal()->SetDebugColor(m_DebugColorEnable);

    //===========================================SetTexture=========================================
    SetLabel("Texture", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::Image(m_PreviewTexture, ImVec2(m_TextureWidth, m_TextureHeight), uv_min, uv_max, tint_col, border_col);
    ChangeTexture();
    if (m_TextureWidth >= 100.f)
    {
        m_TextureHeight = m_TextureHeight / (m_TextureWidth / 100.f);
        m_TextureWidth = 100.f;
    }
    ImGui::SameLine();
    if (ImGui::Button("Set"))
        GetTarget()->Decal()->SetOutputTexture(m_DecalTexture);


    //===========================================BSType=============================================
    SetLabel("SetBsType", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    if (ImGui::Button("DEFAULT", ImVec2(85.f, 18.f)))
        m_DecalShader->SetBSType(BS_TYPE::DEFAULT);
    ImGui::SameLine();
    if (ImGui::Button("ALPHA_BLEND", ImVec2(85.f, 18.f)))
        m_DecalShader->SetBSType(BS_TYPE::ALPHA_BLEND);
    ImGui::SameLine();
    if (ImGui::Button("ONE_ONE", ImVec2(85.f, 18.f)))
        m_DecalShader->SetBSType(BS_TYPE::ONE_ONE);
    ImGui::SameLine();
    if (ImGui::Button("MASK", ImVec2(85.f, 18.f)))
        m_DecalShader->SetBSType(BS_TYPE::MASK);

    //===========================================Color=============================================
    SetLabel("Color", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::ColorEdit4("##DecalColor", m_DecalColor);
    GetTarget()->Decal()->SetDecalColor(m_DecalColor);

    return TRUE;
}

void DecalUI::ChangeTexture()
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
                m_DecalTexture = (CTexture*)pRes;
            }
        }
        ImGui::EndDragDropTarget();
    }

    if (nullptr != m_DecalTexture)
    {
        m_PreviewTexture = m_DecalTexture->GetSRV().Get();
        m_TextureWidth = m_DecalTexture->Width();
        m_TextureHeight = m_DecalTexture->Height();
    }
}
