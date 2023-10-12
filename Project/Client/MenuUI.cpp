#include "pch.h"
#include "MenuUI.h"

#include "CLevelSaveLoad.h"
#include <Engine\CEventMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>
#include <Engine\CScript.h>
#include <Engine\CLevelMgr.h>

#include <Script\CScriptMgr.h>



#include "ImGuiMgr.h"
#include "OutlinerUI.h"
#include "ContentUI.h"
#include "InspectorUI.h"
#include "CLevelSaveLoad.h"



MenuUI::MenuUI()
	: UI("##Menu")
{
	SetName("Menu");
}

MenuUI::~MenuUI()
{
}

void MenuUI::finaltick()
{
    if (!IsActive())
        return;

    render_update();
}

int MenuUI::render_update()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("Save Level"))
            {
                char LvName[64];
                strcpy_s(LvName, m_LevelName.c_str());
                ImGui::InputText("##SaveLevel", LvName, 31);
                m_LevelName = LvName;

                // Level 저장
                if (ImGui::MenuItem("Save"))
                {
                    std::wstring Path = L"Level\\" + ChangeToWString(m_LevelName) + L".lv";

                    CLevelSaveLoad::SaveLevel(Path, CLevelMgr::GetInst()->GetCurLevel());
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Load Level"))
            {
                char LvName[64];
                strcpy_s(LvName, m_LevelName.c_str());
                ImGui::InputText("##LoadLevel", LvName, 64);
                m_LevelName = LvName;
                // Level 불러오기
                if (ImGui::MenuItem("Load"))
                {



                    std::wstring Path = L"Level\\" + ChangeToWString(m_LevelName) + L".lv";
                    CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(Path);

                    if (pLoadedLevel)
                    {
                        tEvent evn = {};
                        evn.Type = EVENT_TYPE::LEVEL_CHANGE;
                        evn.wParam = (DWORD_PTR)pLoadedLevel;
                        evn.lParam = (DWORD_PTR)LEVEL_STATE::STOP;

                        CEventMgr::GetInst()->AddEvent(evn);
                    }
                }

                ImGui::EndMenu();
            }

            if (ImGui::MenuItem("New Level"))
            {
                std::wstring Path = L"Level\\NewLevel.lv";
                CLevel* pNewLevel = CLevelSaveLoad::LoadLevel(Path);

                if (pNewLevel)
                {
                    tEvent evn = {};
                    evn.Type = EVENT_TYPE::LEVEL_CHANGE;
                    evn.wParam = (DWORD_PTR)pNewLevel;
                    evn.lParam = (DWORD_PTR)LEVEL_STATE::STOP;

                    CEventMgr::GetInst()->AddEvent(evn);
                }
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("GameObject"))
        {
            // 현재 레벨에 게임오브젝트 생성
            if (ImGui::BeginMenu("Create Empty Object"))
            {
                ImGui::Text("ObjectName : ");
                ImGui::SameLine();

                char ObjName[64];
                strcpy_s(ObjName, m_ObjectName.c_str());
                ImGui::InputText("##CreateObj", ObjName, 64);
                m_ObjectName = ObjName;

                ImGui::Text("Layer Num  : ");
                ImGui::SameLine();
                ImGui::InputInt("##Layer", &m_Layer);

                if (ImGui::MenuItem("Create"))
                {
                    CreateEmptyObject(ChangeToWString(m_ObjectName), m_Layer);
                }
                ImGui::EndMenu();
            }

            
            if (ImGui::BeginMenu("Add Component"))
            {
                for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
                {
                    if (ImGui::MenuItem(ToString((COMPONENT_TYPE)i)))
                    {
                        AddComponent(COMPONENT_TYPE(i));
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::BeginMenu("Add Script"))
            {
                vector<wstring> vecScripts;
                CScriptMgr::GetScriptInfo(vecScripts);
                
                for (size_t i = 0; i < vecScripts.size(); ++i)
                {
                    string strScriptName = string(vecScripts[i].begin(), vecScripts[i].end());
                    if (ImGui::MenuItem(strScriptName.c_str()))
                    {
                        AddScript(vecScripts[i]);
                    }
                }
                
                ImGui::EndMenu();
            }

            //=============================================================Material
            if (ImGui::BeginMenu("Create Material"))
            {
                ImGui::Text("MtrlName : ");
                ImGui::SameLine();

                char MtrlName[64];
                strcpy_s(MtrlName, m_MtrlName.c_str());
                ImGui::InputText("##CreateMtrl", MtrlName, 64);
                m_MtrlName = MtrlName;

                ImGui::Checkbox("Std2d", &m_Std2D);
                ImGui::SameLine();
                ImGui::Checkbox("Std3d", &m_Std3D);
                ImGui::SameLine();
                ImGui::Checkbox("Std3dUI", &m_Std3DUI);
                ImGui::SameLine();
                ImGui::Checkbox("Std2dUI", &m_Distortion);   // 임시로 2DUI로 대체

                if (ImGui::MenuItem("Create"))
                {

                    Ptr<CMaterial> pMtrl = nullptr;
                    CResMgr* pRes = CResMgr::GetInst();
                    // Test Material
                    pMtrl = new CMaterial(true);

                    if (m_Std2D)
                        pMtrl->SetShader(pRes->FindRes<CGraphicsShader>(L"Std2DShader"));
                    else if (m_Std3D)
                        pMtrl->SetShader(pRes->FindRes<CGraphicsShader>(L"Std3D_DeferredShader"));
                    else if (m_Std3DUI)
                        pMtrl->SetShader(pRes->FindRes<CGraphicsShader>(L"Std3DUI_DeferredShader"));
                    else if (m_Distortion)
                        pMtrl->SetShader(pRes->FindRes<CGraphicsShader>(L"Std2DUIShader"));

                    pRes->AddRes(ChangeToWString(m_MtrlName), pMtrl);

                    ContentUI* Content = (ContentUI*)ImGuiMgr::GetInst()->FindUI("##Content");

                    Content->Reload();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Level"))
        {
            CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();
            bool PlayEnable = true;
            bool PauseEnable = true;
            bool StopEnable = true;

            if (CurLevel->GetState() == LEVEL_STATE::PLAY)
            {
                PlayEnable = false;
                PauseEnable = true;
                StopEnable = true;
            }
            else if (CurLevel->GetState() == LEVEL_STATE::PAUSE)
            {
                PlayEnable = true;
                PauseEnable = false;
                StopEnable = true;
            }
            else if (CurLevel->GetState() == LEVEL_STATE::STOP)
            {
                PlayEnable = true;
                PauseEnable = false;
                StopEnable = false;
            }



            if (ImGui::MenuItem("Play", nullptr, nullptr, PlayEnable))
            {                
                CLevelSaveLoad::SaveLevel(L"Level\\Temp.lv", CurLevel);
                CurLevel->ChangeState(LEVEL_STATE::PLAY);
            }
            else if (ImGui::MenuItem("Pause", nullptr, nullptr, PauseEnable))
            {
                CurLevel->ChangeState(LEVEL_STATE::PAUSE);
            }
            else if (ImGui::MenuItem("Stop", nullptr, nullptr, StopEnable))
            {
                CurLevel->ChangeState(LEVEL_STATE::STOP);
                CLevel* pNewLevel = CLevelSaveLoad::LoadLevel(L"Level\\Temp.lv");
             
                tEvent evn = {};
                evn.Type = EVENT_TYPE::LEVEL_CHANGE;
                evn.wParam = DWORD_PTR(pNewLevel);
                CEventMgr::GetInst()->AddEvent(evn);

                // InspectorUI
                InspectorUI* Inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");
                Inspector->SetTargetObject(nullptr);
            }

            ImGui::EndMenu();
        }




        ImGui::EndMainMenuBar();
    }

	return 0;
}

void MenuUI::CreateEmptyObject(const wstring& _ObjName, int _layer)
{
    CGameObject* pNewObject = new CGameObject;
    pNewObject->AddComponent(new CTransform);
    pNewObject->SetName(_ObjName);
    SpawnGameObject(pNewObject, Vec3(0.f, 0.f, 0.f), _layer);

    // Outliner 를 가져온다.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");

    // 새로추가된 오브젝트를 데이터로 하는 노드가 추가되면, 선택상태로 두게 한다.
    outliner->SetSelectedNodeData(DWORD_PTR(pNewObject));
}

void MenuUI::AddComponent(COMPONENT_TYPE _type)
{
    // Outliner 와 Inspector 를 가져온다.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    InspectorUI* inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");

    // 선택된 오브젝트를 가져와서 ComponentType 에 맞는 컴포넌트를 생성해서 추가한다.
    CGameObject* pSelectedObject = outliner->GetSelectedObject();

    if (nullptr == pSelectedObject)
        return;

    switch (_type)
    {
    case COMPONENT_TYPE::TRANSFORM:
        pSelectedObject->AddComponent(new CTransform);
        break;
    case COMPONENT_TYPE::COLLIDER2D:
        pSelectedObject->AddComponent(new CCollider2D);
        break;
    case COMPONENT_TYPE::COLLIDER3D:
        pSelectedObject->AddComponent(new CCollider3D);
        break;
    case COMPONENT_TYPE::ANIMATOR2D:
        pSelectedObject->AddComponent(new CAnimator2D);
        break;
    case COMPONENT_TYPE::ANIMATOR3D:
        pSelectedObject->AddComponent(new CAnimator3D);
        break;
    case COMPONENT_TYPE::LIGHT2D:
        pSelectedObject->AddComponent(new CLight2D);
        break;
    case COMPONENT_TYPE::LIGHT3D:
        pSelectedObject->AddComponent(new CLight3D);
        break;
    case COMPONENT_TYPE::CAMERA:
        pSelectedObject->AddComponent(new CCamera);
        break;
    case COMPONENT_TYPE::FONT:
        pSelectedObject->AddComponent(new CFont);
        break;
    case COMPONENT_TYPE::MESHRENDER:
        pSelectedObject->AddComponent(new CMeshRender);
        break;
    case COMPONENT_TYPE::PARTICLESYSTEM:
        pSelectedObject->AddComponent(new CParticleSystem);
        break;
    //case COMPONENT_TYPE::TILEMAP:
    //    pSelectedObject->AddComponent(new CTileMap);
    //    break;
    case COMPONENT_TYPE::SKYBOX:
        pSelectedObject->AddComponent(new CSkyBox);
        break;
    case COMPONENT_TYPE::LANDSCAPE:
        pSelectedObject->AddComponent(new CLandScape);
        break;
    case COMPONENT_TYPE::DECAL:
        pSelectedObject->AddComponent(new CDecal);
        break;            
    }

    // Inspector 에 새롭게 추가된 컴포넌트를 알리기 위해서 타겟을 다시 알려준다.
    inspector->SetTargetObject(pSelectedObject);

}

void MenuUI::AddScript(const wstring& _strScriptName)
{
    // Outliner 와 Inspector 를 가져온다.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    InspectorUI* inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");

    // 선택된 오브젝트를 가져와서 ComponentType 에 맞는 컴포넌트를 생성해서 추가한다.
    CGameObject* pSelectedObject = outliner->GetSelectedObject();

    if (nullptr == pSelectedObject)
        return;

    CScript* pScript = CScriptMgr::GetScript(_strScriptName);

    pSelectedObject->AddComponent(pScript);

    inspector->SetTargetObject(pSelectedObject);
}
