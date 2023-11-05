#pragma once

#include "GameObject.h"
class MainMap;

static int PlayerPosX;
static int PlayerPosY;

class Player : public GameObject
{
public:
	Player() { }
	~Player() { }
	
	void InitPlayer(int x, int y, MainMap* GameMap);
	void Update(int m, bool p);
	void draw() override;

	FORCEINLINE void SetDead(bool Value) { IsDead = Value; }
	FORCEINLINE bool CheckDead() { return IsDead; }

	FORCEINLINE void SetPowered(bool Value) { IsPowerful = Value; PowerLow = !Value; }
	FORCEINLINE bool CheckPowered() { return IsPowerful; }

	FORCEINLINE int GetMoveDirection() const { return MoveDirection; }

	FORCEINLINE void AddCookieStack() { CookieStack++; }
private:
	MainMap* GameMap;

	int MoveDirection;
	int CookieStack;
	bool IsDead;
	bool IsPowerful;
	bool PowerLow;
};
