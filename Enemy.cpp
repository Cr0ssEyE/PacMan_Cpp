#include "Enemy.h"

#include "MainMap.h"
#include "EnemyState.h"
#include "Player.h"

static const int Xpos[4] = { 1, 0, -1, 0 };
static const int Ypos[4] = { 0, 1, 0, -1 };

Enemy::Enemy()
{
    GameMap = nullptr;
    PathMap = nullptr;
    Parent = nullptr;
    DetectedPlayer = nullptr;
    CurrentState = InBox::GetInstance();
    DefaultColor = RED;
    Color = RED;
    DetectRange = 4;
    TraceRange = 6;
}

Enemy::~Enemy()
{
    
}

void Enemy::Update(Player* Player, int Time)
{
    if(!DetectedPlayer)
    {
        DetectPlayer(Player);
    }
    UpdateTime = Time;
    CurrentState->Execute(this, PathMap, DetectedPlayer, TargetLocation);
    FindPath();
}

void Enemy::draw()
{
    SetColor(Color);
    GameObject::draw();
}

void Enemy::InitEnemy(int x, int y, unsigned short c, MainMap* GameMap)
{
    Pos.first = x;
    Pos.second = y;
    SpawnLocation = make_pair(x, y);
    TargetLocation = make_pair(x, y);
    DefaultColor = c;
    this->Color = c;
    this->GameMap = GameMap;
    PathMap = GameMap;
    Object_Img = const_cast<wchar_t*>(L"Ω");
    Parent = new pair<int, int> * [GameMapHeight];
    for (int h = 0; h < GameMapHeight; h++)
    {
        Parent[h] = new pair<int, int>[GameMapWidth];
    }
    ChangeState(InBox::GetInstance());
    ClearMapInfo();
}

void Enemy::ExtractMin(pair<int, int>& Pos, int dx, int dy)
{
    int Min = INT_MAX;
    int Width = GameMapWidth;
    int Height = GameMapHeight;

    int CurX, CurY;
    list<pair<int, int>>::reverse_iterator CurPos;
    for (CurPos = VisitPoint.rbegin(); CurPos != VisitPoint.rend(); CurPos++)
    {
        for (int i = 0; i < 4; i++)
        {
            CurX = CurPos->first + Xpos[i];
            CurY = CurPos->second + Ypos[i];
            if (CurX < 0 || CurX > Height - 1 || CurY < 0 || CurY > Width - 1)
            {
                continue;
            }
				
            int hx = abs(dx - CurX) * 10;
            int hy = abs(dy - CurY) * 10;
            int hdist = hx + hy;
                
            if (PathMap->GetWeightInfo(CurX, CurY) +hdist < Min && !PathMap->GetVisitInfo(CurX, CurY))
            {
                Min = PathMap->GetWeightInfo(CurX, CurY) + hdist;
                Pos = make_pair(CurX, CurY);
            }
        }
    }
}

void Enemy::FindPath()
{
    bool m_bFound = false;
    pair<int, int> TrackPos = Pos;
    Parent[TrackPos.first][TrackPos.second] = TrackPos;
    PathMap->SetWeightInfo(TrackPos.first, TrackPos.second, 0);
    
    for (int i = 0; i < GameMapWidth * GameMapHeight; i++)
    {
        PathMap->SetVisitInfo(TrackPos.first, TrackPos.second, true);
        VisitPoint.push_back(TrackPos);

        if (TrackPos == TargetLocation)
        {
            m_bFound = true;
            break;
        }

        for (int i = 0; i < 5; i++)
        {
            int nX = TrackPos.first + Xpos[i];
            int nY = TrackPos.second + Ypos[i];
            int dist;
            if (nX < 0 || nX > GameMapHeight - 1 || nY < 0 || nY > GameMapWidth - 1)
            {
                continue;
            }

            if (!PathMap->GetVisitInfo(nX, nY))
            {
                dist = 1;
                int NewMapVal = PathMap->GetWeightInfo(TrackPos.first, TrackPos.second) + dist;
                if (PathMap->GetWeightInfo(nX, nY) > NewMapVal)
                {
                    PathMap->SetWeightInfo(nX, nY, NewMapVal);
                    Parent[nX][nY] = TrackPos;
                }
            }
        }
        ExtractMin(TrackPos, TargetLocation.first, TargetLocation.second);
    }
    
    if (m_bFound)
    {
        pair<int, int> p = TargetLocation;
        PathStack.push(p);
        while (p.first != Pos.first || p.second != Pos.second)
        {
            p = Parent[p.first][p.second];
            if(!p.first && !p.second)
            {
                break;
            }
            PathStack.push(p);
        }
        if(!PathStack.empty())
        {
            PathStack.pop();
            if(!PathStack.empty())
            {
                Pos = PathStack.top();
            }
            while (!PathStack.empty())
            {
                PathStack.pop();
            }
        }
    }
    ClearMapInfo();
}

void Enemy::ClearMapInfo()
{
    PathMap->ResetInfo();
    VisitPoint.clear();
}

void Enemy::DetectPlayer(Player* Player)
{
    bool Detected = false;
    // 4방향 탐지
    for (int i = 0; i < 4; i++)
    {
        if(Detected)
        {
            break;
        }
        int Detect_sx = Pos.first + Xpos[i];
        int Detect_sy = Pos.second + Ypos[i];
        for (int j = 0; j < DetectRange; j++)
        {
            int Detect_nx = Detect_sx + Xpos[i] * j;
            int Detect_ny = Detect_sy + Ypos[i] * j;
            if(Detect_nx >= 0 && Detect_nx < GameMapHeight - 1 && Detect_ny >= 0 && Detect_ny < GameMapWidth - 1)
            {
                if(Detect_nx == Player->GetX() && Detect_ny == Player->GetY())
                {
                    Detected = true;
                    DetectedPlayer = Player;
                    break;
                }
                if(GameMap->GetMapImg(Detect_nx, Detect_ny) == const_cast<wchar_t*>(L"■"))
                {
                    break;
                }
            }
        }
    }
    if(!Detected)
    {
        DetectedPlayer = nullptr;
    }
}

void Enemy::ChangeState(EnemyState* NewState)
{
    CurrentState->ExitState(this);
    CurrentState = NewState;
    CurrentState->EnterState(this);
}