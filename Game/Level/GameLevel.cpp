#include "GameLevel.h"
#include "Engine.h"

//#include "Stage/Stage1.cpp"

#include "Actor/Player.h"
#include "Actor/Monster.h"
#include "Actor/MultiLine_Actor.h"
#include "Actor/Wall_Length.h"
#include "Actor/Wall_Width.h"
#include "Actor/ActorWall_Length.h"
#include "Actor/ActorWall_Width.h"
#include "Actor/BreathActor.h"
#include "Actor/Block.h"
#include "UI/Stat_UI.h"
#include "UI/Speech_UI.h"
#include "UI/Attack_UI/AttackUI_Length.h"
#include "UI/Attack_UI/AttackUI_Width.h"
#include "UI/Attack_UI/AttackUI_Mini_Width.h"
#include "UI/Attack_UI/AttackUI_DoubleLine.h"

#include "Input.h"
#include <Windows.h>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

GameLevel::GameLevel()
{
	SetConsoleTitle(L"♥ UnderTale");
	//플레이어 맵 파일 리딩
	ReadMapFile("map_small.txt");
	

	//턴 카운트
	TurnCount = 1;
	//플레이어 렌더링
	AddActor(new Player());

	//샌즈 렌더링
	AddActor(new Monster("../Assets/Actor/sans_unicode_3.txt",
		Color::White, Vector2(50, 0), "Sans"));

	//파란색 뼈 움직이면 피해입음 기본뼈랑 같이써야댐
	//AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt",
	//	Color::SkyBlue, Vector2(55, 18), "BlueBoneLeft"));

	//AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt",
	//	Color::White, Vector2(64, 18), "Bone"));


	//AddActor(new Block(Vector2(60,20),"Right"));
	//MakeAttackUIFile();
	//UI
	//공격 UI
	AddActor(new MultiLine_UI("../Assets/UI/fight.txt",
		Color::Yellow, Vector2(39, 25), UI_Type::FIGHT, "MainUI"));
	//행동 UI
	AddActor(new MultiLine_UI("../Assets/UI/act.txt",
		Color::Yellow, Vector2(49, 25), UI_Type::ACTOR, "MainUI"));
	//아이템 UI
	AddActor(new MultiLine_UI("../Assets/UI/item.txt",
		Color::Yellow, Vector2(59, 25), UI_Type::ITEM, "MainUI"));
	//자비 UI
	AddActor(new MultiLine_UI("../Assets/UI/mercy.txt",
		Color::Yellow, Vector2(69, 25), UI_Type::MERCY, "MainUI"));

	//말풍선
	AddActor(new Speech_UI("../Assets/UI/speech_bubble.txt", Color::White,
		Vector2(66, 2)));


	//캐릭터 상태 UI
	AddActor(new Stat_UI("CHARA", Color::White, Vector2(33, 23), 'C'));
	AddActor(new Stat_UI("LV19", Color::White, Vector2(40, 23), 'L'));
	AddActor(new Stat_UI("HP", Color::White, Vector2(46, 23)));

	for (int i = 1; i <= 12; i++)
		AddActor(new Stat_UI("|", Color::Yellow, Vector2(47 + i, 23), 40 + i));

	AddActor(new Stat_UI("KR", Color::White, Vector2(62, 23)));
	AddActor(new Stat_UI("92", Color::White, Vector2(65, 23), 'H'));
	AddActor(new Stat_UI("/ 92", Color::White, Vector2(68, 23)));

	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();
		
		if(player != nullptr)
			player->SetHp(92);
	}

	UIcontrollerNum = 1;
	bSansIsMoving = false;
	HadEatenFood = false;
	//EatFoodTwo = false;
	//testUImode = false;
	//levelTimer.SetTargetTime(2.0f);

	//인트로
	IntroTimer.SetTargetTime(0.1f);
	BurningToHell.SetTargetTime(1.0f);

	//스테이지1
	TStage_1_1.SetTargetTime(1.0f);
	TStage_1_2.SetTargetTime(0.5f);
	TStage_1_3.SetTargetTime(0.5f);
	TStage_1_4.SetTargetTime(0.5f);
	TStage_1_5.SetTargetTime(0.5f);
	TStage_1_5_Array.SetTargetTime(0.3f);
	TStage_1_6.SetTargetTime(0.5f);
	TStage_1_7.SetTargetTime(0.5f); //4자 브레스 생성
	TStage_1_8.SetTargetTime(0.5f); //4자브레스 삭제
	TStage_1_9.SetTargetTime(0.5f); //x자브레스 생성
	TStage_1_10.SetTargetTime(0.5f); //x자브레스 삭제 및 4자브레스 다시
	TStage_1_11.SetTargetTime(0.5f); //초대형 블래스터 생성!
	TStage_1_12.SetTargetTime(0.5f); //초대형 블래스터 삭제 및 슈퍼브레스
	TStage_1_13.SetTargetTime(0.5f); //초대형 브레스 삭제
	TStage_1_14.SetTargetTime(1.5f); //전투 끝 샌즈 대사 차례
	TStage_1_15.SetTargetTime(1.5f); //전투 끝 샌즈 대사 차례
	TStage_1_16.SetTargetTime(1.0f); //턴 1 샌즈의 턴 종료
	TStage_1_17.SetTargetTime(0.5f); //턴 1 끝 플레이어 차례

	//스테이지 2
	TStage_2_1.SetTargetTime(1.0f); //턴 2 시작 공격실패 샌즈의 턴
	TStage_2_2.SetTargetTime(2.0f); //턴 2 시작 공격실패 샌즈의 턴
	TStage_2_3.SetTargetTime(0.5f); //턴 2 샌즈의 공격
	TStage_2_4.SetTargetTime(2.0f); //턴 2 샌즈의 턴 종료
	TStage_2_5.SetTargetTime(0.5f); //턴 2 끝 플레이어의 차례

	//스테이지 3
	TStage_3_1.SetTargetTime(1.0f);
	TStage_3_2.SetTargetTime(0.5f);
	TStage_3_3.SetTargetTime(0.1f);
	TStage_3_4.SetTargetTime(0.5f);
	TStage_3_5.SetTargetTime(0.3f);
	TStage_3_6.SetTargetTime(0.3f);
	TStage_3_7.SetTargetTime(0.3f);
	TStage_3_8.SetTargetTime(1.0f);
	TStage_3_9.SetTargetTime(0.5f);

	//스테이지 4
	TStage_4_1.SetTargetTime(1.0f); //턴 4 시작 공격실패 샌즈의 턴
	TStage_4_2.SetTargetTime(0.5f); 
	TStage_4_3.SetTargetTime(0.5f); 
	TStage_4_3_1.SetTargetTime(0.5f); 
	TStage_4_4.SetTargetTime(0.5f); 
	TStage_4_5.SetTargetTime(1.0f); 
	TStage_4_6.SetTargetTime(2.0f); 
	TStage_4_7.SetTargetTime(0.5f); 

	//스테이지 5
	TStage_5_1.SetTargetTime(1.0f); 
	TStage_5_2.SetTargetTime(1.0f);
	TStage_5_3.SetTargetTime(1.0f);
	TStage_5_4.SetTargetTime(1.0f);


	AttackTrigger = false;
}

