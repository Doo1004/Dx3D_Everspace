#pragma once
#include "CRes.h"

class CGameObject;

class CPrefab :
    public CRes
{
private:
	CGameObject*	m_ProtoObj;

public:
	CGameObject* Instantiate();
	CGameObject* GetProtoObj() { return m_ProtoObj; }

private:
	virtual int Load(const wstring& _strFilePath) { return S_OK; }
public:
	virtual int Save(const wstring& _strRelativePath) { return S_OK; }
	int SavePref(const wstring& _Filename);
	int LoadPref(const wstring& _Filename);

public:
	void RegisterProtoObject(CGameObject* _Proto);

public:
	CPrefab(bool _bEngine = false);
	~CPrefab();
};

