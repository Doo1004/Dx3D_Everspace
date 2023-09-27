#pragma once
#include "CComponent.h"

class CCollider3D :
    public CComponent
{
private:
    Vec3                m_vOffsetPos;
    Vec3                m_vOffsetScale;
    bool                m_bAbsolute;
    COLLIDER3D_TYPE     m_Shape;
    Matrix              m_matCollider3D;        // Collider 의 월드행렬

    std::vector<Matrix> m_vecCollider3D;        // Collider3D 컨테이너

    bool                m_bShowColliderShape;   // DebugShape 표시 여부

    int                 m_iCollisionCount;      // 충돌 횟수


public:
    virtual void finaltick() override;

public:
    void SetOffsetPos(Vec3 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetOffsetScale(Vec3 _vOffsetScale) { m_vOffsetScale = _vOffsetScale; }
    void SetAbsolute(bool _bSet) { m_bAbsolute = _bSet; }
    void SetCollider3DType(COLLIDER3D_TYPE _Type) { m_Shape = _Type; }
    void SetShowColliderShape(bool _Show) { m_bShowColliderShape = _Show; }

    Vec3 GetOffsetPos() { return m_vOffsetPos; }
    Vec3 GetOffsetScale() { return m_vOffsetScale; }
    bool IsUseAbsolute() { return m_bAbsolute; }
    bool IsShowColliderShape() { return m_bShowColliderShape; }
    COLLIDER3D_TYPE GetCollider3DType() { return m_Shape; }

    const Matrix& GetColliderWorldMat() { return m_matCollider3D; }


//public:
//    void AddCollider3D(const Matrix& _Collider3D);
//    void DelCollider3D(int _Index);

public:
    void BeginOverlap(CCollider3D* _Other);
    void OnOverlap(CCollider3D* _Other);
    void EndOverlap(CCollider3D* _Other);

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CCollider3D);
public:
    CCollider3D();
    ~CCollider3D();
};

