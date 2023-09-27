#include "pch.h"
#include "ParticleDetailSetUI.h"

ParticleDetailSetUI::ParticleDetailSetUI()
    : UI("##DetailUI")
{
}

ParticleDetailSetUI::~ParticleDetailSetUI()
{
}

int ParticleDetailSetUI::render_update()
{

    ImGui::Checkbox("ColorChange", &m_ColorChangeEnable);

    if (m_ColorChangeEnable)
    {
        SetLabel("StartColor", 80.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::ColorEdit3("##StartColor", m_StartColor);

        SetLabel("EndColor", 80.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::ColorEdit3("##EndColor", m_EndColor);
    }

    ImGui::Checkbox("Scale Change", &m_ScaleChangeEnable);
    if (m_ScaleChangeEnable)
    {
        SetLabel("Min / Max", 80.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::InputFloat2("##ScaleChange", m_ScaleChangeData);
    }

    ImGui::Checkbox("Add Velocity", &m_AddVelocityEnable);
    if (m_AddVelocityEnable)
    {
        SetLabel("Type", 80.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        if (ImGui::Button("FromCenter", ImVec2(100.f, 18.f)))
        {
            m_AddVelocityType = 0;
        }
        ImGui::SameLine();
        if (ImGui::Button("ToCenter", ImVec2(100.f, 18.f)))
        {
            m_AddVelocityType = 1;
        }

        SetLabel("Speed", 80.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::InputFloat("##Speed", &m_Speed);

    }

    ImGui::Checkbox("Drag", &m_DragEnable);
    if (m_DragEnable)
    {
        SetLabel("Start Drag", 80.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::InputFloat("##Start Drag", &m_StartDrag);

        SetLabel("End Drag", 80.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::InputFloat("##End Drag", &m_EndDrag);
    }

    ImGui::Checkbox("Noise Force", &m_NoiseForceEnable);
    if (m_NoiseForceEnable)
    {
        SetLabel("NoiseTerm", 80.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::DragFloat("##NoiseTerm", &m_NoiseTerm);

        SetLabel("NoiseForce", 80.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::DragFloat("##NoiseForce", &m_NoiseForce);
    }

    ImGui::Checkbox("Render", &m_RenderEnable);
    if (m_RenderEnable)
    {

    }

    return TRUE;
}

void ParticleDetailSetUI::Reset(const string& _strName, ImVec2 _vSize)
{
    SetName(_strName);

    SetSize(_vSize.x, _vSize.y);

    SetActive(true);

    // 위치 조정
    HWND hWnd = ImGuiMgr::GetInst()->GetMainHwnd();

    RECT rt = {};
    //GetClientRect(hWnd, &rt);
    GetWindowRect(hWnd, &rt);

    float CenterX = (float)((rt.left + rt.right) / 2);
    float CenterY = (float)((rt.bottom + rt.top) / 2);

    SetPopupPos(ImVec2(CenterX - _vSize.x / 2.f, CenterY - _vSize.y / 2.f));
}