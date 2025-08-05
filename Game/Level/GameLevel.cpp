#include "GameLevel.h"

#include "Actor/Player.h"
#include "Actor/Monster.h"
#include "Actor/MultiLine_Actor.h"
#include "Actor/Wall_Length.h"
#include "Actor/Wall_Width.h"


#include "UI/Stat_UI.h"

#include "Input.h"
#include <Windows.h>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

GameLevel::GameLevel()
{
	SetConsoleTitle(L"♥ UnderTale");
	//플레이어 맵 파일 리딩
	ReadMapFile("map.txt");

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
	AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt", 
		Color::White, Vector2(70, 18),"Sans_Bone"));
	AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt", 
		Color::White, Vector2(71, 18),"Sans"));
	AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt", 
		Color::White, Vector2(72, 18),"Sans"));
	AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt", 
		Color::White, Vector2(73, 18),"Sans"));
	AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt", 
		Color::White, Vector2(74, 18),"Sans"));
	
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
	Super::BeginPlay();	SetConsoleOutputCP(CP_UTF8);
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

	if (Input::GetController().GetKeyDown(VK_CONTROL))
	{
		std::cout << "Working?";
		levelTimer.SetTargetTime(2.0f);
		levelTimer.Reset();
	}

	if (levelTimer.Update(DeltaTime))
	{
		for (Actor* actor : actors) {
			if (auto* player = actor->As<Player>()) {
				player->ChangeToIsGravity();
			}
		}
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
	else if(UIcontroller == 2 && (mainUI->GetUIType() == UI_Type::ACTOR)) // ACT
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

void GameLevel::LevelTest(float DeltaTime)
{
	levelTimer.Tick(DeltaTime);

	if (!levelTimer.IsTimeOut())
	{
		return;
	}

	/*levelTimer.Reset();*/

	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();

		if (player != nullptr)
		{
			player->ChangeToIsGravity();
		}
	}
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
}

void GameLevel::UIController()
{
	//플레이어가 턴인지 가져와서 레벨에 저장

	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();

		if (player != nullptr)
		{
			PlayerIsTurn = player->GetIsTurn();
			PlayerHp = player->GetHp();
		}

		//플레이어가 턴이 아닐때 UI조작하게 설정
		if (PlayerIsTurn == false)
		{
			MultiLine_UI* mainUI = actor->As<MultiLine_UI>();

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
		//if (statUI != nullptr && statUI->GetTag() == 40 + 12)
		//{
		//	if (PlayerHp > 92)
		//		statUI->SetColor(Color::Yellow);
		//	else
		//		statUI->SetColor(Color::Red);
		//}

		//if (statUI != nullptr && statUI->GetTag() == 40 + 11)
		//{
		//	if (PlayerHp > 82)
		//		statUI->SetColor(Color::Yellow);
		//	else
		//		statUI->SetColor(Color::Red);
		//}
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
	for (Actor* actor : actors)
	{
		MultiLine_Actor* EnemyObject = actor->As<MultiLine_Actor>();

		if (EnemyObject != nullptr) //적 오브젝트 발견
		{
			EnemyObject_Actor.emplace_back(EnemyObject); // 배열에 추가
			continue;
		}

		if (player == nullptr) //플레이어를 못찾았을시
		{
			player = actor->As<Player>(); // 찾기
		}
	}

	//적 오브젝트를 담은 배열의 크기가 0이거나 플레이어를 못찾았을시
	if (EnemyObject_Actor.size() == 0 || !player)
	{
		return;
	}

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
}

