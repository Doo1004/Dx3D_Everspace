#include "pch.h"
#include <Engine\CFont.h>
#include "FontUI.h"


FontUI::FontUI()
    : ComponentUI("##Font", COMPONENT_TYPE::FONT)
{
    SetName("Font");
}

FontUI::~FontUI()
{
}

int FontUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    //=======================================================String
    ImGui::Text("Text : ");
    ImGui::SameLine();
    char Text[64];
    strcpy_s(Text, m_sText.c_str());
    ImGui::InputText("##SetName", Text, 64);
    m_sText = Text;
    ImGui::SameLine();
    if (ImGui::Button("Set"))
        GetTarget()->Font()->SetString(ChangeToWString(m_sText));


    //=======================================================Pos
    Vec2 vPos = GetTarget()->Font()->GetPos();
    m_vPos = Vec3(vPos.x, vPos.y, 0.f);

    ImGui::Text("Text Pos : ");
    ImGui::SameLine();
    ImGui::InputFloat2("##Pos", m_vPos);

    GetTarget()->Font()->SetPos(Vec2(m_vPos.x, m_vPos.y));
    //=======================================================Scale
    m_fScale = GetTarget()->Font()->GetScale();

    ImGui::Text("Text Size : ");
    ImGui::SameLine();
    ImGui::InputFloat("##Size", &m_fScale);

    GetTarget()->Font()->SetScale(m_fScale);
    //=======================================================Color
    m_vColor = GetTarget()->Font()->GetColor();
    Vec4 vColor = m_vColor / 255;

    ImGui::Text("Text Color : ");
    ImGui::SameLine();
    ImGui::ColorEdit4("##Color", vColor);

    m_vColor = Vec4(vColor.x * 255, vColor.y * 255, vColor.z * 255, vColor.w * 255);

    GetTarget()->Font()->SetColor(m_vColor);

    return TRUE;
}