GameLevel::~GameLevel()
{
	mciSendStringW(L"stop bgm", NULL, 0, NULL);
	mciSendStringW(L"close bgm", NULL, 0, NULL);
	mciSendStringW(L"stop se", NULL, 0, NULL);
	mciSendStringW(L"close se", NULL, 0, NULL);
}

void GameLevel::BeginPlay()
{
	Super::BeginPlay();
	SetConsoleOutputCP(CP_UTF8);
}

void GameLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameOver(DeltaTime);
	DieToClearFront();
	//LevelTest(DeltaTime);

	//if (Input::GetController().GetKeyDown(VK_CONTROL))
	//{
	//	IsMapSmall = !IsMapSmall;
	//	if (IsMapSmall)
	//	{
	//		ReadMapFile("map_small.txt");
	//	}
	//	else
	//	{
	//		DeleteMap();
	//	}
	//}
	
	//std::cout << UIcontrollerNum;
	//if (TurnCount != 2)
	//{
	//	TStage_2_1.Reset();
	//}

	if (Input::GetController().GetKeyDown(VK_NUMPAD1))
	{
		for (Actor* actor : actors)
		{
			Speech_UI* speechUI = actor->As<Speech_UI>();
			if (speechUI != nullptr)
			{
				speechUI->BlackOut();

			}
		}
	}

	if (Input::GetController().GetKeyDown(VK_NUMPAD1))
	{
		Start = true;
	}

	if (Input::GetController().GetKeyDown(VK_NUMPAD2))
	{
		Engine::Get().LoadEngineSetting("EngineSettings_LargeMap.txt");
	}

	//Stage1 타이머
	if (!IntroTimer.IsTimeOut())
	{
		Intro(DeltaTime);
	}
	else if (!BurningToHell.IsTimeOut())
	{
		BlackOut_1(DeltaTime);
	}
	else if (!TStage_1_1.IsTimeOut())
	{
		Stage1_1(DeltaTime);
	}
	else if (!TStage_1_2.IsTimeOut())
	{
		Stage1_2(DeltaTime);
	}
	else if (!TStage_1_3.IsTimeOut())
	{
		Stage1_3(DeltaTime);
	}
	else if (!TStage_1_4.IsTimeOut())
	{
		Stage1_4(DeltaTime);
	}
	else if (!TStage_1_5.IsTimeOut())
	{
		Stage1_5(DeltaTime);
	}
	else if (!TStage_1_5_Array.IsTimeOut() && TimerArrayCount == 1)
	{
		Stage1_5_1(DeltaTime);
	}
	else if (!TStage_1_5_Array.IsTimeOut() && TimerArrayCount == 2)
	{
		Stage1_5_2(DeltaTime);
	}
	else if (!TStage_1_5_Array.IsTimeOut() && TimerArrayCount == 3)
	{
		Stage1_5_3(DeltaTime);
	}
	/////////////////////////////////////////////
	else if (!TStage_1_6.IsTimeOut())
	{
		Stage1_6(DeltaTime);
	}
	else if (!TStage_1_7.IsTimeOut())
	{
		Stage1_7(DeltaTime);
	}
	else if (!TStage_1_8.IsTimeOut())
	{
		Stage1_8(DeltaTime);
	}
	else if (!TStage_1_9.IsTimeOut())
	{
		Stage1_9(DeltaTime);
	}
	else if (!TStage_1_10.IsTimeOut())
	{
		Stage1_10(DeltaTime);
	}
	else if (!TStage_1_11.IsTimeOut())
	{
		Stage1_11(DeltaTime);
	}
	else if (!TStage_1_12.IsTimeOut())
	{
		Stage1_12(DeltaTime);
	}
	else if (!TStage_1_13.IsTimeOut())
	{
		Stage1_13(DeltaTime);
	}
	else if (!TStage_1_14.IsTimeOut())
	{
		Stage1_14(DeltaTime);
	}
	else if (!TStage_1_15.IsTimeOut())
	{
		Stage1_15(DeltaTime);
	}
	else if (!TStage_1_16.IsTimeOut())
	{
		Stage1_16(DeltaTime);
	}
	else if (!TStage_1_17.IsTimeOut())
	{
		Stage1_17(DeltaTime);
	}

	//스테이지 2
	else if (!TStage_2_1.IsTimeOut() && TurnCount == 2)
	{
		Stage2_1(DeltaTime);
	}
	else if (!TStage_2_2.IsTimeOut() && TurnCount == 2)
	{
		Stage2_2(DeltaTime);
	}
	else if (!TStage_2_3.IsTimeOut() && TurnCount == 2)
	{
		Stage2_3(DeltaTime);
	}
	else if (!TStage_2_4.IsTimeOut() && TurnCount == 2)
	{
		Stage2_4(DeltaTime);
	}
	else if (!TStage_2_5.IsTimeOut() && TurnCount == 2)
	{
		Stage2_5(DeltaTime);
	}

	//스테이지 3
	else if (!TStage_3_1.IsTimeOut() && TurnCount == 3)
	{
		Stage3_1(DeltaTime);
	}
	else if (!TStage_3_2.IsTimeOut() && TurnCount == 3)
	{
		Stage3_2(DeltaTime);
	}
	else if (!TStage_3_3.IsTimeOut() && TurnCount == 3)
	{
		Stage3_3(DeltaTime);
	}
	else if (!TStage_3_4.IsTimeOut() && TurnCount == 3)
	{
		Stage3_4(DeltaTime);
	}	
	else if (!TStage_3_5.IsTimeOut() && TurnCount == 3)
	{
		Stage3_5(DeltaTime);
	}
	else if (!TStage_3_6.IsTimeOut() && TurnCount == 3)
	{
		Stage3_6(DeltaTime);
	}	
	else if (!TStage_3_7.IsTimeOut() && TurnCount == 3)
	{
		Stage3_7(DeltaTime);
	}	
	else if (!TStage_3_8.IsTimeOut() && TurnCount == 3)
	{
		Stage3_8(DeltaTime);
	}
	else if (!TStage_3_9.IsTimeOut() && TurnCount == 3)
	{
		Stage3_9(DeltaTime);
	}

	//스테이지4
	else if (!TStage_4_1.IsTimeOut() && TurnCount == 4)
	 {
		 Stage4_1(DeltaTime);
	 }
	else if (!TStage_4_2.IsTimeOut() && TurnCount == 4)
	 {
		 Stage4_2(DeltaTime);
	 }
	else if (!TStage_4_3.IsTimeOut() && TurnCount == 4)
	 {
		 Stage4_3(DeltaTime);
	 }
	else if (!TStage_4_3_1.IsTimeOut() && TurnCount == 4)
	 {
		 Stage4_3_1(DeltaTime);
	 }
	else if (!TStage_4_4.IsTimeOut() && TurnCount == 4)
	 {
		 Stage4_4(DeltaTime);
	 }
	else if (!TStage_4_5.IsTimeOut() && TurnCount == 4)
	 {
		 Stage4_5(DeltaTime);
	 }
	else if (!TStage_4_6.IsTimeOut() && TurnCount == 4)
	 {
		 Stage4_6(DeltaTime);
	 }
	else if (!TStage_4_7.IsTimeOut() && TurnCount == 4)
	 {
		 Stage4_7(DeltaTime);
	 }

	//스테이지5
	else if (!TStage_5_1.IsTimeOut() && TurnCount == 5)
	 {
		 Stage5_1(DeltaTime);
	 }
	else if (!TStage_5_2.IsTimeOut() && TurnCount == 5)
	 {
		 Stage5_2(DeltaTime);
	 }
	else if (!TStage_5_3.IsTimeOut() && TurnCount == 5)
	 {
		 Stage5_3(DeltaTime);
	 }
	else if (!TStage_5_4.IsTimeOut() && TurnCount == 5)
	 {
		 Stage5_4(DeltaTime);
	 }
	

	//테스트 용도
	//std::cout << UIcontroller;
	UIController();
	ProcessCollisionPlayerAndBlock();
	ProcessCollisionPlayerAndEnemyObject();

}

