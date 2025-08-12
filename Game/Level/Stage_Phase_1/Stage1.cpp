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

void GameLevel::Stage1_1(float DeltaTime)
{
	TStage_1_1.Tick(DeltaTime);

	if (!TStage_1_1.IsTimeOut())
	{
		return;
	}

	if (TStage_1_1.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Player* player = actor->As<Player>();

			if (player != nullptr)
			{
				player->ChangeToIsGravity();
				//continue;
			}

		}

	}
	TStage_1_2.Reset();
}

void GameLevel::Stage1_2(float DeltaTime)
{
	TStage_1_2.Tick(DeltaTime);

	if (!TStage_1_2.IsTimeOut())
	{
		return;
	}

	if (TStage_1_2.Update(DeltaTime))
	{
		for (int i = 51; i < 66; i++)
			AddActor(new ActorWall_Width(Vector2(i, 20), 
				Color::Orange));
	}
	TStage_1_3.Reset();
}

void GameLevel::Stage1_3(float DeltaTime)
{
	TStage_1_3.Tick(DeltaTime);

	if (!TStage_1_3.IsTimeOut())
	{
		return;
	}

	if (TStage_1_3.Update(DeltaTime))
	{
		//AddActor()
		for(int i = 51; i < 66; i ++)
			AddActor(new MultiLine_Actor("../Assets/Actor/Stage1/bone_1.txt",
				Color::White, Vector2(i, 18), "Sans_Bone"));
	}
	TStage_1_4.Reset();
}

void GameLevel::Stage1_4(float DeltaTime)
{
	TStage_1_4.Tick(DeltaTime);

	if (!TStage_1_4.IsTimeOut())
	{
		return;
	}

	if (TStage_1_4.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			ActorWall_Width* RedWall = actor->As<ActorWall_Width>();

			if(RedWall != nullptr)
				RedWall->Destroy();

			MultiLine_Actor* Bones = actor->As<MultiLine_Actor>();

			if (Bones != nullptr)
				Bones->Destroy();
		}

	}
	TStage_1_5.Reset();
}

void GameLevel::Stage1_5(float DeltaTime)
{
	TStage_1_5.Tick(DeltaTime);

	if (!TStage_1_5.IsTimeOut())
	{
		return;
	}

	if (TStage_1_5.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Player* player = actor->As<Player>();
			if (player != nullptr)
				player->ChangeToIsGravity();
		}

		AddActor(new MultiLine_Actor("../Assets/Actor/Stage1/bone_array_1.txt",
			Color::White, Vector2(51, 16), "Right_Lower"));
	}
	TimerArrayCount = 1;
	TimerEndCount++;
	TStage_1_5_Array.Reset();
}

void GameLevel::Stage1_5_1(float DeltaTime)
{
	TStage_1_5_Array.Tick(DeltaTime);

	if (!TStage_1_5_Array.IsTimeOut())
	{
		return;
	}

	if (TStage_1_5_Array.Update(DeltaTime))
	{
		AddActor(new MultiLine_Actor("../Assets/Actor/Stage1/bone_array_2.txt",
			Color::White, Vector2(51, 16), "Right_Lower"));
	}
	TimerArrayCount = 2;
	TimerEndCount++;
	TStage_1_5_Array.Reset();
}

void GameLevel::Stage1_5_2(float DeltaTime)
{
	TStage_1_5_Array.Tick(DeltaTime);

	if (!TStage_1_5_Array.IsTimeOut())
	{
		return;
	}

	if (TStage_1_5_Array.Update(DeltaTime))
	{
		AddActor(new MultiLine_Actor("../Assets/Actor/Stage1/bone_array_3.txt",
			Color::White, Vector2(51, 16), "Right_Lower"));
	}
	TimerArrayCount = 3;
	TimerEndCount++;
	TStage_1_5_Array.Reset();
}

