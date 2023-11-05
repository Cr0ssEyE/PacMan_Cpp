#pragma once

#include <iostream>
#include <list>
#include <stack>

#include "GameObject.h"

class MainMap;
class EnemyState;
class Player;

class Enemy : public GameObject
{
public:
    Enemy();
    ~Enemy();
    
    void Update(Player* Player, int Time);
    void draw() override;
    void InitEnemy(int x, int y, unsigned short c, MainMap* GameMap);
    void ChangeState(EnemyState* NewState);

    FORCEINLINE int GetInBoxTime() const { return InBoxElapsedTime; }
    
    FORCEINLINE void UpdateInBoxTime() { InBoxElapsedTime += clock() - UpdateTime; }
    
    FORCEINLINE int GetTraceRange() const { return TraceRange; }
    
    FORCEINLINE pair<int, int> GetSpawnLocation() const { return SpawnLocation; }
    
    FORCEINLINE void SetTargetLocation(int x, int y) { TargetLocation = make_pair(x, y); }
    
    FORCEINLINE void SetRange(int d, int t) { DetectRange = d; TraceRange = t; }
    
    FORCEINLINE void SetDefaultColor() { Color = DefaultColor; }
    
    FORCEINLINE void SetDrawColor(unsigned short c) { Color = c; }
    
private:
    // 최단 경로 탐색(A*)
    void ExtractMin(pair<int, int>& Pos, int x, int y);
    void FindPath();
    void ClearMapInfo();
    
    // 범위 탐색
    void DetectPlayer(Player* Player);

    // FSM
    void CheckState(Player* Player);
    
private:
    MainMap* GameMap;
    MainMap* PathMap;
    pair<int, int>** Parent;
    
    EnemyState* CurrentState;
    Player* DetectedPlayer;
    unsigned short DefaultColor;
    unsigned short Color;
    
    pair<int, int> SpawnLocation;
    pair<int, int> TargetLocation;

    stack<pair<int, int>> PathStack;
    list<pair<int, int>> VisitPoint;

    int DetectRange;
    int TraceRange;

    int UpdateTime;
    int InBoxElapsedTime;
};
