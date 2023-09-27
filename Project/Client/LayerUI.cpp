#include "pch.h"
#include "LayerUI.h"
#include "TransformUI.h"
#include <Engine\CLevel.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLayer.h>
#include <Engine\CCollisionMgr.h>
#include <Engine\CResMgr.h>
#include <Engine\CKeyMgr.h>

LayerUI::LayerUI()
    : UI("##Layer"),
    m_SelectedNum(-1),
    m_SelectedLayer1(-1),
    m_SelectedLayer2(-1),
    m_Layer1EditMode(false),
    m_Layer2EditMode(false)
{
}

LayerUI::~LayerUI()
{
}

void LayerUI::finaltick()
{
    UI::finaltick();

    if (KEY_TAP(KEY::ESC))
    {
        SetActive(false);

        // 모든 UI 포커스 해제
        ImGui::SetWindowFocus(nullptr);
    }
}

int LayerUI::render_update()
{
    CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
    bool Layer1EditMode = false;
    bool Layer2EditMode = false;

    for (int i = 0; i < 32; ++i)
    {
        m_LayerName[i] = string(pCurLevel->GetLayer(i)->GetName().begin(), pCurLevel->GetLayer(i)->GetName().end());
    }

    SetLabel("Show Layer List", 120.f, 18.f, 0.4f, 1.f, 0.4f);
    ShowLayerList();

    if (ImGui::Button("SetLayer1"))
        m_SelectedLayer1 = m_SelectedNum;
    ImGui::SameLine();
    if (ImGui::Button("SetLayer2"))
        m_SelectedLayer2 = m_SelectedNum;

    if (m_SelectedLayer1 >= 0)
    {
        char LayerName1[64];
        strcpy_s(LayerName1, m_LayerName[m_SelectedLayer1].c_str());
        SetLabel("Layer1", 50.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::Text(LayerName1);
        ImGui::SameLine();
        if (ImGui::Button("EditLayer1"))
        {
            if (m_Layer1EditMode)
                m_Layer1EditMode = false;
            else
                m_Layer1EditMode = true;
        }

        if (m_Layer1EditMode)
        {
            char Ly1[64];
            strcpy_s(Ly1, m_LayerName1.c_str());
            ImGui::InputText("##InputName1", Ly1, 64);
            m_LayerName1 = Ly1;
            if (ImGui::Button("Set"))
                pCurLevel->GetLayer(m_SelectedLayer1)->SetName(ChangeToWString(m_LayerName1));
        }
    }

    if (m_SelectedLayer2 >= 0)
    {
        char LayerName2[64];
        strcpy_s(LayerName2, m_LayerName[m_SelectedLayer2].c_str());
        SetLabel("Layer2", 50.f, 18.f, 0.6f, 1.f, 0.6f);
        ImGui::SameLine();
        ImGui::Text(LayerName2);
        ImGui::SameLine();
        if (ImGui::Button("EditLayer2"))
        {
            if (m_Layer2EditMode)
                m_Layer2EditMode = false;
            else
                m_Layer2EditMode = true;
        }

        if (m_Layer2EditMode)
        {
            char Ly2[64];
            strcpy_s(Ly2, m_LayerName2.c_str());
            ImGui::InputText("##InputName2", Ly2, 64);
            m_LayerName2 = Ly2;
            if (ImGui::Button("Set"))
                pCurLevel->GetLayer(m_SelectedLayer2)->SetName(ChangeToWString(m_LayerName2));
        }
    }

    if (m_SelectedLayer1 >= 0 && m_SelectedLayer2 >= 0)
    {
        bool CheckCollider = CCollisionMgr::GetInst()->IsLayerColliding(m_SelectedLayer1, m_SelectedLayer2);
        ImGui::Text("LayerCollision : ");
        ImGui::SameLine();
        ImGui::Checkbox("##LayerCheck", &CheckCollider);

        ImGui::Text("SetLayerCollision : ");
        ImGui::SameLine();
        if (ImGui::Button("Set True"))
            CCollisionMgr::GetInst()->ModifyLayerCollision(m_SelectedLayer1, m_SelectedLayer2, true);
        ImGui::SameLine();
        if (ImGui::Button("Set False"))
            CCollisionMgr::GetInst()->ModifyLayerCollision(m_SelectedLayer1, m_SelectedLayer2, false);
    }

    return TRUE;
}

void LayerUI::Reset(const string& _strName, ImVec2 _vSize)
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

void LayerUI::ShowLayerList()
{

    auto getter = [](void* data, int idx, const char** out_text)
    {
        std::string* layerNameArray = static_cast<std::string*>(data);
        *out_text = layerNameArray[idx].c_str();
        return true;
    };

    ImGui::ListBox("##LayerList", &m_SelectedNum, getter, static_cast<void*>(m_LayerName), 32);
}