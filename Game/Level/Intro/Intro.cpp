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

void GameLevel::Intro(float DeltaTime)
{
	IntroTimer.Tick(DeltaTime);

	if (!IntroTimer.IsTimeOut())
	{
		return;
	}
	//IntroTimer.Reset();

	if (IntroTimer.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{

			Speech_UI* speechUI = actor->As<Speech_UI>();
			if (speechUI != nullptr)
			{
				speechUI->SetIsVisible(true);
				speechUI->SayTalking
				("오늘은 정말 \n아름다운날이야", Vector2(3, 2), 100, true, "SansTalking");
				Sleep(100);
				speechUI->SayTalking
				("새들은 지저귀고 \n꽃들은 피어나고", Vector2(3, 2), 100, true, "SansTalking");
				Sleep(100);
				speechUI->SayTalking
				("이런날엔, 너같은\n꼬마들은...", Vector2(3, 2), 100, true, "SansTalking");
				speechUI->BlackOut();
			}
		}
	}
	BurningToHell.Reset();
}

void GameLevel::BlackOut_1(float DeltaTime)
{
	BurningToHell.Tick(DeltaTime);

	if (!BurningToHell.IsTimeOut())
	{
		return;
	}

	if (BurningToHell.Update(DeltaTime))
	{

		for (Actor* actor : actors)
		{
			Speech_UI* speechUI = actor->As<Speech_UI>();

			if (speechUI != nullptr)
			{
				speechUI->SayTalking
				("지옥에서 \n불타야해", Vector2(3, 2), 200, false, "SansTalking");
			}
		}
	}
	TStage_1_1.Reset();
}
