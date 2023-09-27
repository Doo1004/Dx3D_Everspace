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

    int                 m_iHP;                  // 몬스터 체력
    int                 m_iMaxHP;               // 몬스터 최대 체력
    float               m_fHPRatio;             // 몬스터 체력 비율
    int                 m_iShootDist;           // 몬스터 사거리
    float               m_fSpeed;               // 몬스터 스피드
    float               m_fMoveDT;              // 몬스터 랜덤 움직임 쿨타임 계산
    bool                m_bIncreaseCoolTime;    // 몬스터 랜덤 움직임 쿨타임 예외 처리;
    bool                m_bRandomMove;          // 몬스터 움직임 예외 처리
    Vec3                m_vRandomDir;

    float               m_fBulletDelay;         // 몬스터 총알 딜레이
    float               m_fBulletDT;

    float               m_fPlayerDistance;      // 플레이어와의 거리
    
    float               m_fExScale;             // Explosion 오브젝트 관련
    float               m_fExLifeTime;

    Vec3                m_vPlayerPos;
    Vec3                m_vPlayerDir;           // 몬스터에서 플레이어까지의 방향
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

    void SetBeginData();      // 몬스터 초기 설정

    float CalculateVolume(float _fDist, float _fMin, float _fMax)
    {
        const float MIN_DISTANCE = _fMin; //300.0f
        const float MAX_DISTANCE = _fMax; //1400.0f

        // m_fPlayerDistance가 MIN_DISTANCE 이하이면 볼륨은 최대
        if (_fDist <= MIN_DISTANCE)
            return 1.0f;
        // m_fPlayerDistance가 MAX_DISTANCE 이상이면 볼륨은 최소
        else if (_fDist >= MAX_DISTANCE)
            return 0.0f;
        // 그 사이의 거리에서는 선형적으로 감소
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


