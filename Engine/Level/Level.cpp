#include "Level.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"
#include <iostream>

Level::Level()
{

}

Level::~Level()
{
	for (Actor* actor : actors)
	{
		//액터배열을 한번씩 스캔한 다음에 찾은 액터들 삭제
		SafeDelete(actor);
	}

	actors.clear();
}

void Level::BeginPlay()
{
	for (Actor* actor : actors)
	{
		//반복문을 사용해 actors배열내부 모든 액터들을 스캔
		// 그 후 각 액터객체들의 BeginPlay함수 실행시켜줌
		//액터 처리 여부 확인
		//삭제 요청이 들어온 상태거나, 비활성화 상태면 건너뜀

		if (!actor->isActive || actor->isExpired)
			continue;

		//이미 호출된 액터객체는 건너뜀.
		if (actor->HasBeganPlay())
			continue;

		actor->BeginPlay();
	}
}

void Level::Tick(float DeltaTime)
{
	//반복문을 사용해 실시간으로 액터배열에 있는 액터들 탐색
	//그후 각 액터객체들의 Tick함수 실행시켜줌
	for (Actor* actor : actors)
	{
		//삭제 요청이 들어온상태거나, 비활성화상태면 건너뜀
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->Tick(DeltaTime);
	}
}

void Level::AddActor(Actor* newActor)
{
	//예외처리(중복여부 확인) 필수!

	//push_back, emplace_back => vector배열 맨 뒤에 새로운 요소를 추가하는 메소드
	//push_back = && 이중참조, emplace_back = & 참조
	//즉 push_back은 객체를 집어넣는 메소드
	//emplace_back은 c+11에 추가된 메소드로 템플릿을 사용해 객체 생성에 필요한
	//인자만 받은 후 함수내에서 객체를 생성해서 삽입하는 방식

	addRequestActors.emplace_back(newActor);
	//addRequestActors.push_back(newActor);
}

void Level::Render()
{
	//그리기 전에 정렬 순서기준으로 재배치(정렬)
	SortActorsBySortingOrder();

	//Actor포인터를 사용해서 백터액터 배열을 탐색
	for (Actor* actor : actors)
	{
		Actor* searchedActor = nullptr;
		//삭제 요청이 들어온 상태거나, 비활성화 상태면 건너뜀
		if (!actor->isActive || actor->isExpired)
			continue;

		//검사(같은 위치에 정렬순서 높은 액터가 있는지 확인)
		for (Actor* const otherActor : actors)
		{
			if (actor == otherActor)
				continue;

			if (actor->GetActorPosition() == otherActor->GetActorPosition())
			{
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					searchedActor = otherActor;
					break;
				}
			}
		}

		//어떤 액터와 같은 위치에 정렬 순서가 더 높은 액터가 있으면,
		//그리지 않고 건너뛰기
		if (searchedActor)
		{
			continue;
		}

		//드로우콜
		actor->Render();
	}
}

void Level::DestoryActor(Actor* destroyedActor)
{
	//삭제 대기배열에 추가
	destroyRequestActors.emplace_back(destroyedActor);
}

void Level::ProcessAddAndDestroyActors()
{
	//1. auto iterator를 이용한 반복문 삭제처리
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		//for문을 이용해서 삭제 요청된 액터인지 확인 후에 배열에서 삭제처리
		//포인터를 가르키는 포인터 *iterator = Actor* <더블포인터>

		if ((*iterator)->isExpired == true)
		{
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	//destroyRequset 배열을 순회하면서 액터 지우기
	for (auto* actor : destroyRequestActors)
	{
		//액터가 그려져있으면 지우기
		//Utils::SetConsolePosition(actor->actorPosition);

		if (actor->CheckString == IsString::STR_FALSE)
		{
			Utils::SetConsolePosition(actor->actorPosition);
			for (int ix = 0; ix < actor->width; ++ix)
			{
				// " "로 바꿔서 지워버리기.
				std::cout << " ";
			}

		}
		else if(actor->CheckString == IsString::STR_TRUE)
		{
			for (int ix = 0; ix < actor->height; ++ix)
			{
				Utils::SetConsolePosition(Vector2(
					actor->actorPosition.x,
					actor->actorPosition.y + ix
				));
				for (int jx = 0; jx < actor->width; ++jx)
				{
					// " "로 바꿔서 지워버리기.
					std::cout << " ";
				}
			}
		}

		SafeDelete(actor);
	}

	destroyRequestActors.clear();

	for (Actor* const actor : addRequestActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	addRequestActors.clear();
}

//액터들 정렬시키는 함수
void Level::SortActorsBySortingOrder()
{
	for (int ix = 0; ix < (int)actors.size(); ++ix)
	{
		for (int jx = 0; jx < (int)actors.size() - 1; ++jx)
		{
			if (actors[jx]->sortingOrder < actors[jx + 1]->sortingOrder)
				std::swap(actors[jx], actors[jx + 1]);
		}
	}
}