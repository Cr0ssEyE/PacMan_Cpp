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
}

void Player::Update(int p)
{
	switch (p)
	{
	case 0: //UP
		if(Pos.second > 1 && GameMap->GetMapImg(Pos.first, Pos.second - 1) != const_cast<wchar_t*>(L"■"))
		{
			Pos.second--;
			Object_Img = const_cast<wchar_t*>(L"▲");
		}
		break;
	case 1: //DOWN
		if(Pos.second < GameMapWidth - 1 && GameMap->GetMapImg(Pos.first, Pos.second + 1) != const_cast<wchar_t*>(L"■"))
		{
			Pos.second++;
			Object_Img = const_cast<wchar_t*>(L"▼");
		}
		break;
	case 2: //LEFT
		if(!Pos.first)
		{
			Pos.first = GameMapHeight - 1;
			Object_Img = const_cast<wchar_t*>(L"◀");
			break;
		}
		if(GameMap->GetMapImg(Pos.first - 1, Pos.second) != const_cast<wchar_t*>(L"■"))
		{
			Pos.first--;
			Object_Img = const_cast<wchar_t*>(L"◀");
		}
		break;
	case 3: //RIGHT
		if(Pos.first == GameMapHeight - 1)
		{
			Pos.first = 0;
			Object_Img = const_cast<wchar_t*>(L"▶");
			break;
		}
		if(Pos.first < GameMapHeight - 1 && GameMap->GetMapImg(Pos.first + 1, Pos.second) != const_cast<wchar_t*>(L"■"))
		{
			Pos.first++;
			Object_Img = const_cast<wchar_t*>(L"▶");
		}
		break;
	}
	PlayerPosX = Pos.first;
	PlayerPosY = Pos.second;
}

void Player::draw()
{
	if(IsPowerful)
	{
		SetColor(WHITE);
	}
	else
	{
		SetColor(BROWN);
	}
	GameObject::draw();
}
