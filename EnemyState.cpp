#include "EnemyState.h"
#include "Enemy.h"
#include "MainMap.h"
#include "Player.h"

///////////////////////////////////////////////////////////////////////////////

InBox* InBox::GetInstance()
{
    static InBox* instance;
    if (instance == nullptr)
    {
        instance = new InBox;
    }
    return instance;
}

void InBox::EnterState(Enemy* Ghost)
{
    EnemyState::EnterState(Ghost);
    Ghost->SetImg(const_cast<wchar_t*>(L"▣"));
    InBoxTimer = 0;
}

void InBox::Execute(Enemy* Ghost, MainMap* GameMap, Player* DetectedPlayer, pair<int, int> TargetLocation)
{
    EnemyState::Execute(Ghost, GameMap, DetectedPlayer, TargetLocation);
    
    if(!GameMap->CheckClosed() && BeginPlay < 4)
    {
        BeginPlay++;
        Ghost->ChangeState(Hunter::GetInstance());
        return;
    }
    Ghost->UpdateInBoxTime();
    if(Ghost->GetInBoxTime() > IN_BOX_TIME * 1000)
    {
        Ghost->ChangeState(Hunter::GetInstance());
    }
}

void InBox::ExitState(Enemy* Ghost)
{
    EnemyState::ExitState(Ghost);
    Ghost->SetImg(const_cast<wchar_t*>(L"Ω"));
}

///////////////////////////////////////////////////////////////////////////////

Hunter* Hunter::GetInstance()
{
    static Hunter* instance;
    if (instance == nullptr)
    {
        instance = new Hunter;
    }
    return instance;
}

void Hunter::EnterState(Enemy* Ghost)
{
    EnemyState::EnterState(Ghost);
    Ghost->SetDefaultColor();
}

void Hunter::Execute(Enemy* Ghost, MainMap* GameMap, Player* DetectedPlayer, pair<int, int> TargetLocation)
{
    EnemyState::Execute(Ghost, GameMap, DetectedPlayer, TargetLocation);
    if(DetectedPlayer)
    {
        if(Ghost->collision(DetectedPlayer) && !DetectedPlayer->CheckPowered())
        {
            DetectedPlayer->SetDead(true);
            return;
        }
        const int TraceRange = Ghost->GetTraceRange();
        // 이미 발견한 상태라면 탐지 범위보다 큰 범위의 정사각형 범위 체크
        if(DetectedPlayer->GetX() > Ghost->GetX() - TraceRange && DetectedPlayer->GetX() < Ghost->GetX() + TraceRange && DetectedPlayer->GetY() > Ghost->GetY() - TraceRange && DetectedPlayer->GetY() < Ghost->GetY() + TraceRange)
        {
            Ghost->SetTargetLocation(DetectedPlayer->GetX(), DetectedPlayer->GetY());
        }
        else
        {
            DetectedPlayer = nullptr;
            Execute(Ghost, GameMap, DetectedPlayer, TargetLocation);
            return;
        }
        if(DetectedPlayer->CheckPowered())
        {
            Ghost->ChangeState(Hunted::GetInstance());
            return;
        }
    }
    else if((TargetLocation.first == Ghost->GetX() && TargetLocation.second == Ghost->GetY()) || (!TargetLocation.first && !TargetLocation.second))
    {
        while (true)
        {
            TargetLocation = make_pair(1 + rand() % (GameMapHeight - 2), 1 + rand() % (GameMapWidth - 2));
            if(GameMap->GetMapImg(TargetLocation.first, TargetLocation.second) != const_cast<wchar_t*>(L"■"))
            {
                Ghost->SetTargetLocation(TargetLocation.first, TargetLocation.second);
                break;
            }
        }
    }
    
}

void Hunter::ExitState(Enemy* Ghost)
{
    EnemyState::ExitState(Ghost);
}

///////////////////////////////////////////////////////////////////////////////

Hunted* Hunted::GetInstance()
{
    static Hunted* instance;
    if (instance == nullptr)
    {
        instance = new Hunted;
    }
    return instance;
}

void Hunted::EnterState(Enemy* Ghost)
{
    EnemyState::EnterState(Ghost);
    Ghost->SetDrawColor(WHITE);
}

void Hunted::Execute(Enemy* Ghost, MainMap* GameMap, Player* DetectedPlayer, pair<int, int> TargetLocation)
{
    EnemyState::Execute(Ghost, GameMap, DetectedPlayer, TargetLocation);
    if(DetectedPlayer)
    {
        if(Ghost->collision(DetectedPlayer))
        {
            Ghost->ChangeState(Eaten::GetInstance());
            DetectedPlayer = nullptr;
            return;
        }
        if(!DetectedPlayer->CheckPowered())
        {
            Ghost->ChangeState(Hunter::GetInstance());
            Ghost->SetTargetLocation(0, 0);
            return;
        }
        // 플레이어와 가장 먼 모서리로 위치 찍기
        int TargetX = GameMapHeight / 2 - DetectedPlayer->GetX() > 0 ? GameMapHeight - 2 : 1;
        int TargetY = GameMapWidth / 2 - DetectedPlayer->GetY() > 0 ? GameMapWidth - 2 : 1;
        GameMap->SetVisitInfo(DetectedPlayer->GetX(), DetectedPlayer->GetY(), true);
        Ghost->SetTargetLocation(TargetX, TargetY);
    }
}

void Hunted::ExitState(Enemy* Ghost)
{
    EnemyState::ExitState(Ghost);
    
}

///////////////////////////////////////////////////////////////////////////////

Eaten* Eaten::GetInstance()
{
    static Eaten* instance;
    if (instance == nullptr)
    {
        instance = new Eaten;
    }
    return instance;
}

void Eaten::EnterState(Enemy* Ghost)
{
    EnemyState::EnterState(Ghost);
    Ghost->SetDrawColor(DARKGRAY);
}

void Eaten::Execute(Enemy* Ghost, MainMap* GameMap, Player* DetectedPlayer, pair<int, int> TargetLocation)
{
    EnemyState::Execute(Ghost, GameMap, DetectedPlayer, TargetLocation);
    if(Ghost->GetX() == Ghost->GetSpawnLocation().first && Ghost->GetY() == Ghost->GetSpawnLocation().second)
    {
        Ghost->ChangeState(InBox::GetInstance());
        return;
    }
    if(TargetLocation != Ghost->GetSpawnLocation())
    {
        // 시작 지점으로 돌아가기
        Ghost->SetTargetLocation(Ghost->GetSpawnLocation().first, Ghost->GetSpawnLocation().second);
    }
}

void Eaten::ExitState(Enemy* Ghost)
{
    EnemyState::ExitState(Ghost);
    Ghost->SetDefaultColor();
}
