#include "pch.h"
#include "PrefabUI.h"
#include <Engine\CPrefab.h>
#include <Engine\CPathMgr.h>
#include <Engine\CResMgr.h>
#include "CLevelSaveLoad.h"


PrefabUI::PrefabUI()
    :ResUI(RES_TYPE::PREFAB)
{
    SetName("Prefab");
}

PrefabUI::~PrefabUI()
{

}

int PrefabUI::render_update()
{
    ResUI::render_update();
    
    CPrefab* pPref = (CPrefab*)GetTargetRes().Get();
    

    //ImGui::Text("IsLoadedPrefObj? : ");
    //ImGui::SameLine();
    //
    //if (!pPref->GetProtoObj())
    //{
    //    ImGui::Text("N");
    //    ImGui::SameLine();
    //    if (ImGui::Button("LoadObj"))
    //        pPref->LoadPref(pPref->GetRelativePath());
    //}
    //else
    //    ImGui::Text("Y");

    ImGui::InputInt("InputLayerIndex", &m_Layer);
    
    if (ImGui::Button("Prefab Save", ImVec2(110.f, 18.f)))
        pPref->SavePref(pPref->GetName());
    
    ImGui::SameLine();
    
    if (ImGui::Button("Prefab Insert", ImVec2(110.f, 18.f)))
    {
        if (!pPref->GetProtoObj())
            pPref->LoadPref(pPref->GetRelativePath());

        CGameObject* pPrefabObj = pPref->Instantiate();
        SpawnGameObject(pPrefabObj, Vec3(0.f, 0.f, 1.f), m_Layer);
    }
    
    ImGui::Text("Layer Detail");
    
    return 0;
}

int CPrefab::SavePref(const wstring& _Filename)
{
    wstring strPath = CPathMgr::GetInst()->GetContentPath();
    strPath += L"prefab\\" + _Filename + L".pref";

    FILE* pFile = nullptr;
    _wfopen_s(&pFile, strPath.c_str(), L"wb");

    if (nullptr == pFile)
        return E_FAIL;

    CLevelSaveLoad::SaveGameObject(m_ProtoObj, pFile);

    fclose(pFile);

    return S_OK;
}

int CPrefab::LoadPref(const wstring& _strRelativePath)
{
    wstring strPath = CPathMgr::GetInst()->GetContentPath();
    strPath += _strRelativePath;

    FILE* pFile = nullptr;
    _wfopen_s(&pFile, strPath.c_str(), L"rb");

    if (nullptr == pFile)
        return 0;

    m_ProtoObj = CLevelSaveLoad::LoadGameObject(pFile);

    fclose(pFile);

    return 0;
}