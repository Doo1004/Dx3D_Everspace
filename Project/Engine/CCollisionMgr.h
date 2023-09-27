#pragma once
#include "CSingleton.h"

class CLayer;
class CCollider2D;
class CCollider3D;


union CollisionID
{
	struct
	{
		UINT LeftID;
		UINT RightID;
	};

	UINT_PTR id;
};


class CCollisionMgr :
	public CSingleton<CCollisionMgr>
{
	SINGLE(CCollisionMgr);
private:
	UINT					m_matrix[MAX_LAYER];
	map<UINT_PTR, bool>		m_mapColID;

public:
	void LayerCheck(UINT _left, UINT _right);
	void LayerCheck(const wstring& _strLeftLayer, const wstring& _strRightLayer);
	bool IsLayerColliding(UINT _left, UINT _right);
	void ModifyLayerCollision(UINT _left, UINT _right, bool _collide);

	void Clear()
	{
		memset(m_matrix, 0, sizeof(UINT) * MAX_LAYER);
	}

public:
	void tick();

private:
	void CollisionBtwLayer(CLayer* _LeftLayer, CLayer* _RightLayer);
	void CollisionBtwObject(CGameObject* _LeftObject, CGameObject* _RightObject);
	bool CollisionBtwCollider2D(CCollider2D* _pLeft, CCollider2D* _pRight);
	bool CollisionBtwCollider3D(CCollider3D* _pLeft, CCollider3D* _pRight);

	bool CollisionBtwCube(CCollider3D* _pLeft, CCollider3D* _pRight);
	bool CollisionBtwSphere(CCollider3D* _pLeft, CCollider3D* _pRight);
	bool CollisionBtwCubeToSphere(CCollider3D* _pCube, CCollider3D* _pSphere);
};

