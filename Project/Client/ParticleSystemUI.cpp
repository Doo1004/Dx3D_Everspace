#include "pch.h"
#include "ParticleSystemUI.h"

#include <Engine\CParticleSystem.h>
#include <Engine\CStructuredBuffer.h>


ParticleSystemUI::ParticleSystemUI()
    : ComponentUI("##ParticleSystem", COMPONENT_TYPE::PARTICLESYSTEM)
{
    SetName("ParticleSystem");
}

ParticleSystemUI::~ParticleSystemUI()
{

}


int ParticleSystemUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    GetTargetData();
    SetChangeButtonColor();

    ImGui::Checkbox("Particle Spawn", &m_SpawnEnable);

    if (m_SpawnEnable)
    {
        SetLabel("DebugShape", 90.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::Checkbox("##ShowDebugShape", &m_ShowDebugShape);

        SetLabel("MaxParticle", 90.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::InputInt("##MaxParticle", &m_MaxParticle);

        SetLabel("SpawnRate", 90.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::InputInt("##SpawnRate", &m_SpawnRate);

        SetLabel("SpawnColor", 90.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::ColorEdit4("##SpawnColor", m_SpawnColor);

        SetLabel("ScaleMin", 90.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::InputFloat2("##ScaleMin", m_ScaleMin);

        SetLabel("ScaleMax", 90.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::InputFloat2("##ScaleMax", m_ScaleMax);

        SetLabel("ShapeType", 90.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        UIColorButton(m_BoxBtnColor);
        if (ImGui::Button("Box", ImVec2(100.f, 18.f)))
        {
            m_ShapeType = 0;
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();

        ImGui::SameLine();

        UIColorButton(m_CubeBtnColor);
        if (ImGui::Button("Cube", ImVec2(100.f, 18.f)))
        {
            m_ShapeType = 2;
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();

        SetLabel("ShapeScale", 90.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::InputFloat3("##ShapeScale", m_ShapeScale);

        SetLabel("LifeTime", 90.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::InputFloat2("##LifeTime", m_LifeTime);
        ImGui::Text("                  Min           Max");

        /////////////////////////////////////////////////////////////////////////////////////////ColorChange
        ImGui::Checkbox("ColorChange", &m_ColorChangeEnable);

        if (m_ColorChangeEnable)
        {
            SetLabel("StartColor", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            ImGui::ColorEdit4("##StartColor", m_StartColor);

            SetLabel("EndColor", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            ImGui::ColorEdit4("##EndColor", m_EndColor);
        }

        /////////////////////////////////////////////////////////////////////////////////////////ScaleChange
        ImGui::Checkbox("Scale Change", &m_ScaleChangeEnable);
        if (m_ScaleChangeEnable)
        {
            SetLabel("Min / Max", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            ImGui::InputFloat2("##ScaleChange", m_ScaleChangeData);
        }

        /////////////////////////////////////////////////////////////////////////////////////////AddVelocity
        ImGui::Checkbox("Add Velocity", &m_AddVelocityEnable);
        if (m_AddVelocityEnable)
        {
            SetLabel("Type", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            UIColorButton(m_FromCenterBtnColor);
            if (ImGui::Button("FromCenter", ImVec2(100.f, 18.f)))
            {
                m_AddVelocityType = 0;
            }
            ImGui::PopStyleColor(3);
            ImGui::PopID();

            ImGui::SameLine();
            UIColorButton(m_ToCenterBtnColor);
            if (ImGui::Button("ToCenter", ImVec2(100.f, 18.f)))
            {
                m_AddVelocityType = 1;
            }
            ImGui::PopStyleColor(3);
            ImGui::PopID();


            ImGui::Text("             ");

            ImGui::SameLine();
            UIColorButton(m_DirectionBtnColor);
            if (ImGui::Button("Direction", ImVec2(100.f, 18.f)))
            {
                m_AddVelocityType = 2;
            }
            ImGui::PopStyleColor(3);
            ImGui::PopID();


            SetLabel("Speed", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            ImGui::InputFloat("##Speed", &m_Speed);

            SetLabel("VelocityDir", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            ImGui::InputFloat3("##VelocityDir", m_VelocityDir);

            SetLabel("OffsetAngle", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            ImGui::InputFloat("##OffsetAngle", &m_OffsetAngle);
        }

        /////////////////////////////////////////////////////////////////////////////////////////Drag
        ImGui::Checkbox("Drag", &m_DragEnable);
        if (m_DragEnable)
        {
            SetLabel("Start Drag", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            ImGui::InputFloat("##Start Drag", &m_StartDrag);

            SetLabel("End Drag", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            ImGui::InputFloat("##End Drag", &m_EndDrag);
        }

        /////////////////////////////////////////////////////////////////////////////////////////NoiseForce
        ImGui::Checkbox("Noise Force", &m_NoiseForceEnable);
        if (m_NoiseForceEnable)
        {
            SetLabel("NoiseTerm", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            ImGui::InputFloat("##NoiseTerm", &m_NoiseTerm);

            SetLabel("NoiseForce", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            ImGui::InputFloat("##NoiseForce", &m_NoiseForce);
        }

        /////////////////////////////////////////////////////////////////////////////////////////Render
        ImGui::Checkbox("Render", &m_RenderEnable);
        if (m_RenderEnable)
        {
            SetLabel("Velocity", 90.f, 18.f, 0.6f, 1.f, 0.6f);
            ImGui::SameLine();
            UIColorButton(m_AlignmentBtnColor);
            if (ImGui::Button("Alignment", ImVec2(100.f, 18.f)))
            {
                if (m_VelocityAlignment)
                    m_VelocityAlignment = false;
                else
                    m_VelocityAlignment = true;
            }
            ImGui::PopStyleColor(3);
            ImGui::PopID();

            ImGui::SameLine();

            UIColorButton(m_ScaleBtnColor);
            if (ImGui::Button("ScaleChange", ImVec2(100.f, 18.f)))
            {
                if (m_VelocityScale)
                    m_VelocityScale = false;
                else
                    m_VelocityScale = true;
            }
            ImGui::PopStyleColor(3);
            ImGui::PopID();
        }
    }

    SetTargetData();

    return TRUE;
}


void ParticleSystemUI::GetTargetData()
{
    m_ShowDebugShape = GetTarget()->ParticleSystem()->IsShowDebugShape();
    m_SpawnEnable = GetTarget()->ParticleSystem()->GetSpawnEnable();
    m_ColorChangeEnable = GetTarget()->ParticleSystem()->GetColorChangeEnable();
    m_ScaleChangeEnable = GetTarget()->ParticleSystem()->GetScaleChangeEnable();
    m_AddVelocityEnable = GetTarget()->ParticleSystem()->GetAddVelocityEnable();
    m_DragEnable = GetTarget()->ParticleSystem()->GetDragEnable();
    m_NoiseForceEnable = GetTarget()->ParticleSystem()->GetNoiseForceEnable();
    m_RenderEnable = GetTarget()->ParticleSystem()->GetRenderEnable();

    m_MaxParticle = GetTarget()->ParticleSystem()->GetMaxParticle();
    m_SpawnRate = GetTarget()->ParticleSystem()->GetSpawnRate();
    m_SpawnColor = GetTarget()->ParticleSystem()->GetSpawnColor();
    m_ScaleMin = GetTarget()->ParticleSystem()->GetSpawnScaleMin();
    m_ScaleMax = GetTarget()->ParticleSystem()->GetSpawnScaleMax();
    m_ShapeType = GetTarget()->ParticleSystem()->GetShapeType();
    m_ShapeScale = GetTarget()->ParticleSystem()->GetShapeScale();
    m_LifeTime = Vec3(GetTarget()->ParticleSystem()->GetMinLifeTime(), GetTarget()->ParticleSystem()->GetMaxLifeTime(), 0.f);
    m_StartColor = GetTarget()->ParticleSystem()->GetStartColor();
    m_EndColor = GetTarget()->ParticleSystem()->GetEndColor();
    m_ScaleChangeData = Vec3(GetTarget()->ParticleSystem()->GetStartScale(), GetTarget()->ParticleSystem()->GetEndScale(), 0.f);
    m_AddVelocityType = GetTarget()->ParticleSystem()->GetAddVelocityType();
    m_Speed = GetTarget()->ParticleSystem()->GetSpeed();
    m_VelocityDir = GetTarget()->ParticleSystem()->GetVelocityDir();
    m_OffsetAngle = GetTarget()->ParticleSystem()->GetOffsetAngle();
    m_StartDrag = GetTarget()->ParticleSystem()->GetStartDrag();
    m_EndDrag = GetTarget()->ParticleSystem()->GetEndDrag();
    m_NoiseTerm = GetTarget()->ParticleSystem()->GetNoiseTerm();
    m_NoiseForce = GetTarget()->ParticleSystem()->GetNoiseForce();
    m_VelocityAlignment = GetTarget()->ParticleSystem()->GetVelocityAlignment();
    m_VelocityScale = GetTarget()->ParticleSystem()->GetVelocityScale();
}

void ParticleSystemUI::SetTargetData()
{
    GetTarget()->ParticleSystem()->SetShowDebugShape(m_ShowDebugShape);
    GetTarget()->ParticleSystem()->SetSpawnEnable(m_SpawnEnable);
    GetTarget()->ParticleSystem()->SetColorChangeEnable(m_ColorChangeEnable);
    GetTarget()->ParticleSystem()->SetScaleChangeEnable(m_ScaleChangeEnable);
    GetTarget()->ParticleSystem()->SetAddVelocityEnable(m_AddVelocityEnable);
    GetTarget()->ParticleSystem()->SetDragEnable(m_DragEnable);
    GetTarget()->ParticleSystem()->SetNoiseForceEnable(m_NoiseForceEnable);
    GetTarget()->ParticleSystem()->SetRenderEnable(m_RenderEnable);

    GetTarget()->ParticleSystem()->SetMaxParticle(m_MaxParticle);
    GetTarget()->ParticleSystem()->SetSpawnRate(m_SpawnRate);
    GetTarget()->ParticleSystem()->SetSpawnColor(m_SpawnColor);
    GetTarget()->ParticleSystem()->SetSpawnScaleMin(m_ScaleMin);
    GetTarget()->ParticleSystem()->SetSpawnScaleMax(m_ScaleMax);
    GetTarget()->ParticleSystem()->SetShapeType(m_ShapeType);
    GetTarget()->ParticleSystem()->SetShapeScale(m_ShapeScale);
    GetTarget()->ParticleSystem()->SetMinLifeTime(m_LifeTime.x);
    GetTarget()->ParticleSystem()->SetMaxLifeTime(m_LifeTime.y);
    GetTarget()->ParticleSystem()->SetStartScale(m_ScaleChangeData.x);
    GetTarget()->ParticleSystem()->SetEndScale(m_ScaleChangeData.y);
    GetTarget()->ParticleSystem()->SetStartColor(m_StartColor);
    GetTarget()->ParticleSystem()->SetEndColor(m_EndColor);
    GetTarget()->ParticleSystem()->SetAddVelocityType(m_AddVelocityType);
    GetTarget()->ParticleSystem()->SetSpeed(m_Speed);
    GetTarget()->ParticleSystem()->SetVelocityDir(m_VelocityDir);
    GetTarget()->ParticleSystem()->SetOffsetAngle(m_OffsetAngle);
    GetTarget()->ParticleSystem()->SetStartDrag(m_StartDrag);
    GetTarget()->ParticleSystem()->SetEndDrag(m_EndDrag);
    GetTarget()->ParticleSystem()->SetNoiseTerm(m_NoiseTerm);
    GetTarget()->ParticleSystem()->SetNoiseForce(m_NoiseForce);
    GetTarget()->ParticleSystem()->SetVelocityAlignment(m_VelocityAlignment);
    GetTarget()->ParticleSystem()->SetVelocityScale(m_VelocityScale);
}

void ParticleSystemUI::SetChangeButtonColor()
{
    if (m_VelocityAlignment) // 방향 변환
        m_AlignmentBtnColor = Vec3(0.4f, 1.f, 0.4f);
    else
        m_AlignmentBtnColor = Vec3(1.f, 0.6f, 1.f);

    if (m_VelocityScale) // 크기 변환
        m_ScaleBtnColor = Vec3(0.4f, 1.f, 0.4f);
    else
        m_ScaleBtnColor = Vec3(1.f, 0.6f, 1.f);

    if (m_ShapeType == 0) // ShapeType이 Box일 때
    {
        m_BoxBtnColor = Vec3(0.4f, 1.f, 0.4f);
        m_CubeBtnColor = Vec3(1.f, 0.6f, 1.f);
    }
    else if (m_ShapeType == 1) // ShapeType이 Sphere일 때
    {
        m_BoxBtnColor = Vec3(1.f, 0.6f, 1.f);
        m_CubeBtnColor = Vec3(0.4f, 1.f, 0.4f);
    }

    if (m_AddVelocityType == 0) // VelocityType이 0일 때
    {
        m_FromCenterBtnColor = Vec3(0.4f, 1.f, 0.4f);
        m_ToCenterBtnColor = Vec3(1.f, 0.6f, 1.f);
        m_DirectionBtnColor = Vec3(1.f, 0.6f, 1.f);
    }
    else if (m_AddVelocityType == 1) // VelocityType이 1일 때
    {
        m_FromCenterBtnColor = Vec3(1.f, 0.6f, 1.f);
        m_ToCenterBtnColor = Vec3(0.4f, 1.f, 0.4f);
        m_DirectionBtnColor = Vec3(1.f, 0.6f, 1.f);
    }
    else if (m_AddVelocityType == 2) // VelocityType이 1일 때
    {
        m_FromCenterBtnColor = Vec3(1.f, 0.6f, 1.f);
        m_ToCenterBtnColor = Vec3(1.f, 0.6f, 1.f);
        m_DirectionBtnColor = Vec3(0.4f, 1.f, 0.4f);
    }
}