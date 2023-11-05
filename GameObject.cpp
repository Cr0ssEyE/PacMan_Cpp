#include "GameObject.h"
#include "MainMap.h"

GameObject::GameObject()
{
    Pos.first = 0;
    Pos.second = 0;
    Object_Img = const_cast<wchar_t*>(L" ");
}

GameObject::GameObject(int x, int y, wchar_t* img)
{
    Pos.first = x;
    Pos.second = y;
    Object_Img = img;
}

GameObject::~GameObject()
{
    
}

bool GameObject::collision(GameObject* other)
{
    if (Pos.first == other->GetX() && Pos.second == other->GetY())
    {
        return true;
    }
    return false;
}

void GameObject::Update(int p)
{
    //TODO:: 뭔가 해야 함
}

void GameObject::draw()
{
    ScreenPrint(Pos.first, Pos.second, Object_Img);
}
