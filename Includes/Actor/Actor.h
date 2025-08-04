#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Core.h"
#include <Windows.h>
#include "RTTI.h"

class Level;

class Engine_API Actor : public RTTI
{
	friend class Level;

	RTTI_DECLARATIONS(Actor, RTTI)


public:
	Actor(const char* image = " ", Color color = Color::White,
		const Vector2& position = Vector2::Zero,bool IsUI = false);

	virtual ~Actor();

	//��ü �����ֱ⿡ 1��(������)�� �����
	virtual void BeginPlay();

	//�� �����Ӹ��� ȣ���(�ݺ��� �۾� Update/Step ��)
	virtual void Tick(float DeltaTime);

	//cmdâ�� ���ڸ� ����ؼ� �׸��� �Լ�
	virtual void Render();

	//BeginPlay ȣ�⿩�� Ȯ��
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	void SetPosition(const Vector2& newPosition);
	Vector2 GetActorPosition() const;

	//���ڿ� ���� ��ȯ
	int GetWidth() const;

	//Sorting Order ����
	void SetSortingOrder(unsigned int sortingOrder);

	//���ʽ� ����
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	//���� ��ȯ
	Color GetColor() const;

	//���� ����
	void SetColor(const Color color);

	//�浹 Ȯ�� ��û �Լ� (AABB ����)
	bool TestIntersect(const Actor* const other);

	//��ü ������Ű�� �Լ�
	void Destroy();

	//���� ���� ��û
	void QuitGame();

protected:
	//��ü�� ��ġ
	Vector2 actorPosition;
	
	//�׸� �ؽ�Ʈ
	char* image = nullptr;

	//���ڿ� ����
	int width = 0;

	//���ڿ� ����
	int height = 0;

	//�ؽ�Ʈ ����
	Color color; 

	//BeginPlay ȣ���� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;

	//���� ���� ����
	unsigned int sortingOrder = 0;

	//���Ͱ� Ȱ�� ����
	bool isActive = true;

	//���� ��û�ƴ��� �˷��ִ� ����
	bool isExpired = false;

	//��ü�� ������ ����
	Level* owner = nullptr;

	const int LeftSide = 40;

	//UI���� �� ũ�⿡ ���� x
	bool IsUI = false;

	bool IsVisible;
};