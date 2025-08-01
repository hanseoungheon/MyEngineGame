#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

Actor::Actor(const char* image, Color color, const Vector2& position)
{
    //액터 생성자로 받은 문자열의 길이를 width 정수형에 저장
    width = (int)strlen(image);

    //액터를 만들기 위한 메모리 할당
    this->image = new char[width + 1];

    //생성자로 받은 문자열을 액터의 이미지 변수에 저장
    strcpy_s(this->image, width + 1, image);
}

Actor::~Actor()
{
    //메모리 해제
    SafeDeleteArray(image);
}

void Actor::BeginPlay()
{
    hasBeganPlay = true;
}

void Actor::Tick(float DeltaTime)
{
    //기본형이라 없음
}

void Actor::Render()
{
    //커서 이동
    Utils::SetConsolePosition(actorPosition);

    //색상 설정
    Utils::SetConsoleTextColor(color);

    //그리기
    std::cout << image;
}

void Actor::SetPosition(const Vector2& newPosition)
{
    //예외 처리 (화면 벗어났는지 확인.)
}

Vector2 Actor::GetActorPosition() const
{
    return actorPosition;
}

int Actor::GetWidth() const
{
    return width;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
    this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
    owner = newOwner;
}

Level* Actor::GetOwner()
{
    return owner;
}

bool Actor::TestIntersect(const Actor* const other)
{
    //이 액터의 x좌표 정보
    int xMin = actorPosition.x;
    int xMax = actorPosition.x + width - 1;

    //이 액터의 y 좌표 정보


    //충돌비교할 다른 액터의 x좌표 정보
    int other_xMin = other->actorPosition.x;
    int other_xMax = other->actorPosition.x + other->width - 1;

    //다른 액터의 y좌표 정보

    //안겹치는 조건 확인
    if (other_xMin > xMax)
    {
        return false;
    }

    if (other_xMax < xMin)
    {
        return false;
    }

    return actorPosition.y == other->actorPosition.y;
}

void Actor::Destroy()
{
    isExpired = true;
    owner->
}

void Actor::QuitGame()
{
}
