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
#include "Actor/Block.h"

void GameLevel::Stage5_1(float DeltaTime)
{
	TStage_5_1.Tick(DeltaTime);

	if (!TStage_5_1.IsTimeOut())
	{
		return;
	}

	if (TStage_5_1.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Speech_UI* speechUI = actor->As<Speech_UI>();
			if (speechUI != nullptr)
			{
				speechUI->SayTalking(
					"헤 헤 헤...",
					Vector2(3, 1), 20, true, "SansTalking");
			}
		}
	}
	
	TStage_5_2.Reset();
}

void GameLevel::Stage5_2(float DeltaTime)
{
	TStage_5_2.Tick(DeltaTime);

	if (!TStage_5_2.IsTimeOut())
	{
		return;
	}

	if (TStage_5_2.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Speech_UI* speechUI = actor->As<Speech_UI>();
			if (speechUI != nullptr)
			{
				speechUI->SayTalking(
					"네가 한 짓이지, 응?",
					Vector2(3, 1), 20, true, "SansTalking");
			}
		}
	}

	TStage_5_3.Reset();
}

void GameLevel::Stage5_3(float DeltaTime)
{
	TStage_5_3.Tick(DeltaTime);

	if (!TStage_5_3.IsTimeOut())
	{
		return;
	}

	if (TStage_5_3.Update(DeltaTime))
	{
		TurnStart();
	}
	
	TStage_5_4.Reset();
}

void GameLevel::Stage5_4(float DeltaTime)
{
	TStage_5_4.Tick(DeltaTime);

	if (!TStage_5_4.IsTimeOut())
	{
		return;
	}

	if (TStage_5_4.Update(DeltaTime))
	{
		AddActor(new Block(Vector2(41,20),"Right"));
	}

}