void GameLevel::ControllMainUI(MultiLine_UI* mainUI)
{
	//1:FIGHT, 2:ACT, 3:ITEM, 4:MERCY

	mainUI->SetColor(Color::Yellow);

	if (UIcontrollerNum == 1 && (mainUI->GetUIType() == UI_Type::FIGHT)) //FIGHT
	{
		mainUI->SetColor(Color::Orange);
	}
	else if (UIcontrollerNum == 2 && (mainUI->GetUIType() == UI_Type::ACTOR)) // ACT
	{
		mainUI->SetColor(Color::Orange);
	}
	else if (UIcontrollerNum == 3 && (mainUI->GetUIType() == UI_Type::ITEM)) //ITEM
	{
		mainUI->SetColor(Color::Orange);
	}
	else if (UIcontrollerNum == 4 && (mainUI->GetUIType() == UI_Type::MERCY)) //MERCY
	{
		mainUI->SetColor(Color::Orange);
	}
}

void GameLevel::Render()
{
	Super::Render();
}

void GameLevel::ReadMapFile(const char* fileName)
{
	char filePath[256] = {};
	sprintf_s(filePath, 256, "../Assets/Map/%s", fileName);

	FILE* mapFile = nullptr;
	fopen_s(&mapFile, filePath, "rt");

	//예외처리
	if (mapFile == nullptr)
	{
		std::cout << "Fatal Error : Can not Read Map File\n";
		__debugbreak();
		return;
	}

	//파싱 하기 
	fseek(mapFile, 0, SEEK_END); //파일 포인터를 파일 주소의 끝 값으로 이동
	size_t fileSize = ftell(mapFile); //파일의 크기를 저장
	rewind(mapFile); //다시 파일 포인터를 파일 주소의 시작점으로 이동

	//확인한 파일 크기를 활용해 버퍼 할당
	char* buffer = new char[fileSize + 1];

	size_t readSize = fread(buffer, sizeof(char), fileSize, mapFile);


	//배열 순회를 위한 인덱스
	int index = 0;

	//문자열 길이
	int size = (int)readSize;

	//좌표
	Vector2 position;

	while (index < size) //인덱스가 파일 문자열 길이를 넘어가면 종료
	{
		//맵 문자 확인
		char mapBlock = buffer[index++];

		if (mapBlock == '\n') // 개행문자 처리
		{
			++position.y;
			position.x = 0;

			continue;
		}

		switch (mapBlock)
		{
		case '|':
			AddActor(new Wall_Length(position));
			break;
		case '_':
			AddActor(new Wall_Width(position));
			break;
		}

		++position.x;
	}

	delete[] buffer;

	fclose(mapFile);

	//system("cls");
}

