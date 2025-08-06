#pragma once
#include "Level/GameLevel.h"
#include "Actor/Player.h"
#include "Actor/ActorWall_Width.h"
#include "Actor/MultiLine_Actor.h"
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
			Color::White, Vector2(51, 16), "Right"));
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
			Color::White, Vector2(51, 16), "Right"));
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
			Color::White, Vector2(51, 16), "Right"));
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
			Color::White, Vector2(51, 16), "Right"));
	}
	TimerArrayCount = 1;
	TimerEndCount++;
	if(TimerEndCount < 6)
		TStage_1_5_Array.Reset();
}






