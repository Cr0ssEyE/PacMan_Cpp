#pragma once
#include <Windows.h>
#include <vector>
#include "util.h"

using namespace std;

class MainMap;

class GameObject
{
public:
	GameObject();
	GameObject(int x, int y, wchar_t* img);
	~GameObject();
	
	FORCEINLINE int GetX() { return Pos.first; }
	FORCEINLINE int GetY() { return Pos.second; }
	FORCEINLINE wchar_t* GetImg() { return Object_Img; }
	
	FORCEINLINE void SetPos(int x, int y) { Pos.first = x; Pos.second = y; }
	FORCEINLINE void SetImg(wchar_t* img) { Object_Img = img; }

	virtual bool collision(GameObject* other);
	virtual void Update(int p);

	virtual void draw();

protected:
	pair<int, int> Pos;
	wchar_t* Object_Img;
};

