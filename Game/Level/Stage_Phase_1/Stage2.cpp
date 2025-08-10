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


//void GameLevel::Stage2_0(float DeltaTime)
//{
//	TStage_2_0.Tick(DeltaTime);
//
//	if (!TStage_2_0.IsTimeOut())
//	{
//		return;
//	}
//	if (Input::GetController().GetKeyDown(VK_RETURN) && AttackTrigger == true)
//	{
//		DeleteAttackUI();
//		bSansIsMoving = true;
//		TStage_2_1.Reset();
//	}
//	if (TStage_2_0.Update(DeltaTime))
//	{
//		DeleteAttackUI();
//		bSansIsMoving = true;
//	}
//	TStage_2_1.Reset();
//}

void GameLevel::Stage2_1(float DeltaTime)
{
	TStage_2_1.Tick(DeltaTime);

	if (!TStage_2_1.IsTimeOut())
	{
		return;
	}

	if (TStage_2_1.Update(DeltaTime))
	{

		for (Actor* actor : actors)
		{
			Speech_UI* speechUI = actor->As<Speech_UI>();
			if (speechUI != nullptr)
			{
				speechUI->SayTalking("뭐?\n내가 가만히 서서\n맞아 줄거라 생각했어?",
					Vector2(3, 2), 20, true, "SansTalking");
			}
		}
	}
	TStage_2_2.Reset();
}

void GameLevel::Stage2_2(float DeltaTime)
{
	TStage_2_2.Tick(DeltaTime);

	if (!TStage_2_2.IsTimeOut())
	{
		return;
	}

	if (TStage_2_2.Update(DeltaTime))
	{

		TurnStart();

		if (EatFoodTwo)
		{
			TStage_2_3.Reset();
			EatFoodTwo = false;
			return;
		}
		else
		{
			CheckPlayerGravity();
		}
	}
	TStage_2_3.Reset();
}

void GameLevel::Stage2_3(float DeltaTime)
{
	TStage_2_3.Tick(DeltaTime);

	if (!TStage_2_3.IsTimeOut())
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

	if (TimerEndCount < 8)
	{
		TStage_2_3.Reset();
	}
	else
	{
		TimerEndCount = 0;
		TStage_2_4.Reset();
	}
}

void GameLevel::Stage2_4(float DeltaTime)
{
	TStage_2_4.Tick(DeltaTime);

	if (!TStage_2_4.IsTimeOut())
	{
		return;
	}

	if (TStage_2_4.Update(DeltaTime))
	{
		if (HadEatenFood == true)
		{
			HadEatenFood = true;
			EatFoodTwo = !EatFoodTwo;
		}

		TurnEnd();
	}
	TStage_2_5.Reset();
}

void GameLevel::Stage2_5(float DeltaTime)
{
	TStage_2_5.Tick(DeltaTime);

	if (!TStage_2_5.IsTimeOut())
	{
		return;
	}

	if (TStage_2_5.Update(DeltaTime))
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