void GameLevel::ReadAttackUIFile(const char* fileName,Color color)
{
	char filePath[256] = {};
	sprintf_s(filePath, 256, "../Assets/Actor/AttackUI/%s", fileName);

	FILE* mapFile = nullptr;
	fopen_s(&mapFile, filePath, "rt");

	//예외처리
	if (mapFile == nullptr)
	{
		std::cout << "Fatal Error : Can not Read Map File\n";
		__debugbreak();
		return;
	}

	//파싱 하기 
	fseek(mapFile, 0, SEEK_END); //파일 포인터를 파일 주소의 끝 값으로 이동
	size_t fileSize = ftell(mapFile); //파일의 크기를 저장
	rewind(mapFile); //다시 파일 포인터를 파일 주소의 시작점으로 이동

	//확인한 파일 크기를 활용해 버퍼 할당
	char* buffer = new char[fileSize + 1];

	size_t readSize = fread(buffer, sizeof(char), fileSize, mapFile);


	//배열 순회를 위한 인덱스
	int index = 0;

	//문자열 길이
	int size = (int)readSize;

	//좌표
	Vector2 position;

	while (index < size) //인덱스가 파일 문자열 길이를 넘어가면 종료
	{
		//맵 문자 확인
		char mapBlock = buffer[index++];

		if (mapBlock == '\n') // 개행문자 처리
		{
			++position.y;
			position.x = 0;

			continue;
		}

		switch (mapBlock)
		{
		case '|':
			AddActor(new AttackUI_Length(position,color));
			break;
		case '_':
			AddActor(new AttackUI_Width(position,color));
			break;
		case '-':
			AddActor(new AttackUI_Mini_Width(position, color));
			break;
		case '=':
			AddActor(new AttackUI_DoubleLine(position, color));
			break;
		}

		++position.x;
	}

	delete[] buffer;

	fclose(mapFile);
}

