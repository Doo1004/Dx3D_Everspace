#include "pch.h"
#include "Light3DUI.h"
#include <Engine\CLight3D.h>
#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>
#include <Engine\CResMgr.h>


Light3DUI::Light3DUI()
    : ComponentUI("##Light3D", COMPONENT_TYPE::LIGHT3D)
{
    SetName("Light3D");
}

Light3DUI::~Light3DUI()
{
}


int Light3DUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    m_Diffuse = GetTarget()->Light3D()->GetLightInfo().Color.vDiffuse;
    m_Specular = GetTarget()->Light3D()->GetLightInfo().Color.vSpecular;
    m_Ambient = GetTarget()->Light3D()->GetLightInfo().Color.vAmbient;
    m_Direction = GetTarget()->Light3D()->GetLightInfo().vWorldDir;

    m_LightType = (LIGHT_TYPE)GetTarget()->Light3D()->GetLightInfo().LightType;
    m_LightDiffuse = Vec3(m_Diffuse.x, m_Diffuse.y, m_Diffuse.z);
    m_LightAngle = GetTarget()->Light3D()->GetLightInfo().Angle;
    m_LightSpecular = Vec3(m_Specular.x, m_Specular.y, m_Specular.z);
    m_LightAmbient = Vec3(m_Ambient.x, m_Ambient.y, m_Ambient.z);
    m_LightRadius = GetTarget()->Light3D()->GetLightInfo().Radius;
    m_LightDirection = Vec3(m_Direction.x, m_Direction.y, m_Direction.z);


    ImGui::Text("LightType : ");
    ImGui::SameLine();
    if ((UINT)m_LightType == 0)
        ImGui::Text("Directional Light");
    else if ((UINT)m_LightType == 1)
        ImGui::Text("Point Light");
    else if ((UINT)m_LightType == 2)
        ImGui::Text("Spot Light");

    SetLabel("Type", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    if (ImGui::Button("Direction"))
        m_LightType = LIGHT_TYPE::DIRECTIONAL;
    ImGui::SameLine();
    if (ImGui::Button("Point"))
        m_LightType = LIGHT_TYPE::POINT;
    ImGui::SameLine();
    if (ImGui::Button("Spot"))
        m_LightType = LIGHT_TYPE::SPOT;

    SetLabel("Diffuse", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::ColorEdit3("##LightDiffuse", m_LightDiffuse);

    SetLabel("Angle", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::DragFloat("##LightAngle", &m_LightAngle);

    SetLabel("Specular", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::ColorEdit3("##LightSpecular", m_LightSpecular);

    SetLabel("Ambient", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::ColorEdit3("##LightAmbient", m_LightAmbient);

    SetLabel("Radius", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::DragFloat("##LightRadius", &m_LightRadius);

    SetLabel("Direction", 70.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::DragFloat3("##LightDirection", m_LightDirection);


    SetLabel("ShowDebugMesh", 100.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::Checkbox("##ShowDebugMesh", &m_ShowDebugMesh);
    //if(m_ShowDebugMesh)
    //    GetTarget()->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeMtrl"));
    //else if (!m_ShowDebugMesh)
    //{
    //    if ((UINT)m_LightType == 0)
    //        GetTarget()->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DirLightMtrl"));
    //    else if ((UINT)m_LightType == 1)
    //        GetTarget()->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PointLightMtrl"));
    //    else if ((UINT)m_LightType == 2)
    //        GetTarget()->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SpotLightMtrl"));
    //}



    GetTarget()->Light3D()->SetLightType(m_LightType);
    GetTarget()->Light3D()->SetLightDiffuse(m_LightDiffuse);
    GetTarget()->Light3D()->SetAngle(m_LightAngle);
    GetTarget()->Light3D()->SetLightSpecular(m_LightSpecular);
    GetTarget()->Light3D()->SetLightAmbient(m_LightAmbient);
    GetTarget()->Light3D()->SetRadius(m_LightRadius);
    GetTarget()->Light3D()->SetLightDirection(m_LightDirection);

    return TRUE;
}