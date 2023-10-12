#include "pch.h"
#include "CameraUI.h"
#include <Engine\CCamera.h>


CameraUI::CameraUI()
    : ComponentUI("##Camera", COMPONENT_TYPE::CAMERA)
{
    SetName("Camera");
}

CameraUI::~CameraUI()
{
}

int CameraUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    m_UseCameraDebugShape = GetTarget()->Camera()->IsUseCameraDebug();
    SetLabel("ShowDebug", 80.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::Checkbox("##CameraDebug", &m_UseCameraDebugShape);
    GetTarget()->Camera()->ShowCameraDebug(m_UseCameraDebugShape);

    m_CameraDebugScale = GetTarget()->Camera()->GetCameraDebugScale();
    SetLabel("DebugScale", 80.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::DragFloat("##CameraScale", &m_CameraDebugScale, 0.001f, 1.f, 2.f);
    GetTarget()->Camera()->SetCameraDebugScale(m_CameraDebugScale);


    m_iProjType = (UINT)GetTarget()->Camera()->GetProjType();
    SetLabel("ProjType", 80.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    if (m_iProjType == 0)
        ImGui::Text("ORTHOGRAPHIC");
    else if (m_iProjType == 1)
        ImGui::Text("PERSPECTIVE");
    ImGui::SameLine();
    
    if (ImGui::Button("Set 2D"))
        GetTarget()->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
    ImGui::SameLine();
    if (ImGui::Button("Set 3D"))
        GetTarget()->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);

    SetLabel("CameraLayer", 80.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    std::string str = "Layer: " + std::to_string(GetTarget()->Camera()->GetCameraIndex());
    ImGui::Text(str.c_str());
    ImGui::InputInt("##Index", &m_iIndex);
    ImGui::SameLine();
    if(ImGui::Button("Set##1"))
        GetTarget()->Camera()->SetCameraIndex(m_iIndex);

    SetLabel("LayerMask", 80.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::InputInt("##Layer", &m_iLayer);
    ImGui::SameLine();
    m_bLayerCheck = GetTarget()->Camera()->IsLayerMask(m_iLayer);
    ImGui::Checkbox("##Check", &m_bLayerCheck);
    GetTarget()->Camera()->SetLayerMask(m_iLayer, m_bLayerCheck);

    SetLabel("UIEnable", 80.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    m_bCameraUI = GetTarget()->Camera()->IsCameraUIRender();
    ImGui::Checkbox("##CameraUI", &m_bCameraUI);
    GetTarget()->Camera()->SetCameraUIRender(m_bCameraUI);

    return TRUE;
}