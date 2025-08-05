#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

Actor::Actor(const char* image, Color color, const Vector2& position,
    bool IsUI)
    :color(color), actorPosition(position),IsUI(IsUI)
{
    //�������� ���ڿ����� �����ϱ�
    if (strlen(image) == 1)
    {
        SingleImage = image[0];
        image = nullptr;
    }

    if (image != nullptr)
    {
        //���� �����ڷ� ���� ���ڿ��� ���̸� width �������� ����
        width = (int)strlen(image);

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
}

void Actor::Render()
{
    if (IsVisible == true)
    {
        //�׸���
        if (image != nullptr)
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
    //���� ó�� (ȭ�� ������� Ȯ��.)

    if (!IsUI)
    {
        //������ ���� �����ڸ��� ȭ�� ������ �������
        if (newPosition.x < LeftSide)
            return;

        //������ ������ �����ڸ��� ȭ�� �������� �������
        if (newPosition.x + width - 1 > Engine::Get().Width())
            return;

        //������ ���� �����ڸ��� ȭ�� ������ �������
        if (newPosition.y < 16)
            return;

        //���Ͱ� ȭ�� �Ʒ��� �������
        if (newPosition.y - 1 > Engine::Get().Height())
            return;

        if (actorPosition == newPosition)
            return;


        //���� ��ġ Ȯ��
        Vector2 direction = newPosition - actorPosition;
        // �� ��ġ - ���� ��ġ = ���⺤��

        if (image != nullptr)
        {
            //���ڿ��̸� ���� �����ؾߵǿ�
            actorPosition.x = (direction.x >= 0) ? 
                actorPosition.x : actorPosition.x
                + width - 1;
        }
        else
        {
            //�����ϰ�쿡�� ���� �����ϸ� �ȵſ�
            actorPosition.x = (direction.x >= 0) ? 
                actorPosition.x : actorPosition.x;
        }
    

        //Ŀ�� �̵�
        Utils::SetConsolePosition(actorPosition);

        //���ڿ� ���� ����ؼ� ������ġ Ȯ��
        std::cout << ' ';

        actorPosition = newPosition;
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

        return actorPosition.y == other->actorPosition.y;
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
