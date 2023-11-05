#pragma once

#include <Windows.h>
#include "GameObject.h"
class GameObject;

static int GameMapWidth = 29;
static int GameMapHeight = 25;

class MainMap
{
public:
	MainMap();
	~MainMap();
	void initMap();
	bool Update(GameObject* other);
	void draw();
	void ResetInfo();
	void OpenBox();

	FORCEINLINE int GetWidth() { return MapWidth; }
	FORCEINLINE int GetHeight() { return MapHeight; }
	
	FORCEINLINE wchar_t* GetMapImg(int x, int y) { return MapInfo[x][y].GetImg(); }
	FORCEINLINE void SetMapImg(int x, int y, wchar_t* NewImg) { MapInfo[x][y].SetImg(NewImg); }
	
	FORCEINLINE void SetWeightInfo(int x, int y, int val) { MapWeightInfo[x][y] = val; }
	FORCEINLINE int GetWeightInfo(int x, int y) { return MapWeightInfo[x][y]; }
	
	FORCEINLINE void SetVisitInfo(int x, int y, bool val) { VisitInfo[x][y] = val; }
	FORCEINLINE bool GetVisitInfo(int x, int y) { return VisitInfo[x][y]; }

	FORCEINLINE bool CheckClosed() const { return Closed; }
private:
	int MapWidth;
	int MapHeight;
	GameObject** MapInfo;
	int** MapWeightInfo;
	bool** VisitInfo;

	bool Closed;
	bool CookieRemain;
};
