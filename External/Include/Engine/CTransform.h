#pragma once
#include "CComponent.h"

class CTransform :
    public CComponent
{
private:
    Vec3                m_vRelativePos;
    Vec3                m_vRelativeScale;
    Vec3                m_vRelativeRot;

    bool                m_bAbsolute;        // ��� �̵�, ũ�⸦ ���밪���� ����    

    Vec3                m_vRelativeDir[3];
    Vec3                m_vWorldDir[3];

    Matrix              m_matWorldScale;    // ���� ũ�� ���
    Matrix	            m_matRelativeRot;   // ���� ȸ�� ���

    Matrix              m_matWorld;         // ũ��, ȸ��, �̵� ������ ���ĳ���
    Matrix              m_matWorldInv;      // ���� �����

    Quaternion          m_qOrientation;
    Vec3                m_vQuaternionRot;
    Quaternion          m_qRelativeRot;     // ���ʹϾ� ȸ���� ���� ��� ���� �߰�
    bool                m_bQuaternion;


public:
    void SetQuaternionRot(Vec3 _vSpeed) { m_bQuaternion = true; m_vQuaternionRot = _vSpeed; }
    void SetQuaternionRotX(float _xSpeed) { m_bQuaternion = true; m_vQuaternionRot.x = _xSpeed; }
    void SetQuaternionRotY(float _ySpeed) { m_bQuaternion = true; m_vQuaternionRot.y = _ySpeed; }
    void SetQuaternionRotZ(float _zSpeed) { m_bQuaternion = true; m_vQuaternionRot.z = _zSpeed; }

    void SetRelativePos(Vec3 _vPos) { m_vRelativePos = _vPos; }
    void SetRelativeScale(Vec3 _vScale) { m_vRelativeScale = _vScale; }
    void SetRelativeRot(Vec3 _vRot) { m_bQuaternion = false; m_vRelativeRot = _vRot; }

    void SetRelativePos(float _x, float _y, float _z) { m_vRelativePos = Vec3(_x, _y, _z); }
    void SetRelativeScale(float _x, float _y, float _z) { m_vRelativeScale = Vec3(_x, _y, _z); }
    void SetRelativeRot(float _x, float _y, float _z) { m_bQuaternion = false; m_vRelativeRot = Vec3(_x, _y, _z);  }

    bool IsUseQuaternion() { return m_bQuaternion; }

    // ��� �̵�, ũ�⸦ ���밪���� ����  
    void SetAbsolute(bool _Set) { m_bAbsolute = _Set; }    
    bool IsUseAbsolute() { return m_bAbsolute; }

    Vec3 GetRelativePos() const { return m_vRelativePos; }
    Vec3 GetRelativeScale() const { return m_vRelativeScale; }
    Vec3 GetRelativeRot() const { return m_vRelativeRot; }

    Vec3 GetRelativeDir(DIR_TYPE _type) const { return m_vRelativeDir[(UINT)_type]; }
    Vec3 GetWorldDir(DIR_TYPE _type) const { { return m_vWorldDir[(UINT)_type]; } }
    Vec3 GetWorldPos() { return m_matWorld.Translation(); }

    Matrix GetWorldRotation();

    const Matrix& GetWorldScaleMat() { return m_matWorldScale; }
    const Matrix& GetWorldMat() const { return m_matWorld; }
    const Matrix& GetWorldInvMat() const{ return m_matWorldInv; }

    void SetWorldMat(const Matrix& _mat) { m_matWorld = _mat; }

public:
    virtual void finaltick() override;    
    void UpdateData();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CTransform);
public:
    CTransform();
    ~CTransform();
};
