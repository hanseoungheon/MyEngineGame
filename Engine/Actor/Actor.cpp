#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

Actor::Actor(const char* image, Color color, const Vector2& position,
    bool IsUI,IsString CheckString)
    :color(color), actorPosition(position),IsUI(IsUI),CheckString(CheckString)
{
    //문자인지 문자열인지 구분하기
    if (strlen(image) == 1 && this->CheckString == IsString::STR_FALSE)
    {
        SingleImage = image[0];
        image = nullptr;

        //기본 높이 및 너비 1 1 부여
        SettingWidthAndHeight(1, 1);

        //width = 1;
        //height = 1;
    }

    if (image != nullptr && this->CheckString == IsString::STR_TRUE)
    {
        //width = (int)strlen(image);
        //height = 1;

        //액터 생성자로 받은 문자열의 길이를 width 정수형에 저장
        //그리고 기본 높이 1 부여
        SettingWidthAndHeight((int)strlen(image), 1);

        //액터를 만들기 위한 메모리 할당
        this->image = new char[width + 1];

        //생성자로 받은 문자열을 액터의 이미지 변수에 저장
        strcpy_s(this->image, width + 1, image);

    }

    IsVisible = true;
}

//Actor::Actor(const Vector2& position, char image
//    ,bool IsUI)
//    : SingleImage(image), color(color), actorPosition(position),
//    IsUI(IsUI)
//{
//    color = Color::White;
//    IsVisible = true;
//}

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
    if (height > 1)
        IsHasHeight = true;
}

void Actor::Render()
{
    if (IsVisible == true)
    {
        //그리기
        if (image != nullptr && this->CheckString == IsString::STR_TRUE)
        {
            //커서 이동
            Utils::SetConsolePosition(actorPosition);

            //색상 설정
            Utils::SetConsoleTextColor(color);

            //만약 문자열로 받았다면 문자열 출력
            std::cout << image;
        }
        else
        {
            //아니라면 문자 출력
            COORD coord;
            coord.X = (short)actorPosition.x;
            coord.Y = (short)actorPosition.y;

            Utils::SetConsolePosition(coord);

            Utils::SetConsoleTextColor(color);
            
            std::cout << SingleImage;
        }
    }
}

void Actor::SetPosition(const Vector2& newPosition)
{
    //Vector2 oldPosition = actorPosition;
    //예외 처리 (화면 벗어났는지 확인.)

    if (!IsUI)
    {
        //std::cout << "MainTest";
        //액터의 왼쪽 가장자리가 화면 왼쪽을 벗어났는지
        if (CheckString == IsString::STR_FALSE && newPosition.x < LeftSide)
            return;

        //액터의 오른쪽 가장자리가 화면 오른쪽을 벗어났는지
        if (CheckString == IsString::STR_FALSE && 
            newPosition.x + width - 1 > Engine::Get().Width())
            return;

        //액터의 윗쪽 가장자리가 화면 윗쪽을 벗어났는지
        if (CheckString == IsString::STR_FALSE && newPosition.y < UpSide)
            return;

        //액터가 화면 아래를 벗어났는지
        if (CheckString == IsString::STR_FALSE && newPosition.y - 1 > Engine::Get().Height())
            return;

        if (CheckString == IsString::STR_FALSE && actorPosition == newPosition)
            return;


      



        if (CheckString == IsString::STR_FALSE)
        {
            //지울 위치 확인
            Vector2 direction = newPosition - actorPosition;
            //std::cout << direction.x;
            // 갈 위치 - 현재 위치 = 방향벡터


            //문자열이면 길이 적용해야되용
            actorPosition.x = (direction.x >= 0) ?
                actorPosition.x : actorPosition.x + width - 1;
            //커서 이동
            //std::cout << "[SetPosition] CheckString: " << static_cast<int>(CheckString) << "\n";

            Utils::SetConsolePosition(actorPosition);

            //문자열 길이 고려해서 지울위치 확인
            std::cout << ' ';

            actorPosition = newPosition;
        }

        //if (CheckString == IsString::STR_TRUE)
        //{
        //    //std::cout << "BoneTest";
        //    for (int i = 0; i < height; ++i)
        //    {
        //        Utils::SetConsolePosition(Vector2(actorPosition.x, actorPosition.y + i));
        //        for (int j = 0; j <= width; ++j)
        //        {
        //            std::cout << ' ';
        //        }
        //    }
        //}
    }
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

Color Actor::GetColor() const
{
    return color;
}

void Actor::SetColor(const Color color)
{
    this->color = color;
}

bool Actor::TestIntersect(const Actor* const other)
{
    if (!IsUI)
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

        int yMin = actorPosition.y;
        int yMax = actorPosition.y + height - 1;

        int other_yMin = other->actorPosition.y;
        int other_yMax = other->actorPosition.y + other->height - 1;

        if (other_yMin > yMax)
        {
            return false;
        }

        if (other_yMax < yMin)
        {
            return false;
        }

        //return actorPosition.y == other->actorPosition.y;
 


        return true;
    }
}

void Actor::Destroy()
{
    isExpired = true;
    owner->DestoryActor(this);
}

void Actor::QuitGame()
{
    Engine::Get().Quit();
}

void Actor::SettingWidthAndHeight(int width, int height)
{
    this->width = width;
    this->height = height;
}
