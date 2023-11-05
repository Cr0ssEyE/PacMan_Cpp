#pragma once
#include <iostream>
using namespace std;

class Player;
class MainMap;
class Enemy;
class Hunter;
class Hunted;
class Eaten;

#define IN_BOX_TIME 5

class EnemyState
{
public:
    EnemyState() { }
    virtual ~EnemyState() { }

    virtual void EnterState(Enemy* Ghost) { }
    virtual void Execute(Enemy* Ghost, MainMap* GameMap, Player* DetectedPlayer, pair<int, int> TargetLocation) { }
    virtual void ExitState(Enemy* Ghost) { }
    
protected:
    
};

class InBox : public EnemyState
{
public:
    InBox() { BeginPlay = true; }
    virtual ~InBox() override { }

    static InBox* GetInstance();
    virtual void EnterState(Enemy* Ghost) override;
    virtual void Execute(Enemy* Ghost, MainMap* GameMap, Player* DetectedPlayer, pair<int, int> TargetLocation) override;
    virtual void ExitState(Enemy* Ghost) override;

private:
    int InBoxTimer;
    bool BeginPlay;
};
class Hunter : public EnemyState
{
public:
    Hunter() { }
    virtual ~Hunter() override { }

    static Hunter* GetInstance();
    virtual void EnterState(Enemy* Ghost) override;
    virtual void Execute(Enemy* Ghost, MainMap* GameMap, Player* DetectedPlayer, pair<int, int> TargetLocation) override;
    virtual void ExitState(Enemy* Ghost) override;
    
private:
    
};

class Hunted : public EnemyState
{
public:
    Hunted() { }
    virtual ~Hunted() override { }

    static Hunted* GetInstance();
    virtual void EnterState(Enemy* Ghost) override;
    virtual void Execute(Enemy* Ghost, MainMap* GameMap, Player* DetectedPlayer, pair<int, int> TargetLocation) override;
    virtual void ExitState(Enemy* Ghost) override;
private:
    
};

class Eaten : public EnemyState
{
public:
    Eaten() { }
    virtual ~Eaten() override { }

    static Eaten* GetInstance();
    virtual void EnterState(Enemy* Ghost) override;
    virtual void Execute(Enemy* Ghost, MainMap* GameMap, Player* DetectedPlayer, pair<int, int> TargetLocation) override;
    virtual void ExitState(Enemy* Ghost) override;
private:
    
};