void GameLevel::Stage1_5_3(float DeltaTime)
{
	TStage_1_5_Array.Tick(DeltaTime);

	if (!TStage_1_5_Array.IsTimeOut())
	{
		return;
	}

	if (TStage_1_5_Array.Update(DeltaTime))
	{
		AddActor(new MultiLine_Actor("../Assets/Actor/Stage1/bone_array_4.txt",
			Color::White, Vector2(51, 16), "Right_Lower"));
	}
	TimerArrayCount = 1;
	TimerEndCount++;
	if (TimerEndCount < 6)
		TStage_1_5_Array.Reset();
	else
	{
		TStage_1_6.Reset();
		TimerArrayCount = 0;
		TimerEndCount = 0;
	}

}

void GameLevel::Stage1_6(float DeltaTime)
{
	TStage_1_6.Tick(DeltaTime);

	if (!TStage_1_6.IsTimeOut())
	{
		return;
	}

	if (TStage_1_6.Update(DeltaTime))
	{
		//4방향 블레스터
		MakeBlaster4();
	}
	TStage_1_7.Reset();
}

void GameLevel::Stage1_7(float DeltaTime)
{
	TStage_1_7.Tick(DeltaTime);

	if (!TStage_1_7.IsTimeOut())
	{
		return;

	}

	if (TStage_1_7.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Monster* blasterActor = actor->As<Monster>();

			if (blasterActor != nullptr)
			{
				DeleteBlaster4(blasterActor);
			}
		}
		//4방향 빔
		Breath4();
	}
	TStage_1_8.Reset();

}

void GameLevel::Stage1_8(float DeltaTime)
{
	TStage_1_8.Tick(DeltaTime);

	if (!TStage_1_8.IsTimeOut())
	{
		return;
	}

	if (TStage_1_8.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			BreathActor* breaths = actor->As<BreathActor>();
			if(breaths != nullptr)
				DeleteBreath(breaths);
		}

		MakeXBlaster();
	}
	TStage_1_9.Reset();
}

void GameLevel::Stage1_9(float DeltaTime)
{
	TStage_1_9.Tick(DeltaTime);

	if (!TStage_1_9.IsTimeOut())
	{
		return;
	}

	if (TStage_1_9.Update(DeltaTime))
	{

		for (Actor* actor : actors)
		{
			Monster* blasterActor = actor->As<Monster>();

			if (blasterActor != nullptr)
			{
				//if (monsterActor->CheckTag("GasterBlaster_45") ||
				//	monsterActor->CheckTag("GasterBlaster_-45") ||
				//	monsterActor->CheckTag("GasterBlaster"))
				//{
				//	monsterActor->Destroy();
				//}
				DeleteXBlaster(blasterActor);
			}
		}

		//X자브레스
		BreathX();
	}
	TStage_1_10.Reset();
}

void GameLevel::Stage1_10(float DeltaTime)
{
	TStage_1_10.Tick(DeltaTime);

	if (!TStage_1_10.IsTimeOut())
	{
		return;
	}

	if (TStage_1_10.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			BreathActor* breaths = actor->As<BreathActor>();
			if (breaths != nullptr)
				DeleteBreath(breaths);
		}

		//4방향 블레스터
		MakeBlaster4();
	}

	TStage_1_11.Reset();
}

//11에다가 브레스 발사를 넣고 12에다가 이 11을 넣으면됨
void GameLevel::Stage1_11(float DeltaTime)
{
	TStage_1_11.Tick(DeltaTime);

	if (!TStage_1_11.IsTimeOut())
	{
		return;

	}

	if (TStage_1_11.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Monster* blasterActor = actor->As<Monster>();

			if (blasterActor != nullptr)
			{
				//if (monsterActor->CheckTag("GasterBlaster_0") ||
				//	monsterActor->CheckTag("GasterBlaster_90") ||
				//	monsterActor->CheckTag("GasterBlaster_-90") ||
				//	monsterActor->CheckTag("GasterBlaster"))
				//{
				//	monsterActor->Destroy();
				//}
				DeleteBlaster4(blasterActor);
			}
		}
		Breath4();
	}
	TStage_1_12.Reset();
}