void GameLevel::MakeAttackUIFile()
{
	ReadAttackUIFile("green.txt", Color::Banana);
	ReadAttackUIFile("red.txt", Color::Red);
	ReadAttackUIFile("yellow.txt", Color::Yellow);
	ReadAttackUIFile("Cross.txt", Color::Green);
	ReadAttackUIFile("white.txt", Color::White);
}

void GameLevel::CheckPlayerGravity()
{
	for (Actor* actor : actors)
	{
		if (auto* player = actor->As<Player>())
			player->ChangeToIsGravity();
	}
}

void GameLevel::SettingPlayerGravity(bool SetBool)
{
	for (Actor* actor : actors)
	{
		if (auto* player = actor->As<Player>())
			player->SettingToGravity(SetBool);
	}
}

void GameLevel::UIController()
{
	//플레이어가 턴인지 가져와서 레벨에 저장
	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();
		MultiLine_UI* mainUI = actor->As<MultiLine_UI>();
		Monster* monster = actor->As<Monster>();
		if (player != nullptr)
		{
			PlayerIsTurn = player->GetIsTurn();
			PlayerHp = player->GetHp();
		}

		if (monster != nullptr)
		{
			monster->SetIsSansMoving(bSansIsMoving);
		}

		//플레이어가 턴이 아닐때 UI조작하게 설정
		if (PlayerIsTurn == false)
		{
			if (mainUI != nullptr)
			{
				ControllMainUI(mainUI);
			}
		}

		if (PlayerIsTurn == true)
		{
			MultiLine_UI* mainUI = actor->As<MultiLine_UI>();
			if (mainUI != nullptr)
			{
				mainUI->SetColor(Color::Yellow);
			}
		}

		Stat_UI* statUI = actor->As<Stat_UI>();
		if (statUI != nullptr && statUI->GetTag() == 'H')
		{
			statUI->SetStringStatImage(PlayerHp);
		}

		for (int i = 12; i > 0; i--)
		{
			if (statUI != nullptr && statUI->GetTag() == 40 + i)
			{
				if (PlayerHp > 92 - (13 - i) * 8)
					statUI->SetColor(Color::Yellow);
				else
					statUI->SetColor(Color::Red);
			}
		}
	}
	//UI조작
	if (!PlayerIsTurn && Input::GetController().GetKeyDown(VK_LEFT))
	{
		if (UIcontrollerNum < 1)
			return;

		UIcontrollerNum--;
	}

	if (!PlayerIsTurn && Input::GetController().GetKeyDown(VK_RIGHT))
	{
		if (UIcontrollerNum > 3)
			return;

		UIcontrollerNum++;
	}
	//엔터키 누를시 해당 UI작동

	//전처리
	if (!PlayerIsTurn && Input::GetController().GetKeyUp(VK_RETURN))
	{
		if(UIcontrollerNum == 1)
			AttackTrigger = !AttackTrigger;
	}

	if (!PlayerIsTurn && Input::GetController().GetKeyDown(VK_RETURN) && AttackTrigger == false)
	{
		if (UIcontrollerNum == 1)
		{
			Attack();
		}	

		if (UIcontrollerNum == 3)
		{
			EatItem();

			if (TurnCount == 1)
			{
				TurnCount++;
				TurnTwoFristFoodCheck = true;
			}

			AttackAndStartTurn(TurnCount);
		}
	}
	else if (!PlayerIsTurn && Input::GetController().GetKeyDown(VK_RETURN) && AttackTrigger == true)
	{
		if (TurnCount < 2)
		{
			TurnCount++;
			DeleteAttackUI();
			AttackAndStartTurn(TurnCount);
			for (Actor* actor : actors)
			{
				MultiLine_Actor* stick = actor->As<MultiLine_Actor>();
				if (stick != nullptr && stick->CheckTag("Stick"))
				{
					stick->Destroy();
				}
			}

			bSansIsMoving = true;
		}
		else if(TurnCount >= 2)
		{
			TurnCount++;
			bSansIsMoving = true;
			DeleteAttackUI();
			AttackAndStartTurn(TurnCount);
			for (Actor* actor : actors)
			{
				MultiLine_Actor* stick = actor->As<MultiLine_Actor>();
				if (stick != nullptr && stick->CheckTag("Stick"))
				{
					stick->Destroy();
				}
			}

			AttackSans();
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndEnemyObject()
{
	Player* player = nullptr;

	std::vector<MultiLine_Actor*>EnemyObject_Actor;
	std::vector<MultiLine_Actor*>BlueEnemyObject_Actor;
	std::vector<BreathActor*>Breath_Actor;

	for (Actor* actor : actors)
	{
		MultiLine_Actor* EnemyObject = actor->As<MultiLine_Actor>();
		BreathActor* BreathObject = actor->As<BreathActor>();

		//만약 파란색이 아니면 그냥 적 액터리스트에담고 맞으면 파란적리스트에 넣음
		if (EnemyObject != nullptr && !EnemyObject->CheckTag("BlueBoneLeft")
			&& !EnemyObject->CheckTag("BlueBoneRight")) //적 오브젝트 발견
		{
			EnemyObject_Actor.emplace_back(EnemyObject); // 배열에 추가
			continue;
		}

		if (EnemyObject != nullptr && (EnemyObject->CheckTag("BlueBoneLeft") || EnemyObject->CheckTag("BlueBoneRight"))) //파란색 적 오브젝트 발견
		{
			BlueEnemyObject_Actor.emplace_back(EnemyObject); // 배열에 추가
			continue;
		}


		if (BreathObject != nullptr && BreathObject->CheckTag("breath"))// && MonsterObject->GetTag() == "breath"
		{
			Breath_Actor.emplace_back(BreathObject);
			continue;
		}

		if (player == nullptr) //플레이어를 못찾았을시
		{
			player = actor->As<Player>(); // 찾기
		}
	}

	//적 오브젝트를 담은 배열의 크기가 0이거나 플레이어를 못찾았을시
	if (BlueEnemyObject_Actor.size() == 0 && EnemyObject_Actor.size() == 0 && Breath_Actor.size() == 0 || !player)
	{
		return;
	}

	//if (Monster_Actor.size() == 0 || !player)
	//{
	//	return;
	//}

	//적 오브젝트포인터를 스택에 할당한 후 힙에 할당된
	// 적 오브젝트를 담은 배열의 주소를 가르켜 순환하며 탐색하기
	for (auto* AEnemyObject : EnemyObject_Actor)
	{
		//충돌했다면?
		if (player->GetIsTurn() && player->TestIntersect(AEnemyObject))
		{

			int PlayerCurrentHp = player->GetHp();
			player->SetHp(PlayerCurrentHp - 1);
		}
	}

	for (auto* ABlueEnemyObject : BlueEnemyObject_Actor)
	{
		//충돌했다면?
		if (player->GetIsTurn() && player->TestIntersect(ABlueEnemyObject))
		{
			if (player->GetIsMoving())
			{
				int PlayerCurrentHp = player->GetHp();
				player->SetHp(PlayerCurrentHp - 1);
			}
		}
	}

	for (auto* ABreathObject : Breath_Actor)
	{
		if (player->GetIsTurn() && player->TestIntersect(ABreathObject))
		{
			int PlayerCurrentHp = player->GetHp();
			player->SetHp(PlayerCurrentHp - 1);
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndBlock()
{
	Player* player = nullptr;

	std::vector<Block*> block_Actor;

	for (Actor* const actor : actors)
	{
		Block* block = actor->As<Block>();

		if (block != nullptr)
		{
			block_Actor.emplace_back(block);
			continue;
		}

		if (player == nullptr) //플레이어를 못찾았을시
		{
			player = actor->As<Player>(); // 찾기
		}
	}

	if (block_Actor.size() == 0 || player == nullptr)
	{
		return;
	}

	bool isonblock = false;

		for (auto* Ablock_Actor : block_Actor)
		{
			if (player->GetIsTurn() && player->TestIntersect_Block(Ablock_Actor))
			{
				isonblock = true;
				break;
			}
		}

		player->SetIsOnTheBlock(isonblock);
}



void GameLevel::GameOver(float DeltaTime)
{
	if (bGameOverTriggered) {
		// 이미 게임오버 트리거된 상태: 타이머만 진행
		GameOverDelay.Tick(DeltaTime);
		if (GameOverDelay.IsTimeOut()) {
			Die(); // 여기서 한 번만 종료
		}
		return;
	}

	// 아직 게임오버 트리거 안 됨: 플레이어 HP 체크
	Player* player = nullptr;
	Speech_UI* speechUI = nullptr;

	for (Actor* actor : actors)
	{
		if (!player)    player = actor->As<Player>();
		if (!speechUI)  speechUI = actor->As<Speech_UI>();
	}

	if (player && player->GetHp() <= 0)
	{
		mciSendStringW(L"stop bgm", NULL, 0, NULL);
		mciSendStringW(L"close bgm", NULL, 0, NULL);
		mciSendStringW(L"stop se", NULL, 0, NULL);
		mciSendStringW(L"close se", NULL, 0, NULL);
		// 한 번만 실행
		bGameOverTriggered = true;

		// 입력/턴 등 멈추기
		player->SwitchTurn();

		// 화면/맵 정리 (한 번만)
		DeleteMap();
		system("cls");

		// 대사 띄우기
		if (speechUI) {
			speechUI->SayTalking(
				"Chara! 의지를 가져야 한다.\n어서 일어나렴!",
				Vector2(-33, 15), 100, true, "CharaTalking");
		}

		// 종료 대기 타이머 리셋
		GameOverDelay.Reset();

		// 이 프레임엔 바로 종료하지 않음
		player->SetDieCheck(true); // 상태 표시는 하되 Die()는 나중에
	}
}


void GameLevel::Die()
{
	DieToDark = true;
	// 실제 종료는 여기서 한 번만
	Player* player = nullptr;
	for (Actor* actor : actors)
		if (!player) player = actor->As<Player>();

	if (player && player->GetDieCheck())
	{
		player->QuitGame();
	}
}

void GameLevel::DieToClearFront()
{
	if (DieToDark)
		system("cls");
}

void GameLevel::DeleteMap()
{
	for (Actor* actor : actors)
	{
		Wall_Length* wallLegth = actor->As<Wall_Length>();
		Wall_Width* wallWidth = actor->As<Wall_Width>();

		if (wallLegth != nullptr)
		{
			wallLegth->Destroy();
		}

		if (wallWidth != nullptr)
		{
			wallWidth->Destroy();
		}
	}
}

void GameLevel::DeleteAttackUI()
{
	for (Actor* actor : actors)
	{
		AttackUI_Length* attackUILegth = actor->As<AttackUI_Length>();
		AttackUI_Width* attackUIWidth = actor->As<AttackUI_Width>();
		AttackUI_Mini_Width* attackUIMiniWidth = actor->As<AttackUI_Mini_Width>();
		AttackUI_DoubleLine* attackUIDoubleLine = actor->As<AttackUI_DoubleLine>();

		if (attackUILegth != nullptr)
		{
			attackUILegth->Destroy();
		}

		if (attackUIWidth != nullptr)
		{
			attackUIWidth->Destroy();
		}

		if (attackUIMiniWidth != nullptr)
		{
			attackUIMiniWidth->Destroy();
		}

		if (attackUIDoubleLine != nullptr)
		{
			attackUIDoubleLine->Destroy();
		}
	}
}

void GameLevel::TurnStart()
{
	DeleteMap();
	ReadMapFile("map.txt");


	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();

		if (player != nullptr)
		{
			player->SwitchTurn();
		}
	}
}

void GameLevel::TurnStart_MiniMap()
{
	DeleteMap();
	ReadMapFile("map_small.txt");

	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();

		if (player != nullptr)
		{
			player->SwitchTurn();
		}
	}
}

void GameLevel::TurnEnd()
{
	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();

		if (player != nullptr)
		{
			player->SwitchTurn();
		}
	}
	DeleteMap();
	ReadMapFile("map_talking.txt");
}

void GameLevel::AttackSans()
{
	for (Actor* actor : actors)
	{
		Monster* sans = actor->As<Monster>();

		if (sans != nullptr)
		{
			sans->SetSansLeftRight(true);
		}

	}
}

void GameLevel::EatItem()
{
	HadEatenFood = true;

	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();

		if (player != nullptr)
		{
			int currentHp = player->GetHp();
			if (currentHp + 50 < 92)
			{
				player->SetHp(currentHp + 50);
			}
			else
			{
				player->SetHp(92);
			}
		}

		Speech_UI* speechUI = actor->As<Speech_UI>();
		if (speechUI != nullptr)
		{
			speechUI->SayTalking(
				"* 스테이크를 먹었다!\n   체력을 50 회복했다!",
				Vector2(-33, 15), 20, true, "CharaTalkingAndEatFood");
		}
	}
}

void GameLevel::Attack()
{
	MakeAttackUIFile();
	AddActor(new MultiLine_Actor("../Assets/Actor/stick.txt",
		Color::White, Vector2(41, 17), "Stick"));
}

void GameLevel::AttackAndStartTurn(int TurnCount)
{
	if (TurnCount == 2)
	{
		if (HadEatenFood == false)
		{
			//EatFoodTwo = false;
			TStage_2_1.Reset();
			TStage_2_2.ForceTimeOut();
		}
		else if (HadEatenFood == true)
		{
			TStage_2_2.Reset();
			TStage_2_1.ForceTimeOut();
		}

	}
	else if (TurnCount == 3)
	{
		if (TurnTwoFristFoodCheck == true)
		{
			this->TurnCount = 2;
			TStage_2_1.Reset();
			TStage_2_2.ForceTimeOut();
		}
		else
		{
			if (HadEatenFood == false)
			{
				//EatFoodTwo = false;
				TStage_3_1.Reset();
				TStage_3_2.ForceTimeOut();

			}
			else if (HadEatenFood == true)
			{
				TStage_3_3.Reset();
				TStage_3_1.ForceTimeOut();
				TStage_3_2.ForceTimeOut();
			}
		}

	}
	else if (TurnCount == 4)
	{
		if (HadEatenFood == false)
		{
			TStage_4_1.Reset();
			TStage_4_2.ForceTimeOut();
		}
		else if (HadEatenFood == true)
		{
			TStage_4_2.Reset();
			TStage_4_1.ForceTimeOut();
			//TStage_4_3_1.ForceTimeOut();
		}
	}
	else if (TurnCount == 5)
	{
		if (HadEatenFood == false)
		{
			TStage_5_1.Reset();
			TStage_5_2.ForceTimeOut();
		}
		else if (HadEatenFood == true)
		{
			TStage_5_2.Reset();
			TStage_5_1.ForceTimeOut();
		}
	}
}

//4방향 블래스터
void GameLevel::MakeBlaster4()
{
	//4방향 블레스터
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_0.txt",
		Color::White, Vector2(60, 0), "GasterBlaster_0"));
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_90.txt",
		Color::White, Vector2(20, 15), "GasterBlaster_90"));
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_270.txt",
		Color::White, Vector2(80, 20), "GasterBlaster_-90"));
	AddActor(new Monster("../Assets/Actor/Stage1/gasterblader_stage1_4_test.txt",
		Color::White, Vector2(49, 19), "GasterBlaster"));//얜 안움직임
}

