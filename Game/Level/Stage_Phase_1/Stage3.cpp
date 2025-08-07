#pragma once
#include "Level/GameLevel.h"
#include "Actor/Player.h"
#include "Actor/ActorWall_Width.h"
#include "Actor/MultiLine_Actor.h"
#include "Actor/BreathActor.h"
#include "Actor/Monster.h"
#include "UI/Speech_UI.h"
#include "Engine.h"
#include "Actor/Actor.h"


void GameLevel::Stage3_1(float DeltaTime)
{
	TStage_3_1.Tick(DeltaTime);

	if (!TStage_3_1.IsTimeOut())
	{
		return;
	}

	if (TStage_3_1.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Speech_UI* speechUI = actor->As<Speech_UI>();
			if (speechUI != nullptr)
			{
				speechUI->SayTalking(
					"우린 시공간의\n연속성에\n막대한 변칙이\n있다는걸 발견했어",
					Vector2(3, 1), 20, true, "SansTalking");
			}
		}
	}

	TStage_3_2.Reset();
}

void GameLevel::Stage3_2(float DeltaTime)
{
	TStage_3_2.Tick(DeltaTime);

	if (!TStage_3_2.IsTimeOut())
	{
		return;
	}

	if (TStage_3_2.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Speech_UI* speechUI = actor->As<Speech_UI>();
			if (speechUI != nullptr)
			{
				speechUI->SayTalking(
					"시공간이 좌충우돌\n움직이고\n다시 시작하고...",
					Vector2(3, 1), 20, true, "SansTalking");
			}
		}
	}
	TStage_3_3.Reset();
}

void GameLevel::Stage3_3(float DeltaTime)
{
	TStage_3_3.Tick(DeltaTime);

	if (!TStage_3_3.IsTimeOut())
	{
		return;
	}

	if (TStage_3_3.Update(DeltaTime))
	{
		TurnStart();
	}
	TStage_3_4.Reset();
}

void GameLevel::Stage3_4(float DeltaTime)
{
	TStage_3_4.Tick(DeltaTime);

	if (!TStage_3_4.IsTimeOut())
	{
		return;
	}


	//AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt",
	//	Color::SkyBlue, Vector2(51, 18), "BlueBoneLeft"));
	//AddActor(new MultiLine_Actor("../Assets/Actor/bone_copy.txt",
	//	Color::SkyBlue, Vector2(41, 17), "BlueBoneRight"));
	AddActor(new MultiLine_Actor("../Assets/Actor/Stage3/bone_stage3_mini.txt",
		Color::White, Vector2(74, 22), "Left"));

	//Sleep(1000);

}


