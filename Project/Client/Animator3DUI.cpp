#include "pch.h"
#include "Animator3DUI.h"
#include <Engine\CAnimator3D.h>

Animator3DUI::Animator3DUI()
    : ComponentUI("##Animator3D", COMPONENT_TYPE::ANIMATOR3D)
{
    SetName("Animator3D");
}

Animator3DUI::~Animator3DUI()
{
}


int Animator3DUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    float AnimClipTime = GetTarget()->Animator3D()->GetClipTime(0);
    ImGui::Text("AnimClipTime : ");
    ImGui::SameLine();
    ImGui::InputFloat("##ClipTime", &AnimClipTime);

    //GetTarget()->Animator3D()->SetAnimClip(3);
    int BoneCount = GetTarget()->Animator3D()->GetBoneCount();
    ImGui::Text("BoneCount : ");
    ImGui::SameLine();
    ImGui::InputInt("##BoneCount", & BoneCount);

    return TRUE;
}