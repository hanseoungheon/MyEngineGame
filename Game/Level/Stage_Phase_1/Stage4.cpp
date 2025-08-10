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

void GameLevel::Stage4_1(float DeltaTime)
{
	TStage_4_1.Tick(DeltaTime);

	if (!TStage_4_1.IsTimeOut())
	{
		return;
	}

	if (TStage_4_1.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Speech_UI* speechUI = actor->As<Speech_UI>();
			if (speechUI != nullptr)
			{
				speechUI->SayTalking(
					"그러다 갑자기\n모든 것이\n끝나버려.",
					Vector2(3, 1), 20, true, "SansTalking");
			}
		}
	}

	TStage_4_2.Reset();
}

void GameLevel::Stage4_2(float DeltaTime)
{
	TStage_4_2.Tick(DeltaTime);

	if (!TStage_4_2.IsTimeOut())
	{
		return;
	}

	if (TStage_4_2.Update(DeltaTime))
	{
		TurnStart();

	}

	TStage_4_3.Reset();
}
void GameLevel::Stage4_3(float DeltaTime)
{
	TStage_4_3.Tick(DeltaTime);

	if (!TStage_4_3.IsTimeOut())
	{
		return;
	}

	if (TStage_4_3.Update(DeltaTime))
	{
		AddActor(new MultiLine_Actor("../Assets/Actor/Stage4/bone_mustJump_Up_4_1.txt",
			Color::White, Vector2(74, 16), "Left"));
		AddActor(new MultiLine_Actor("../Assets/Actor/Stage4/bone_mustJump_Down_4_1.txt",
			Color::White, Vector2(74, 20), "Left"));

		AddActor(new MultiLine_Actor("../Assets/Actor/Stage4/bone_mustJump_Up_4_1.txt",
			Color::White, Vector2(41, 16), "Right"));
		AddActor(new MultiLine_Actor("../Assets/Actor/Stage4/bone_mustJump_Down_4_1.txt",
			Color::White, Vector2(41, 20), "Right"));
	}

	TStage_4_3_1.Reset();
}

void GameLevel::Stage4_3_1(float DeltaTime)
{
	TStage_4_3_1.Tick(DeltaTime);

	if (!TStage_4_3_1.IsTimeOut())
	{
		return;
	}

	if (TStage_4_3_1.Update(DeltaTime))
	{

	}

	TStage_4_4.Reset();
}

void GameLevel::Stage4_4(float DeltaTime)
{
	TStage_4_4.Tick(DeltaTime);

	if (!TStage_4_4.IsTimeOut())
	{
		return;
	}

	AddActor(new MultiLine_Actor("../Assets/Actor/bone_mustJump_Up.txt",
		Color::White, Vector2(74, 16), "Left"));
	AddActor(new MultiLine_Actor("../Assets/Actor/bone_mustJump_Down.txt",
		Color::White, Vector2(74, 22), "Left"));

	AddActor(new MultiLine_Actor("../Assets/Actor/bone_mustJump_Up.txt",
		Color::White, Vector2(41, 16), "Right"));
	AddActor(new MultiLine_Actor("../Assets/Actor/bone_mustJump_Down.txt",
		Color::White, Vector2(41, 22), "Right"));

	TimerEndCount++;

	if (TimerEndCount < 3)
	{
		TStage_4_4.Reset();
	}
	else
	{
		TimerEndCount = 0;
		TStage_4_5.Reset();
	}
}

void GameLevel::Stage4_5(float DeltaTime)
{
	TStage_4_5.Tick(DeltaTime);

	if (!TStage_4_5.IsTimeOut())
	{
		return;
	}

	if (TStage_4_5.Update(DeltaTime))
	{
		AddActor(new MultiLine_Actor("../Assets/Actor/Stage4/bone_mustJump_Up_4_2.txt",
			Color::White, Vector2(74, 16), "Left"));
		AddActor(new MultiLine_Actor("../Assets/Actor/Stage4/bone_mustJump_Down_4_2.txt",
			Color::White, Vector2(74, 19), "Left"));

		AddActor(new MultiLine_Actor("../Assets/Actor/Stage4/bone_mustJump_Up_4_2.txt",
			Color::White, Vector2(41, 16), "Right"));
		AddActor(new MultiLine_Actor("../Assets/Actor/Stage4/bone_mustJump_Down_4_2.txt",
			Color::White, Vector2(41, 19), "Right"));
	}
	TStage_4_6.Reset();
}

void GameLevel::Stage4_6(float DeltaTime)
{
	TStage_4_6.Tick(DeltaTime);

	if (!TStage_4_6.IsTimeOut())
	{
		return;
	}

	if (TStage_4_6.Update(DeltaTime))
	{
		if (HadEatenFood == true)
		{
			HadEatenFood = false;
			//EatFoodTwo = !EatFoodTwo;
		}

		TurnEnd();
	}
	TStage_4_7.Reset();
}

void GameLevel::Stage4_7(float DeltaTime)
{
	TStage_4_7.Tick(DeltaTime);

	if (!TStage_4_7.IsTimeOut())
	{
		return;
	}

	if (TStage_4_7.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Speech_UI* speechUI = actor->As<Speech_UI>();
			if (speechUI != nullptr)
			{
				speechUI->SayTalking(
					"* 당신은 죄악이 등을 타고\n  오르는 것을 느꼈다.",
					Vector2(-33, 15), 20, true, "CharaTalking");
			}
		}
	}
}


