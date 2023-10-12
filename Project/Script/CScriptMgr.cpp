#include "pch.h"
#include "CScriptMgr.h"

#include "CCameraMoveScript.h"
#include "CBackFireScript.h"
#include "CBulletScript.h"
#include "CUIScript.h"
#include "CExplosionScript.h"
#include "CMuzzleScript.h"
#include "CMonsterScript.h"
#include "CPlayerScript.h"
#include "CMapObjectScript.h"
#include "CNavObjScript.h"
#include "CHPBarScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CBackFireScript");
	_vec.push_back(L"CBulletScript");
	_vec.push_back(L"CUIScript");
	_vec.push_back(L"CExplosionScript");
	_vec.push_back(L"CMuzzleScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CMapObjectScript");
	_vec.push_back(L"CNavObjScript");
	_vec.push_back(L"CHPBarScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CBackFireScript" == _strScriptName)
		return new CBackFireScript;
	if (L"CBulletScript" == _strScriptName)
		return new CBulletScript;
	if (L"CUIScript" == _strScriptName)
		return new CUIScript;
	if (L"CExplosionScript" == _strScriptName)
		return new CExplosionScript;
	if (L"CMuzzleScript" == _strScriptName)
		return new CMuzzleScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CMapObjectScript" == _strScriptName)
		return new CMapObjectScript;
	if (L"CNavObjScript" == _strScriptName)
		return new CNavObjScript;
	if (L"CHPBarScript" == _strScriptName)
		return new CHPBarScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::BACKFIRESCRIPT:
		return new CBackFireScript;
		break;
	case (UINT)SCRIPT_TYPE::BULLETSCRIPT:
		return new CBulletScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CUIScript;
		break;
	case (UINT)SCRIPT_TYPE::EXPLOSIONSCRIPT:
		return new CExplosionScript;
		break;
	case (UINT)SCRIPT_TYPE::MUZZLESCRIPT:
		return new CMuzzleScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::MAPOBJECTSCRIPT:
		return new CMapObjectScript;
		break;
	case (UINT)SCRIPT_TYPE::NAVOBJSCRIPT:
		return new CNavObjScript;
		break;
	case (UINT)SCRIPT_TYPE::HPBARSCRIPT:
		return new CHPBarScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::BACKFIRESCRIPT:
		return L"CBackFireScript";
		break;

	case SCRIPT_TYPE::BULLETSCRIPT:
		return L"CBulletScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CUIScript";
		break;

	case SCRIPT_TYPE::EXPLOSIONSCRIPT:
		return L"CExplosionScript";
		break;

	case SCRIPT_TYPE::MUZZLESCRIPT:
		return L"CMuzzleScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::MAPOBJECTSCRIPT:
		return L"CMapObjectScript";
		break;

	case SCRIPT_TYPE::NAVOBJSCRIPT:
		return L"CNavObjScript";
		break;

	case SCRIPT_TYPE::HPBARSCRIPT:
		return L"CHPBarScript";
		break;
	}
	return nullptr;
}