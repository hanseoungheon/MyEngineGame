#pragma once
#include "Core.h"
#include <vector>
#include "RTTI.h"

class Actor;

class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level,RTTI)
public:
	Level();

	virtual ~Level();

	void AddActor(Actor* newActor);

	void DestoryActor(Actor* destroyActor);

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
	virtual void Render();

	//�߰� �� ���� ��û�� ���͸� ó���ϴ� �Լ�
	void ProcessAddAndDestroyActors();

private:
	void SortActorsBySortingOrder();

protected:
	//������ ��ġ�� ��� ���͸� �����ϴ� �迭
	std::vector<Actor*> actors;

	//�߰� ��û�� ���͸� �����ϴ� �迭
	std::vector<Actor*> addRequestActors;

	//���� ��û�� ���͸� �����ϴ� �迭
	std::vector<Actor*> destroyRequestActors;
};