void GameLevel::Stage1_12(float DeltaTime)
{
	TStage_1_12.Tick(DeltaTime);

	if (!TStage_1_12.IsTimeOut())
	{
		return;
	}

	if (TStage_1_12.Update(DeltaTime))
	{

		for (Actor* actor : actors)
		{
			BreathActor* breath = actor->As<BreathActor>();
			if(breath != nullptr)
				DeleteBreath(breath);
		}
		MakeBigBlaster();
	}
	TStage_1_13.Reset();
}

void GameLevel::Stage1_13(float DeltaTime)
{
	TStage_1_13.Tick(DeltaTime);

	if (!TStage_1_13.IsTimeOut())
	{
		return;
	}

	if (TStage_1_13.Update(DeltaTime))
	{
		BreathBig();
	}
	TStage_1_14.Reset();
}

void GameLevel::Stage1_14(float DeltaTime)
{
	TStage_1_14.Tick(DeltaTime);

	if (!TStage_1_14.IsTimeOut())
	{
		return;
	}

	if (TStage_1_14.Update(DeltaTime))
	{
		for (Actor* actor : actors)
		{
			Monster* blasterActor = actor->As<Monster>();
			BreathActor* breath = actor->As<BreathActor>();
			if (blasterActor != nullptr)
			{
				//if (monsterActor->CheckTag("GasterBlaster_Big_Left") ||
				//	monsterActor->CheckTag("GasterBlaster_Big_Right"))
				//{
				//	monsterActor->Destroy();
				//}
				DeleteBigBlaster(blasterActor);
			}

			if(breath != nullptr)
				DeleteBreath(breath);
		}
	}
	TStage_1_15.Reset();
}

void GameLevel::Stage1_15(float DeltaTime)
{
	TStage_1_15.Tick(DeltaTime);

	if (!TStage_1_15.IsTimeOut())
	{
		return;
	}
	if (TStage_1_15.Update(DeltaTime))
	{
		for (Actor* actor :actors)
		{
			Speech_UI* speechUI = actor->As<Speech_UI>();

			if (speechUI != nullptr)
			{
				speechUI->SayTalking("흠..", Vector2(3, 2), 100, true, "SansTalking");
				Sleep(500);
				speechUI->SayTalking("왜 다들 처음부터\n강한 공격을\n쓰지않는지\n모르겠다니까.", Vector2(3, 1), 20, true, "SansTalking");
			}
		}
	}
	TStage_1_16.Reset();
}

void GameLevel::Stage1_16(float DeltaTime)
{
	TStage_1_16.Tick(DeltaTime);

	if (!TStage_1_16.IsTimeOut())
	{
		return;
	}
	if (TStage_1_16.Update(DeltaTime))
	{
		//for (Actor* actor : actors)
		//{
		//	Player* player = actor->As<Player>();

		//	if (player != nullptr)
		//	{
		//		player->SwitchTurn();
		//	}
		//}
		//DeleteMap();
		//ReadMapFile("map_talking.txt");
		TurnEnd();
	}
	TStage_1_17.Reset();
}

void GameLevel::Stage1_17(float DeltaTime)
{
	TStage_1_17.Tick(DeltaTime);

	if (!TStage_1_17.IsTimeOut())
	{
		return;
	}
	if (TStage_1_17.Update(DeltaTime))
	{
		PlaySound(L"../Assets/Sounds/sans_megalovania.wav", 0,
			SND_FILENAME | SND_ASYNC | SND_LOOP);
		for (Actor* actor : actors)
		{
			Player* player = actor->As<Player>();
			Speech_UI* speechUI = actor->As<Speech_UI>();
			if (speechUI != nullptr)
			{
				speechUI->SayTalking(
					"* 당신은 끔찍한 시간을\n  보내게 될 것 같은\n  기분이 든다.",
					Vector2(-33, 15), 20, true, "CharaTalking");
			}

			if (player != nullptr)
				player->LeftSide -= 11;
		}


	}
	Engine::Get().LoadEngineSetting("EngineSettings_LargeMap.txt");
	UIcontrollerNum = 1;
}




