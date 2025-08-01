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

	//추가 및 삭제 요청된 액터를 처리하는 함수
	void ProcessAddAndDestroyActors();

private:
	void SortActorsBySortingOrder();

protected:
	//레벨에 배치된 모든 액터를 관리하는 배열
	std::vector<Actor*> actors;

	//추가 요청된 액터를 관리하는 배열
	std::vector<Actor*> addRequestActors;

	//삭제 요청된 액터를 관리하는 배열
	std::vector<Actor*> destroyRequestActors;
};