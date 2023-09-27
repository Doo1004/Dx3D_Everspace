#include "pch.h"
#include "SkyBoxUI.h"
#include "TreeUI.h"
#include <Engine\CSkyBox.h>


SkyBoxUI::SkyBoxUI()
    : ComponentUI("##SkyBox", COMPONENT_TYPE::SKYBOX),
    m_TextureWidth(100.f),
    m_TextureHeight(100.f)
{
    SetName("SkyBox");
}

SkyBoxUI::~SkyBoxUI()
{
}


int SkyBoxUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;
    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                                         // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                                         // Lower-right
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);                           // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);                         // 50% opaque white
    ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);                             // Black background

    //=========================================SetTexture===========================================
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
        GetTarget()->SkyBox()->SetSkyTexture(m_SkyTexture);

    //========================================SetSkyBoxType=========================================
    m_BoxType = (UINT)GetTarget()->SkyBox()->GetBoxType();

    ImGui::Text("BoxType : ");
    ImGui::SameLine();

    if (m_BoxType == 0)
        ImGui::Text("Sphere");
    else if (m_BoxType == 1)
        ImGui::Text("Box");

    ImGui::SameLine(200);

    if (ImGui::Button("Change"))
        if (m_BoxType == 0)
        {
            m_BoxType = 1;
            GetTarget()->SkyBox()->SetType((SKYBOX_TYPE)m_BoxType);
        }
        else if (m_BoxType == 1)
        {
            m_BoxType = 0;
            GetTarget()->SkyBox()->SetType((SKYBOX_TYPE)m_BoxType);
        }

    return TRUE;
}

void SkyBoxUI::ChangeTexture()
{
    if (ImGui::BeginDragDropTarget())
    {
        const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
        if (pPayLoad)
        {
            TreeNode* pNode = (TreeNode*)pPayLoad->Data;
            CRes* pRes = (CRes*)pNode->GetData();
            if (RES_TYPE::TEXTURE == pRes->GetType())
                m_SkyTexture = (CTexture*)pRes;
        }
        ImGui::EndDragDropTarget();
    }

    if (nullptr != m_SkyTexture)
    {
        m_PreviewTexture = m_SkyTexture->GetSRV().Get();
        m_TextureWidth = m_SkyTexture->Width();
        m_TextureHeight = m_SkyTexture->Height();
    }
}
