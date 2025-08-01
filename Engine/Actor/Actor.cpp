#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

Actor::Actor(const char* image, Color color, const Vector2& position)
{
    //���� �����ڷ� ���� ���ڿ��� ���̸� width �������� ����
    width = (int)strlen(image);

    //���͸� ����� ���� �޸� �Ҵ�
    this->image = new char[width + 1];

    //�����ڷ� ���� ���ڿ��� ������ �̹��� ������ ����
    strcpy_s(this->image, width + 1, image);
}

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
    //Ŀ�� �̵�
    Utils::SetConsolePosition(actorPosition);

    //���� ����
    Utils::SetConsoleTextColor(color);

    //�׸���
    std::cout << image;
}

void Actor::SetPosition(const Vector2& newPosition)
{
    //���� ó�� (ȭ�� ������� Ȯ��.)
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

void Actor::Destroy()
{
    isExpired = true;
    owner->
}

void Actor::QuitGame()
{
}
