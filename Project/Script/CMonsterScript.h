#pragma once
#include <Engine\CScript.h>

class CMonsterScript :
    public CScript
{
private:

    enum class eSTATUS
    {
        MOVE,
        ATTACK,
        DEAD,
    };

    int                 m_iHP;                  // ���� ü��
    int                 m_iMaxHP;               // ���� �ִ� ü��
    float               m_fHPRatio;             // ���� ü�� ����
    int                 m_iShootDist;           // ���� ��Ÿ�
    float               m_fSpeed;               // ���� ���ǵ�
    float               m_fMoveDT;              // ���� ���� ������ ��Ÿ�� ���
    bool                m_bIncreaseCoolTime;    // ���� ���� ������ ��Ÿ�� ���� ó��;
    bool                m_bRandomMove;          // ���� ������ ���� ó��
    Vec3                m_vRandomDir;

    float               m_fBulletDelay;         // ���� �Ѿ� ������
    float               m_fBulletDT;

    float               m_fPlayerDistance;      // �÷��̾���� �Ÿ�
    
    float               m_fExScale;             // Explosion ������Ʈ ����
    float               m_fExLifeTime;

    Vec3                m_vPlayerPos;
    Vec3                m_vPlayerDir;           // ���Ϳ��� �÷��̾������ ����
    Vec3                m_vCurPos;
    Vec3                m_vTextPos;
    Vec3                m_vMobBulletPos;

    //===================BossMonster
    Vec3                m_vBulletParticlePos;

    int                 m_iRandomAttack;

    float               m_fAttackDT;
    float               m_fAttackDelay;
    float               m_fAttackDelayDT;

    float               m_fVolume;

    float               m_fSummonMarkRot;

    bool                m_bAttack;
    //==============================

    CGameObject*        m_pPlayer;
    CGameObject*        m_pHPGauge;
    CGameObject*        m_pMark;
    CGameObject*        m_pMarkDecal;
    CGameObject*        m_pBulletParticle;

    eSTATUS             m_eStatus;

    void CreateHPGauge();
    void CreateExplosionObj();
    void GetObjData();
    void SetMonsterData();
    void ActiveMonster();
    void BulletFire(Vec3 _Dir);

    void CreateBossParticle();
    void CreateBossSummonMark();
    void ActiveBossMonster();
    void SummonMonster();

    void SetBeginData();      // ���� �ʱ� ����

    float CalculateVolume(float _fDist, float _fMin, float _fMax)
    {
        const float MIN_DISTANCE = _fMin; //300.0f
        const float MAX_DISTANCE = _fMax; //1400.0f

        // m_fPlayerDistance�� MIN_DISTANCE �����̸� ������ �ִ�
        if (_fDist <= MIN_DISTANCE)
            return 1.0f;
        // m_fPlayerDistance�� MAX_DISTANCE �̻��̸� ������ �ּ�
        else if (_fDist >= MAX_DISTANCE)
            return 0.0f;
        // �� ������ �Ÿ������� ���������� ����
        else
            return 1.0f - (_fDist - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE);
    }



public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CMonsterScript);
public:
    CMonsterScript();
    ~CMonsterScript();
};


