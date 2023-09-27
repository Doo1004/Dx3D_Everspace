#include "pch.h"
#include "Collider3DUI.h"
#include <Engine\CCollider3D.h>


Collider3DUI::Collider3DUI()
    : ComponentUI("##Coillider3D", COMPONENT_TYPE::COLLIDER3D)
{
    SetName("Coillider3D");
}

Collider3DUI::~Collider3DUI()
{
}

int Collider3DUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    //=====================Collider Type=========================//
    m_Type = GetTarget()->Collider3D()->GetCollider3DType();

    SetLabel("ColliderType", 120.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    if (m_Type == COLLIDER3D_TYPE::CUBE)
        ImGui::Text("Cube");
    else
        ImGui::Text("Sphere");

    ImGui::SameLine(170);

    if (ImGui::Button("Swap"))
    {
        if (m_Type == COLLIDER3D_TYPE::CUBE)
        {
            m_Type = COLLIDER3D_TYPE::SPHERE;
        }
        else
        {
            m_Type = COLLIDER3D_TYPE::CUBE;
        }
    }
    GetTarget()->Collider3D()->SetCollider3DType(m_Type);
    //======================SetTransform=========================//
    m_ColliderPos = GetTarget()->Collider3D()->GetOffsetPos();
    m_ColliderScale = GetTarget()->Collider3D()->GetOffsetScale();

    SetLabel("OffsetPos", 120.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::DragFloat3("##ColliderPos", m_ColliderPos);

    SetLabel("OffsetScale", 120.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::DragFloat3("##ColliderScale", m_ColliderScale);

    GetTarget()->Collider3D()->SetOffsetPos(m_ColliderPos);
    GetTarget()->Collider3D()->SetOffsetScale(m_ColliderScale);
    //======================SetAbsolute=========================//
    m_bAbsolute = GetTarget()->Collider3D()->IsUseAbsolute();

    SetLabel("SetAbsolute", 120.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::Checkbox("##SetAbsolute", &m_bAbsolute);
    GetTarget()->Collider3D()->SetAbsolute(m_bAbsolute);
    //======================ShowDebugShape======================//
    m_bShowDebugShape = GetTarget()->Collider3D()->IsShowColliderShape();

    SetLabel("ShowDebugShape", 120.f, 18.f, 0.4f, 1.f, 0.4f);
    ImGui::SameLine();
    ImGui::Checkbox("##ShowDebugShape", &m_bShowDebugShape);
    GetTarget()->Collider3D()->SetShowColliderShape(m_bShowDebugShape);
    
    return TRUE;
}