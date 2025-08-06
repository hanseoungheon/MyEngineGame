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
    //�������� ���ڿ����� �����ϱ�
    if (strlen(image) == 1 && this->CheckString == IsString::STR_FALSE)
    {
        SingleImage = image[0];
        image = nullptr;

        //�⺻ ���� �� �ʺ� 1 1 �ο�
        SettingWidthAndHeight(1, 1);

        //width = 1;
        //height = 1;
    }

    if (image != nullptr && this->CheckString == IsString::STR_TRUE)
    {
        //width = (int)strlen(image);
        //height = 1;

        //���� �����ڷ� ���� ���ڿ��� ���̸� width �������� ����
        //�׸��� �⺻ ���� 1 �ο�
        SettingWidthAndHeight((int)strlen(image), 1);

        //���͸� ����� ���� �޸� �Ҵ�
        this->image = new char[width + 1];

        //�����ڷ� ���� ���ڿ��� ������ �̹��� ������ ����
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
    //�޸� ����
    SafeDeleteArray(image);
}

void Actor::BeginPlay()
{
    hasBeganPlay = true;
}

void Actor::Tick(float DeltaTime)
{
    //�⺻���̶� ����
    if (height > 1)
        IsHasHeight = true;
}

void Actor::Render()
{
    if (IsVisible == true)
    {
        //�׸���
        if (image != nullptr && this->CheckString == IsString::STR_TRUE)
        {
            //Ŀ�� �̵�
            Utils::SetConsolePosition(actorPosition);

            //���� ����
            Utils::SetConsoleTextColor(color);

            //���� ���ڿ��� �޾Ҵٸ� ���ڿ� ���
            std::cout << image;
        }
        else
        {
            //�ƴ϶�� ���� ���
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
    //���� ó�� (ȭ�� ������� Ȯ��.)

    if (!IsUI)
    {
        //std::cout << "MainTest";
        //������ ���� �����ڸ��� ȭ�� ������ �������
        if (CheckString == IsString::STR_FALSE && newPosition.x < LeftSide)
            return;

        //������ ������ �����ڸ��� ȭ�� �������� �������
        if (CheckString == IsString::STR_FALSE && 
            newPosition.x + width - 1 > Engine::Get().Width())
            return;

        //������ ���� �����ڸ��� ȭ�� ������ �������
        if (CheckString == IsString::STR_FALSE && newPosition.y < UpSide)
            return;

        //���Ͱ� ȭ�� �Ʒ��� �������
        if (CheckString == IsString::STR_FALSE && newPosition.y - 1 > Engine::Get().Height())
            return;

        if (CheckString == IsString::STR_FALSE && actorPosition == newPosition)
            return;


      



        if (CheckString == IsString::STR_FALSE)
        {
            //���� ��ġ Ȯ��
            Vector2 direction = newPosition - actorPosition;
            //std::cout << direction.x;
            // �� ��ġ - ���� ��ġ = ���⺤��


            //���ڿ��̸� ���� �����ؾߵǿ�
            actorPosition.x = (direction.x >= 0) ?
                actorPosition.x : actorPosition.x + width - 1;
            //Ŀ�� �̵�
            //std::cout << "[SetPosition] CheckString: " << static_cast<int>(CheckString) << "\n";

            Utils::SetConsolePosition(actorPosition);

            //���ڿ� ���� ����ؼ� ������ġ Ȯ��
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
        //�� ������ x��ǥ ����
        int xMin = actorPosition.x;
        int xMax = actorPosition.x + width - 1;


        //�� ������ y ��ǥ ����
        
        //�浹���� �ٸ� ������ x��ǥ ����
        int other_xMin = other->actorPosition.x;
        int other_xMax = other->actorPosition.x + other->width - 1;

        //�ٸ� ������ y��ǥ ����

        //�Ȱ�ġ�� ���� Ȯ�� 
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
