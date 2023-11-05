#include "MainMap.h"

#include <iostream>

#include "GameObject.h"
#include "Player.h"

MainMap::MainMap()
{
	MapInfo = nullptr;
	VisitInfo = nullptr;
	MapWeightInfo = nullptr;
	Closed = true;
	initMap();
}

void MainMap::initMap()
{
	MapWidth = GameMapWidth;
	MapHeight = GameMapHeight;
	MapInfo = new GameObject * [MapHeight];
	VisitInfo = new bool * [MapHeight];
	MapWeightInfo = new int * [MapHeight];
	
	for (int h = 0; h < MapHeight; h++)
	{
		MapInfo[h] = new GameObject[MapWidth];
		VisitInfo[h] = new bool[MapWidth];
		MapWeightInfo[h] = new int[MapWidth];
		for (int w = 0; w < MapWidth; w++)
		{
			MapInfo[h][w] = GameObject(h, w, const_cast<wchar_t*>(L"■"));
			VisitInfo[h][w] = true;
			MapWeightInfo[h][w] = 99;
		}
	}
	
	// 맵 찍기 반복 작업
	{
		for (int h = 0; h < MapHeight; h++)
		{
			if(h == 0 || (h < MapHeight / 2 + 2 && h > MapHeight / 2 - 2) || h == MapHeight - 1)
			{
				continue;
			}
		
			MapInfo[h][1].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 2].SetImg(const_cast<wchar_t*>(L"·"));
		}

		for (int h = 0; h < MapHeight; h++)
		{
			if(h == 0 || (h < 5 && h > 1) || (h < 10 && h > 5) || (h < 14 && h > 10) || (h < 19 && h > 14) || (h < 23 && h > 19) || h == MapHeight - 1)
			{
				continue;
			}
		
			MapInfo[h][2].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][3].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 3].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 4].SetImg(const_cast<wchar_t*>(L"·"));
		}

		for (int h = 0; h < MapHeight; h++)
		{
			if(h == 0 || h == MapHeight - 1)
			{
				continue;
			}
		
			MapInfo[h][4].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 5].SetImg(const_cast<wchar_t*>(L"·"));
		}

		for (int h = 0; h < MapHeight; h++)
		{
			if(h == 0 || (h < 5 && h > 1) || (h < 9 && h > 5) || (h < 15 && h > 9) || (h < 19 && h > 15) || (h < 23 && h > 19) || h == MapHeight - 1)
			{
				continue;
			}
		
			MapInfo[h][5].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][6].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 6].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 7].SetImg(const_cast<wchar_t*>(L"·"));
		}

		for (int h = 0; h < MapHeight; h++)
		{
			if(h == 0 || (h < 15 && h > 9) || h == MapHeight - 1)
			{
				continue;
			}
		
			MapInfo[h][7].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 8].SetImg(const_cast<wchar_t*>(L"·"));
		}

		for (int h = 0; h < MapHeight; h++)
		{
			if(h < 3 || (h < 9 && h > 3) || (h < MapHeight - 4 && h > 15) || h > MapHeight - 4)
			{
				continue;
			}
		
			MapInfo[h][8].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 9].SetImg(const_cast<wchar_t*>(L"·"));
		}

		for (int h = 0; h < MapHeight; h++)
		{
			if(h != 3 && h != 9 && h != 15 && h != MapHeight - 4)
			{
				continue;
			}
		
			MapInfo[h][9].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 10].SetImg(const_cast<wchar_t*>(L"·"));
		}

		for (int h = 0; h < MapHeight; h++)
		{
			if(h < 3 || h > MapHeight - 4)
			{
				continue;
			}
		
			MapInfo[h][10].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 11].SetImg(const_cast<wchar_t*>(L"·"));
		}

		for (int h = 0; h < MapHeight; h++)
		{
			if(h != 6 && h != 18)
			{
				continue;
			}
		
			MapInfo[h][11].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][12].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][13].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 12].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 13].SetImg(const_cast<wchar_t*>(L"·"));
			MapInfo[h][MapWidth - 14].SetImg(const_cast<wchar_t*>(L"·"));
		}
		
		for (int h = 0; h < MapHeight; h++)
		{
			if(h < 18 && h > 6)
			{
				continue;
			}
		
			MapInfo[h][14].SetImg(const_cast<wchar_t*>(L"·"));
		}

		for (int w = 11; w < 13; w++)
		{
			// MapInfo[12][w].SetImg(const_cast<wchar_t*>(L" "));
		}
		
		for (int h = 11; h < 14; h++)
		{
			for (int w = 13; w < 16; w++)
			{
				MapInfo[h][w].SetImg(const_cast<wchar_t*>(L" "));
			}
		}

		for (int h = 11; h < 14; h++)
		{
			for (int w = MapWidth - 3; w < MapWidth - 1; w++)
			{
				MapInfo[h][w].SetImg(const_cast<wchar_t*>(L" "));
			}
		}
		
		// 벽 아닌 곳만 방문 가능하게 false 처리
		ResetInfo();
	}
}

bool MainMap::Update(GameObject* other)
{
	Player* PlayerCharacter = static_cast<Player*>(other);
	if(PlayerCharacter && MapInfo[other->GetX()][other->GetY()].GetImg() == const_cast<wchar_t*>(L"·"))
	{
		MapInfo[other->GetX()][other->GetY()].SetImg(const_cast<wchar_t*>(L" "));
	}
	else if(PlayerCharacter && MapInfo[other->GetX()][other->GetY()].GetImg() == const_cast<wchar_t*>(L"◎"))
	{
		MapInfo[other->GetX()][other->GetY()].SetImg(const_cast<wchar_t*>(L" "));
		PlayerCharacter->SetPowered(true);
	}
	return false;
}

void MainMap::draw()
{
	for (int h = 0; h < MapHeight; h++)
	{
		for (int w = 0; w < MapWidth; w++)
		{
			if(MapInfo[h][w].GetImg() == const_cast<wchar_t*>(L"·"))
			{
				SetColor(YELLOW);
			}
			else
			{
				if(Closed && (h > GameMapHeight / 2 - 3 && h < GameMapHeight / 2 + 3) && (w > GameMapWidth / 2 - 3 && w < GameMapWidth / 2 + 3))
				{
					SetColor(WHITE);
				}
				else
				{
					SetColor(BLUE);
				}
			}
			MapInfo[h][w].draw();
		}
	}
}

void MainMap::ResetInfo()
{
	for (int h = 0; h < MapHeight ; h++)
	{
		for (int w = 0; w < MapWidth; w++)
		{
			if(MapInfo[h][w].GetImg() != const_cast<wchar_t*>(L"■"))
			{
				VisitInfo[h][w] = false;
			}
			MapWeightInfo[h][w] = 99;
		}
	}
}

void MainMap::OpenBox()
{
	for (int w = 11; w < 13; w++)
	{
		MapInfo[12][w].SetImg(const_cast<wchar_t*>(L" "));
	}
	Closed = false;
}

MainMap::~MainMap()
{
	for (int j = 0; j < MapHeight; j++)
	{
		delete[] MapInfo[j];
	}
	delete MapInfo;
}
