#include "GameLevel.h"
#include "Engine.h"
#include "Map/MainMap.h"

//#include "Stage/Stage1.cpp"
 
#include "Actor/Player.h"
#include "Actor/Monster.h"
#include "Actor/MultiLine_Actor.h"
#include "Actor/Wall_Length.h"
#include "Actor/Wall_Width.h"
#include "Actor/ActorWall_Length.h"
#include "Actor/ActorWall_Width.h"
#include  "Actor/BreathActor.h"
#include "UI/Stat_UI.h"
#include "UI/Speech_UI.h"

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
	PlaySound(L"../Assets/Sounds/sans_megalovania.wav", 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//PlaySound(L"../Assets/Sounds/Sans-Talking-_Sound-Effect_.wav", 0, SND_FILENAME | SND_ASYNC);
	//mciSendStringW(
	//	L"open \"../Assets/Sounds/sans_megalovania.wav\" type waveaudio alias bgm shareable",
	//	NULL, 0, NULL);
	//mciSendStringW(L"play bgm from 0 repeat", NULL, 0, NULL);

	//// 효과음용
	//mciSendStringW(
	//	L"open \"../Assets/Sounds/Sans-Talking-_Sound-Effect_.wav\" type waveaudio alias se shareable",
	//	NULL, 0, NULL);
	//mciSendStringW(L"play se from 0", NULL, 0, NULL);

	//플레이어 렌더링
	AddActor(new Player());

	//샌즈 렌더링
	AddActor(new Monster("../Assets/Actor/sans_unicode_3.txt", 
		Color::White, Vector2(50, 0),"Sans"));

	//AddActor(new Monster("../Assets/Actor/gasterblader0.txt", 
	//	Color::White, Vector2(0, 0),"GasterBlaster"));

	AddActor(new Monster("../Assets/Actor/bless0and180.txt", 
		Color::White, Vector2(0, 6),"breath"));
	AddActor(new Monster("../Assets/Actor/bless90and270.txt", 
		Color::White, Vector2(20, 15),"breath"));

	//AddActor(new MultiLine_Actor("../Assets/Actor/bless90and270.txt",
	//	Color::White, Vector2(0, 12),"Sans"));


	//AddActor(new BreathActor("../Assets/Actor/bless45.txt",
	//	Color::White, Vector2(42, 12), "Sans"));
	//AddActor(new BreathActor("../Assets/Actor/bless135.txt",
	//	Color::White, Vector2(42, 12), "Sans"));
	//AddActor(new BreathActor("../Assets/Actor/bless135.txt",
	//	Color::White, Vector2(42, 12), "Sans"));
	//for (int i = 51; i < 66; i++)
	//{
	//	AddActor(new ActorWall_Width(Vector2(i, 20), Color::Orange));
	//}
;

	//AddActor(new MultiLine_Actor("../Assets/Actor/Stage1/bone_array_1.txt", 
	//	Color::White, Vector2(51, 16),"Sans_Bone"));
	//AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt", 
	//	Color::White, Vector2(71, 18),"Sans_Bone"));
	//AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt", 
	//	Color::White, Vector2(72, 18),"Sans_Bone"));
	//AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt", 
	//	Color::White, Vector2(73, 18),"Sans_Bone"));
	//AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt", 
	//	Color::White, Vector2(74, 18),"Sans_Bone"));
	
	//AddActor(new Wall_Width(Vector2(0, 0),Color::Red));
	//UI
	//공격 UI
	AddActor(new MultiLine_UI("../Assets/UI/fight.txt",
		Color::Yellow, Vector2(39, 25),UI_Type::FIGHT,"MainUI"));
	//행동 UI
	AddActor(new MultiLine_UI("../Assets/UI/act.txt",
		Color::Yellow, Vector2(49, 25),UI_Type::ACTOR,"MainUI"));
	//아이템 UI
	AddActor(new MultiLine_UI("../Assets/UI/item.txt",
		Color::Yellow, Vector2(59, 25),UI_Type::ITEM,"MainUI"));
	//자비 UI
	AddActor(new MultiLine_UI("../Assets/UI/mercy.txt",
		Color::Yellow, Vector2(69, 25),UI_Type::MERCY,"MainUI"));

	//말풍선
	AddActor(new Speech_UI("../Assets/UI/speech_bubble.txt",Color::White,
		Vector2(66,2)));


	//캐릭터 상태 UI
	AddActor(new Stat_UI("CHARA", Color::White, Vector2(33, 23),'C'));
	AddActor(new Stat_UI("LV19",Color::White,Vector2(40,23),'L'));
	AddActor(new Stat_UI("HP",Color::White,Vector2(46,23)));

	for (int i = 1; i <= 12; i++)
		AddActor(new Stat_UI("|", Color::Yellow, Vector2(47 + i, 23),40 + i));

	AddActor(new Stat_UI("KR",Color::White,Vector2(62,23)));
	AddActor(new Stat_UI("92", Color::White, Vector2(65, 23), 'H'));
	AddActor(new Stat_UI("/ 92",Color::White,Vector2(68,23)));

	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();
		player->SetHp(92);	
	}

	UIcontroller = 1;
	//testUImode = false;
	//levelTimer.SetTargetTime(2.0f);


	//인트로
	IntroTimer.SetTargetTime(1.0f);
	BurningToHell.SetTargetTime(1.0f);

	//스테이지1
	TStage_1_1.SetTargetTime(1.0f);
	TStage_1_2.SetTargetTime(0.8f);
	TStage_1_3.SetTargetTime(0.5f);
	TStage_1_4.SetTargetTime(0.5f);
	TStage_1_5.SetTargetTime(0.5f);
	TStage_1_5_Array.SetTargetTime(0.3f);

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

	//일단은 말풍선 안보이게 하는거 포기
	//for (Actor* actor : actors)
	//{
	//	Speech_UI* speech_UI = actor->As<Speech_UI>();

	//	if (speech_UI != nullptr)
	//		speech_UI->SetIsVisible(false);
	//}

	//FILE* rendering_SANS = nullptr;
	//fopen_s(&rendering_SANS, "../Assets/sans_unicode.txt", "rt");

	//if (rendering_SANS == nullptr)
	//{
	//	std::cout << "Fatal_Error: Cannot Read FILE -> sans_unicode.txt\n";
	//}

}

void GameLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//LevelTest(DeltaTime);

	//if (Input::GetController().GetKeyDown(VK_CONTROL))
	//{
	//	IsMap = !IsMap;
	//	if (IsMap)
	//	{
	//		ReadMapFile("map_small.txt");
	//	}
	//	else
	//	{
	//		DeleteMap();
	//	}
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

	if (Input::GetController().GetKeyDown(VK_NUMPAD2))
	{
		Engine::Get().LoadEngineSetting("EngineSettings_SmallMap.txt");
	}


	//Stage1 타이머
	if (!IntroTimer.IsTimeOut())
	{
		Intro(DeltaTime);
	}
	else if(!BurningToHell.IsTimeOut())
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

	//테스트 용도
	//std::cout << UIcontroller;
	UIController();

	ProcessCollisionPlayerAndEnemyObject();
}

void GameLevel::ControllMainUI(MultiLine_UI* mainUI)
{
	//1:FIGHT, 2:ACT, 3:ITEM, 4:MERCY

	mainUI->SetColor(Color::Yellow);

	if (UIcontroller == 1 && (mainUI->GetUIType() == UI_Type::FIGHT)) //FIGHT
	{
		mainUI->SetColor(Color::Orange);
	}
	else if (UIcontroller == 2 && (mainUI->GetUIType() == UI_Type::ACTOR)) // ACT
	{
		mainUI->SetColor(Color::Orange);
	}
	else if (UIcontroller == 3 && (mainUI->GetUIType() == UI_Type::ITEM)) //ITEM
	{
		mainUI->SetColor(Color::Orange);
	}
	else if (UIcontroller == 4 && (mainUI->GetUIType() == UI_Type::MERCY)) //MERCY
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

	system("cls");
}

