#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

#include "Enemy.h"
#include "util.h"
#include "MainMap.h"
#include "Player.h"

#define ENEMY_NUM 4
#define ACTIVATE_GHOST_SECOND 5
#define POWERFUL_STATE_SECOND 10
#define UPDATE_SECOND 0.2

using namespace std;

void main()
{
    bool GameClear = false;
    MainMap* GameMap = new MainMap();
    GameMap->initMap();

    Player* PlayerCharacter = new Player();
    PlayerCharacter->InitPlayer(GameMapHeight / 2, GameMapWidth - 2, GameMap);

    Enemy* Ghost[4];
    Ghost[0] = new Enemy();
    Ghost[0]->InitEnemy(GameMapHeight / 2 - 1, GameMapWidth / 2 - 1, RED, GameMap);
    
    Ghost[1] = new Enemy();
    Ghost[1]->InitEnemy(GameMapHeight / 2 - 1, GameMapWidth / 2 + 1, LIGHTGREEN, GameMap);
    
    Ghost[2] = new Enemy();
    Ghost[2]->InitEnemy(GameMapHeight / 2 + 1, GameMapWidth / 2 - 1, LIGHTCYAN, GameMap);
    
    Ghost[3] = new Enemy();
    Ghost[3]->InitEnemy(GameMapHeight / 2 + 1, GameMapWidth / 2 + 1, LIGHTMAGENTA, GameMap);

    for (auto G : Ghost)
    {
        G->SetRange(4, 6);
    }
    // Ghost[0]->Update(PlayerCharacter);
    // return;
    ScreenInit();
    int Movement = 4;
    int GhostUpdateStack = 0, PowerfulStateCheck = 0, ActivateGhostTimeCheck = 0;
    while (true)
    {
        if(PlayerCharacter->CheckDead())
        {
            ScreenClear();
            ScreenRelease();
            break;
        }
        srand(static_cast<unsigned>(time(nullptr)));
        
        int Timer = clock(), UpdateTimeCheck = 0;
        int PressKey = 0;
        bool BeginPlay = false;
        bool PowerOffBegin = false;
        
        if (_kbhit())
        {
            if (_getch() == 224)
            {
                PressKey = _getch();
                switch (PressKey)
                {
                case UP:
                    Movement = 0;
                    break;
                case DOWN:
                    Movement = 1;
                    break;
                case LEFT:
                    Movement = 2;
                    break;
                case RIGHT:
                    Movement = 3;
                    break;
                }
            }
        }
        
        ScreenClear(GameMap->GetWidth(), GameMap->GetHeight());
        GameMap->draw();
        PlayerCharacter->draw();
        for (auto G : Ghost)
        {
            G->draw();
            G->collision(PlayerCharacter);
        }
        ScreenFlipping();
        
        while (true)
        {
            UpdateTimeCheck = clock() - Timer;
            if (UpdateTimeCheck > UPDATE_SECOND * 1000)
            {
                if(PlayerCharacter->CheckPowered())
                {
                    PowerfulStateCheck += UpdateTimeCheck;
                    if(PowerfulStateCheck > POWERFUL_STATE_SECOND * 700)
                    {
                        PowerOffBegin = true;
                    }
                    if (PowerfulStateCheck > POWERFUL_STATE_SECOND * 1000)
                    {
                        PowerfulStateCheck = 0;
                        PlayerCharacter->SetPowered(false);
                    }
                }
            
                if(!BeginPlay)
                {
                    ActivateGhostTimeCheck += UpdateTimeCheck;
                    if(ActivateGhostTimeCheck > ACTIVATE_GHOST_SECOND * 1000)
                    {
                        ActivateGhostTimeCheck = 0;
                        BeginPlay = true;
                        //TODO: 맵에서 고스트 박스 풀어주기
                        GameMap->OpenBox();
                    }
                }
                
                UpdateTimeCheck = 0;
                GhostUpdateStack++;
                break;
            }
        }

        ScreenClear();
        
        // 입력 받은 방향으로 계속 이동
        PlayerCharacter->Update(Movement, PowerOffBegin);
        if(GhostUpdateStack > 1)
        {
            for (auto G : Ghost)
            {
                G->Update(PlayerCharacter, Timer);
            }
            GhostUpdateStack = 0;
        }
        //Ghost[0]->Update(PlayerCharacter);
        if(GameMap->Update(PlayerCharacter))
        {
            ScreenClear();
            ScreenRelease();
            GameClear = true;
            break;
        }
    }
    if(GameClear)
    {
        cout << " ※※※ PRESS ANY KEY TO EXIT ※※※ \n";
        cout << "   ※※※ !! GAME CLEAR !! ※※※ \n";
        cout << "   ※※※ !! GAME CLEAR !! ※※※ \n";
        cout << "   ※※※ !! GAME CLEAR !! ※※※ \n";
        cout << " ※※※ PRESS ANY KEY TO EXIT ※※※ \n";
    }
    else
    {
        cout << "   ※※※ !! PLAYER DEAD !! ※※※ \n";
        cout << " ※※※ PRESS ANY KEY TO EXIT ※※※ \n";
    }
    while (true)
    {
        int PressKey = 0;
        if (_kbhit())
        {
            if (_getch() == 224)
            {
                return;
            }
        }
    }
}
