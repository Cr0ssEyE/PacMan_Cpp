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

	FORCEINLINE void SetDead(bool Value) { IsDead = Value; }
	FORCEINLINE bool CheckDead() { return IsDead; }

	FORCEINLINE void SetPowered(bool Value) { IsPowerful = Value; }
	FORCEINLINE bool CheckPowered() { return IsPowerful; }
	
	void InitPlayer(int x, int y, MainMap* GameMap);
	void Update(int p) override;
	void draw() override;
	
private:
	MainMap* GameMap;

	bool IsDead;
	bool IsPowerful;
};