void GameLevel::DeleteBlaster4(Monster* monsterActor)
{
	if (monsterActor->CheckTag("GasterBlaster_0") ||
		monsterActor->CheckTag("GasterBlaster_90") ||
		monsterActor->CheckTag("GasterBlaster_-90") ||
		monsterActor->CheckTag("GasterBlaster"))
	{
		monsterActor->Destroy();
	}
}

void GameLevel::Breath4()
{
	AddActor(new BreathActor("../Assets/Actor/Breath/bless90and270_small.txt",
		Color::White, Vector2(45, 15), "breath"));
	AddActor(new BreathActor("../Assets/Actor/Breath/bless0and180_small.txt",
		Color::White, Vector2(50, 14), "breath"));
	AddActor(new BreathActor("../Assets/Actor/Breath/bless0and180_small.txt",
		Color::White, Vector2(60, 14), "breath"));
	AddActor(new BreathActor("../Assets/Actor/Breath/bless90and270_small_down_None.txt",
		Color::White, Vector2(45, 20), "breath"));
}

void GameLevel::MakeXBlaster()
{
	//X자 브레스용 블래스터!
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_45.txt",
		Color::White, Vector2(68, 6), "GasterBlaster_45"));
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_-45.txt",
		Color::White, Vector2(39, 7), "GasterBlaster_-45"));
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_135.txt",
		Color::White, Vector2(68,22), "GasterBlaster")); //얜 안움직일거
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_-135.txt",
		Color::White, Vector2(40,22), "GasterBlaster")); //얜 안움직일거
}

