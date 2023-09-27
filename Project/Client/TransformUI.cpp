#include "pch.h"
#include "TransformUI.h"
#include "OutlinerUI.h"
#include "LayerUI.h"
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>


TransformUI::TransformUI()
	: ComponentUI("##Transform", COMPONENT_TYPE::TRANSFORM)
{
	SetName("Transform");
}

TransformUI::~TransformUI()
{
}

int TransformUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;

	int layer = GetTarget()->GetLayerIndex();
	ImGui::Text("Object Layer : ");
	ImGui::SameLine();
	ImGui::InputInt("##Layer", &layer);
	GetTarget()->SetLayerIndex(layer);

	ImGui::Text("Set ObjectName : ");
	ImGui::SameLine();
	char ObjName[64];
	strcpy_s(ObjName, m_ObjName.c_str());
	ImGui::InputText("##SetName", ObjName, 64);
	m_ObjName = ObjName;
	ImGui::SameLine();
	if (ImGui::Button("Set"))
	{
		GetTarget()->SetName(ChangeToWString(m_ObjName));
		OutlinerUI* Outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
		Outliner->ResetOutliner();
	}

	if (GetTarget())
	{
		m_vPos = GetTarget()->Transform()->GetRelativePos();
		m_vScale = GetTarget()->Transform()->GetRelativeScale();
		m_bAbsolute = GetTarget()->Transform()->IsUseAbsolute();
		m_bQuaternion = GetTarget()->Transform()->IsUseQuaternion();
		if (!m_bQuaternion)
		{
			m_vRotation = GetTarget()->Transform()->GetRelativeRot();
			m_vRotation = (m_vRotation / XM_PI) * 180.f;
		}
	}

	ImGui::Text("Absolute : ");
	ImGui::SameLine();
	ImGui::Checkbox("##Absolute", &m_bAbsolute);
	GetTarget()->Transform()->SetAbsolute(m_bAbsolute);

	ImGui::Text("Position");
	ImGui::SameLine();
	ImGui::DragFloat3("##Relative Position", m_vPos);

	ImGui::Text("Scale   ");
	ImGui::SameLine();
	ImGui::DragFloat3("##Relative Scale", m_vScale);

	ImGui::Text("Rotation");
	ImGui::SameLine();
	ImGui::DragFloat3("##Relative Rotation", m_vRotation);

	ImGui::Text("Quarternion");
	ImGui::SameLine();
	ImGui::Checkbox("##m_bQuaternion", &m_bQuaternion);

	GetTarget()->Transform()->SetRelativePos(m_vPos);
	GetTarget()->Transform()->SetRelativeScale(m_vScale);

	if (!m_bQuaternion)
	{
		m_vRotation = (m_vRotation / 180.f) * XM_PI;
		GetTarget()->Transform()->SetRelativeRot(m_vRotation);
	}
	else
	{
		m_vRotation = (m_vRotation / 180.f) * XM_PI;
		GetTarget()->Transform()->SetQuaternionRot(m_vRotation);
	}

	if (ImGui::Button("LayerEdit"))
	{
		LayerUI* pLayerUI = (LayerUI*)ImGuiMgr::GetInst()->FindUI("##Layer");
		pLayerUI->Reset("LayerEdit", ImVec2(500.f, 700.f));
	}

	return TRUE;
}