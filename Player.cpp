#include "Player.h"
#include "MainMap.h"

void Player::InitPlayer(int x, int y, MainMap* GameMap)
{
	Pos.first = x;
	Pos.second = y;
	Object_Img = const_cast<wchar_t*>(L"▲");
	IsDead = false;
	IsPowerful = false;
	this->GameMap = GameMap;
	MoveDirection = 0;
	CookieStack = 0;
}

void Player::Update(int m, bool p)
{
	switch (m)
	{
	case 0: //UP
		if(Pos.second > 1 && GameMap->GetMapImg(Pos.first, Pos.second - 1) != const_cast<wchar_t*>(L"■"))
		{
			Pos.second--;
			Object_Img = const_cast<wchar_t*>(L"▲");
			MoveDirection = 0;
		}
		break;
	case 1: //DOWN
		if(Pos.second < GameMapWidth - 1 && GameMap->GetMapImg(Pos.first, Pos.second + 1) != const_cast<wchar_t*>(L"■"))
		{
			Pos.second++;
			Object_Img = const_cast<wchar_t*>(L"▼");
			MoveDirection = 1;
		}
		break;
	case 2: //LEFT
		if(!Pos.first)
		{
			Pos.first = GameMapHeight - 1;
			Object_Img = const_cast<wchar_t*>(L"◀");
			MoveDirection = 2;
			break;
		}
		if(GameMap->GetMapImg(Pos.first - 1, Pos.second) != const_cast<wchar_t*>(L"■"))
		{
			Pos.first--;
			Object_Img = const_cast<wchar_t*>(L"◀");
			MoveDirection = 2;
		}
		break;
	case 3: //RIGHT
		if(Pos.first == GameMapHeight - 1)
		{
			Pos.first = 0;
			Object_Img = const_cast<wchar_t*>(L"▶");
			MoveDirection = 3;
			break;
		}
		if(Pos.first < GameMapHeight - 1 && GameMap->GetMapImg(Pos.first + 1, Pos.second) != const_cast<wchar_t*>(L"■"))
		{
			Pos.first++;
			Object_Img = const_cast<wchar_t*>(L"▶");
			MoveDirection = 3;
		}
		break;
	}
	if(p)
	{
		PowerLow = true;
	}
	if(CookieStack >= 20 && !CheckPowered())
	{
		SetPowered(true);
		CookieStack = 0;
	}
	
	PlayerPosX = Pos.first;
	PlayerPosY = Pos.second;
}

void Player::draw()
{
	if(IsPowerful)
	{
		if(PowerLow)
		{
			SetColor(DARKGRAY);
		}
		else
		{
			SetColor(WHITE);
		}
	}
	else
	{
		SetColor(BROWN);
	}
	GameObject::draw();
}