void GameLevel::DeleteXBlaster(Monster* monsterActor)
{
	if (monsterActor->CheckTag("GasterBlaster_45") ||
		monsterActor->CheckTag("GasterBlaster_-45") ||
		monsterActor->CheckTag("GasterBlaster"))
	{
		monsterActor->Destroy();
	}
}

void GameLevel::BreathX()
{
	//X자 브레스
	AddActor(new BreathActor("../Assets/Actor/Breath/doublebless.txt",
		Color::White, Vector2(53, 16), "breath"));
}

void GameLevel::MakeBigBlaster()
{
	//대형 블래스터
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader90.txt",
		Color::White, Vector2(20, 15), "GasterBlaster_Big_Left"));
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader270.txt",
		Color::White, Vector2(80, 15), "GasterBlaster_Big_Right"));
}

void GameLevel::DeleteBigBlaster(Monster* monsterActor)
{
	if (monsterActor->CheckTag("GasterBlaster_Big_Left") ||
		monsterActor->CheckTag("GasterBlaster_Big_Right"))
	{
		monsterActor->Destroy();
	}
}

void GameLevel::BreathBig()
{
	//대형 블레스터 빔
	AddActor(new BreathActor("../Assets/Actor/Breath/bless90and270.txt",
		Color::White, Vector2(45, 17), "breath"));
}

void GameLevel::DeleteBreath(BreathActor* breaths)
{
	if (breaths->CheckTag("breath"))
		breaths->Destroy();
}