void GameLevel::CheckPlayerGravity()
{
	for (Actor* actor : actors)
	{
		if (auto* player = actor->As<Player>())
			player->ChangeToIsGravity();
	}
}

void GameLevel::UIController()
{
	//플레이어가 턴인지 가져와서 레벨에 저장

	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();
		MultiLine_UI* mainUI = actor->As<MultiLine_UI>();
		if (player != nullptr)
		{
			PlayerIsTurn = player->GetIsTurn();
			PlayerHp = player->GetHp();
		}

		//if (mainUI != nullptr && mainUI->GetUIType() == UI_Type::SPEECH)
		//{
		//	mainUI->SetColor(Color::White);
		//	continue;
		//}

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

	if (!PlayerIsTurn && Input::GetController().GetKeyDown(VK_LEFT))
	{
		if (UIcontroller < 1)
			return;

		UIcontroller--;
	}

	if (!PlayerIsTurn && Input::GetController().GetKeyDown(VK_RIGHT))
	{
		if (UIcontroller > 3)
			return;

		UIcontroller++;
	}
}

void GameLevel::ProcessCollisionPlayerAndEnemyObject()
{
	Player* player = nullptr;

	std::vector<MultiLine_Actor*>EnemyObject_Actor;
	std::vector<Monster*>Monster_Actor;

	for (Actor* actor : actors)
	{
		MultiLine_Actor* EnemyObject = actor->As<MultiLine_Actor>();
		Monster* MonsterObject = actor->As<Monster>();

		if (EnemyObject != nullptr) //적 오브젝트 발견
		{
			EnemyObject_Actor.emplace_back(EnemyObject); // 배열에 추가
			continue;
		}

		if (MonsterObject != nullptr && MonsterObject->CheckTag("breath"))// && MonsterObject->GetTag() == "breath"
		{
			Monster_Actor.emplace_back(MonsterObject);
			continue;
		}

		if (player == nullptr) //플레이어를 못찾았을시
		{
			player = actor->As<Player>(); // 찾기
		}
	}

	//적 오브젝트를 담은 배열의 크기가 0이거나 플레이어를 못찾았을시
	if (EnemyObject_Actor.size() == 0 && Monster_Actor.size() == 0 || !player)
	{
		return;
	}

	//if (Monster_Actor.size() == 0 || !player)
	//{
	//	return;
	//}

	//적 오브젝트포인터를 스택에 할당한 후 힙에 할당된
	// 적 오브젝트를 담은 배열의 주소를 가르켜 순환하며 탐색하기
	for (auto* EnemyObject : EnemyObject_Actor)
	{
		//충돌했다면?
		if (player->GetIsTurn() && player->TestIntersect(EnemyObject))
		{
			
			//std::cout << "IsDameged";
			int PlayerCurrentHp = player->GetHp();
			player->SetHp(PlayerCurrentHp - 1);
		}
	}

	for (auto* MonsterObject : Monster_Actor)
	{
		if (player->GetIsTurn() && player->TestIntersect(MonsterObject))
		{
			int PlayerCurrentHp = player->GetHp();
			player->SetHp(PlayerCurrentHp - 1);
		}
	}
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

//void GameLevel::LevelTest(float DeltaTime)
//{
//	levelTimer.Tick(DeltaTime);
//
//	if (!levelTimer.IsTimeOut())
//	{
//		return;
//	}
//
//	/*levelTimer.Reset();*/
//
//	for (Actor* actor : actors)
//	{
//		Player* player = actor->As<Player>();
//
//		if (player != nullptr)
//		{
//			player->ChangeToIsGravity();
//		}
//	}
//
//}

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
				("오늘은 정말 \n아름다운날이야", Vector2(3, 2), 100,true);
				Sleep(100);
				speechUI->SayTalking
				("새들은 지저귀고 \n꽃들은 피어나고", Vector2(3, 2), 100,true);
				Sleep(100);
				speechUI->SayTalking
				("이런날엔, 너같은\n꼬마들은...", Vector2(3, 2), 100,true);
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
				("지옥에서 \n불타야해", Vector2(3, 2), 200,false);
			}
		}
	}
	TStage_1_1.Reset();
}



