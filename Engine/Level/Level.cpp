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
		//���͹迭�� �ѹ��� ��ĵ�� ������ ã�� ���͵� ����
		SafeDelete(actor);
	}

	actors.clear();
}

void Level::BeginPlay()
{
	for (Actor* actor : actors)
	{
		//�ݺ����� ����� actors�迭���� ��� ���͵��� ��ĵ
		// �� �� �� ���Ͱ�ü���� BeginPlay�Լ� ���������
		//���� ó�� ���� Ȯ��
		//���� ��û�� ���� ���°ų�, ��Ȱ��ȭ ���¸� �ǳʶ�

		if (!actor->isActive || actor->isExpired)
			continue;

		//�̹� ȣ��� ���Ͱ�ü�� �ǳʶ�.
		if (actor->HasBeganPlay())
			continue;

		actor->BeginPlay();
	}
}

void Level::Tick(float DeltaTime)
{
	//�ݺ����� ����� �ǽð����� ���͹迭�� �ִ� ���͵� Ž��
	//���� �� ���Ͱ�ü���� Tick�Լ� ���������
	for (Actor* actor : actors)
	{
		//���� ��û�� ���»��°ų�, ��Ȱ��ȭ���¸� �ǳʶ�
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->Tick(DeltaTime);
	}
}

void Level::AddActor(Actor* newActor)
{
	//����ó��(�ߺ����� Ȯ��) �ʼ�!

	//push_back, emplace_back => vector�迭 �� �ڿ� ���ο� ��Ҹ� �߰��ϴ� �޼ҵ�
	//push_back = && ��������, emplace_back = & ����
	//�� push_back�� ��ü�� ����ִ� �޼ҵ�
	//emplace_back�� c+11�� �߰��� �޼ҵ�� ���ø��� ����� ��ü ������ �ʿ���
	//���ڸ� ���� �� �Լ������� ��ü�� �����ؼ� �����ϴ� ���

	addRequestActors.emplace_back(newActor);
	//addRequestActors.push_back(newActor);
}

void Level::Render()
{
	//�׸��� ���� ���� ������������ ���ġ(����)
	SortActorsBySortingOrder();

	//Actor�����͸� ����ؼ� ���;��� �迭�� Ž��
	for (Actor* actor : actors)
	{
		Actor* searchedActor = nullptr;
		//���� ��û�� ���� ���°ų�, ��Ȱ��ȭ ���¸� �ǳʶ�
		if (!actor->isActive || actor->isExpired)
			continue;

		//�˻�(���� ��ġ�� ���ļ��� ���� ���Ͱ� �ִ��� Ȯ��)
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

		//� ���Ϳ� ���� ��ġ�� ���� ������ �� ���� ���Ͱ� ������,
		//�׸��� �ʰ� �ǳʶٱ�
		if (searchedActor)
		{
			continue;
		}

		//��ο���
		actor->Render();
	}
}

void Level::DestoryActor(Actor* destroyedActor)
{
	//���� ���迭�� �߰�
	destroyRequestActors.emplace_back(destroyedActor);
}

void Level::ProcessAddAndDestroyActors()
{
	//1. auto iterator�� �̿��� �ݺ��� ����ó��
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		//for���� �̿��ؼ� ���� ��û�� �������� Ȯ�� �Ŀ� �迭���� ����ó��
		//�����͸� ����Ű�� ������ *iterator = Actor* <����������>

		if ((*iterator)->isExpired == true)
		{
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	//destroyRequset �迭�� ��ȸ�ϸ鼭 ���� �����
	for (auto* actor : destroyRequestActors)
	{
		//���Ͱ� �׷��������� �����
		//Utils::SetConsolePosition(actor->actorPosition);

		if (actor->CheckString == IsString::STR_FALSE)
		{
			Utils::SetConsolePosition(actor->actorPosition);
			for (int ix = 0; ix < actor->width; ++ix)
			{
				// " "�� �ٲ㼭 ����������.
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
					// " "�� �ٲ㼭 ����������.
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

//���͵� ���Ľ�Ű�� �Լ�
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