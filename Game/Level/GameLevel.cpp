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
	SetConsoleTitle(L"�� UnderTale");
	//�÷��̾� �� ���� ����
	ReadMapFile("map_small.txt");
	PlaySound(L"../Assets/Sounds/sans_megalovania.wav", 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//PlaySound(L"../Assets/Sounds/Sans-Talking-_Sound-Effect_.wav", 0, SND_FILENAME | SND_ASYNC);
	//mciSendStringW(
	//	L"open \"../Assets/Sounds/sans_megalovania.wav\" type waveaudio alias bgm shareable",
	//	NULL, 0, NULL);
	//mciSendStringW(L"play bgm from 0 repeat", NULL, 0, NULL);

	//// ȿ������
	//mciSendStringW(
	//	L"open \"../Assets/Sounds/Sans-Talking-_Sound-Effect_.wav\" type waveaudio alias se shareable",
	//	NULL, 0, NULL);
	//mciSendStringW(L"play se from 0", NULL, 0, NULL);

	//�÷��̾� ������
	AddActor(new Player());

	//���� ������
	AddActor(new Monster("../Assets/Actor/sans_unicode_3.txt",
		Color::White, Vector2(50, 0), "Sans"));

	//�Ķ��� �� �����̸� �������� �⺻���� ���̽�ߴ�
	//AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt",
	//	Color::Blue, Vector2(55, 17), "BlueBoneLeft"));
	//AddActor(new MultiLine_Actor("../Assets/Actor/bone.txt",
	//	Color::White, Vector2(64, 17), "Bone"));

	//AddActor(new Monster("../Assets/Actor/Stage1/gasterblader_stage1_4_test.txt",
	//	Color::White, Vector2(60, 18), "GasterBlaster"));
	//AddActor(new Monster("../Assets/Actor/gasterblader_small_0.txt",
	//	Color::White, Vector2(0,0), "GasterBlaster"));

	//4���� ������
	//AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_0.txt",
	//	Color::White, Vector2(60, 0), "GasterBlaster_0"));
	//AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_90.txt",
	//	Color::White, Vector2(20, 15), "GasterBlaster_90"));
	//AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_270.txt",
	//	Color::White, Vector2(80, 20), "GasterBlaster_-90"));
	//AddActor(new Monster("../Assets/Actor/Stage1/gasterblader_stage1_4_test.txt",
	//	Color::White, Vector2(49, 19), "GasterBlaster"));//�� �ȿ�����

	////4���� ��!
	//AddActor(new BreathActor("../Assets/Actor/Breath/bless90and270_small.txt",
	//	Color::White, Vector2(45, 15), "breath"));
	//AddActor(new BreathActor("../Assets/Actor/Breath/bless0and180_small.txt",
	//	Color::White, Vector2(50, 14), "breath"));
	//AddActor(new BreathActor("../Assets/Actor/Breath/bless0and180_small.txt",
	//	Color::White, Vector2(60, 14), "breath"));
	//AddActor(new BreathActor("../Assets/Actor/Breath/bless90and270_small_down_None.txt",
	//	Color::White, Vector2(45, 20), "breath"));


	//X�� �극���� ������!
	//AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_45.txt",
	//	Color::White, Vector2(68, 6), "GasterBlaster_45"));
	//AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_-45.txt",
	//	Color::White, Vector2(39, 7), "GasterBlaster_-45")); //43,11
	//AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_135.txt",
	//	Color::White, Vector2(68,22), "GasterBlaster")); //�� �ȿ����ϰ�
	//AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_-135.txt",
	//	Color::White, Vector2(40,22), "GasterBlaster")); //�� �ȿ����ϰ�


	//X�� �극��
	//AddActor(new BreathActor("../Assets/Actor/doublebless.txt",
	//	Color::White, Vector2(53, 16), "breath"));

	//���� ������
	//AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader90.txt",
	//	Color::White, Vector2(20, 15), "GasterBlaster_Big_Left"));
	//AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader270.txt",
	//	Color::White, Vector2(80, 15), "GasterBlaster_Big_Right"));

	//���� ������ ��
	//AddActor(new BreathActor("../Assets/Actor/Breath/bless90and270.txt",
	//	Color::White, Vector2(45, 16), "breath"));




	//UI
	//���� UI
	AddActor(new MultiLine_UI("../Assets/UI/fight.txt",
		Color::Yellow, Vector2(39, 25), UI_Type::FIGHT, "MainUI"));
	//�ൿ UI
	AddActor(new MultiLine_UI("../Assets/UI/act.txt",
		Color::Yellow, Vector2(49, 25), UI_Type::ACTOR, "MainUI"));
	//������ UI
	AddActor(new MultiLine_UI("../Assets/UI/item.txt",
		Color::Yellow, Vector2(59, 25), UI_Type::ITEM, "MainUI"));
	//�ں� UI
	AddActor(new MultiLine_UI("../Assets/UI/mercy.txt",
		Color::Yellow, Vector2(69, 25), UI_Type::MERCY, "MainUI"));

	//��ǳ��
	AddActor(new Speech_UI("../Assets/UI/speech_bubble.txt", Color::White,
		Vector2(66, 2)));


	//ĳ���� ���� UI
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
		player->SetHp(92);
	}

	UIcontroller = 1;
	//testUImode = false;
	//levelTimer.SetTargetTime(2.0f);


	//��Ʈ��
	IntroTimer.SetTargetTime(1.0f);
	BurningToHell.SetTargetTime(1.0f);

	//��������1
	TStage_1_1.SetTargetTime(1.0f);
	TStage_1_2.SetTargetTime(0.5f);
	TStage_1_3.SetTargetTime(0.5f);
	TStage_1_4.SetTargetTime(0.5f);
	TStage_1_5.SetTargetTime(0.5f);
	TStage_1_5_Array.SetTargetTime(0.3f);
	TStage_1_6.SetTargetTime(0.5f);
	TStage_1_7.SetTargetTime(0.5f); //4�� �극�� ����
	TStage_1_8.SetTargetTime(0.5f); //4�ں극�� ����
	TStage_1_9.SetTargetTime(0.5f); //x�ں극�� ����
	TStage_1_10.SetTargetTime(0.5f); //x�ں극�� ���� �� 4�ں극�� �ٽ�
	TStage_1_11.SetTargetTime(0.5f); //�ʴ��� ������ ����!
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
		Engine::Get().LoadEngineSetting("EngineSettings_LargeMap.txt");
	}


	//Stage1 Ÿ�̸�
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

	//�׽�Ʈ �뵵
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

	//����ó��
	if (mapFile == nullptr)
	{
		std::cout << "Fatal Error : Can not Read Map File\n";
		__debugbreak();
		return;
	}

	//�Ľ� �ϱ� 
	fseek(mapFile, 0, SEEK_END); //���� �����͸� ���� �ּ��� �� ������ �̵�
	size_t fileSize = ftell(mapFile); //������ ũ�⸦ ����
	rewind(mapFile); //�ٽ� ���� �����͸� ���� �ּ��� ���������� �̵�

	//Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�
	char* buffer = new char[fileSize + 1];

	size_t readSize = fread(buffer, sizeof(char), fileSize, mapFile);


	//�迭 ��ȸ�� ���� �ε���
	int index = 0;

	//���ڿ� ����
	int size = (int)readSize;

	//��ǥ
	Vector2 position;

	while (index < size) //�ε����� ���� ���ڿ� ���̸� �Ѿ�� ����
	{
		//�� ���� Ȯ��
		char mapBlock = buffer[index++];

		if (mapBlock == '\n') // ���๮�� ó��
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
	//�÷��̾ ������ �����ͼ� ������ ����

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

		//�÷��̾ ���� �ƴҶ� UI�����ϰ� ����
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
	std::vector<MultiLine_Actor*>BlueEnemyObject_Actor;
	std::vector<BreathActor*>Breath_Actor;

	for (Actor* actor : actors)
	{
		MultiLine_Actor* EnemyObject = actor->As<MultiLine_Actor>();
		BreathActor* BreathObject = actor->As<BreathActor>();

		//���� �Ķ����� �ƴϸ� �׳� �� ���͸���Ʈ����� ������ �Ķ�������Ʈ�� ����
		if (EnemyObject != nullptr && !(EnemyObject->CheckTag("BlueBone"))) //�� ������Ʈ �߰�
		{
			EnemyObject_Actor.emplace_back(EnemyObject); // �迭�� �߰�
			continue;
		}

		if (EnemyObject != nullptr && (EnemyObject->CheckTag("BlueBoneLeft") || EnemyObject->CheckTag("BlueBoneRight"))) //�Ķ��� �� ������Ʈ �߰�
		{
			BlueEnemyObject_Actor.emplace_back(EnemyObject); // �迭�� �߰�
			continue;
		}


		if (BreathObject != nullptr && BreathObject->CheckTag("breath"))// && MonsterObject->GetTag() == "breath"
		{
			Breath_Actor.emplace_back(BreathObject);
			continue;
		}

		if (player == nullptr) //�÷��̾ ��ã������
		{
			player = actor->As<Player>(); // ã��
		}
	}

	//�� ������Ʈ�� ���� �迭�� ũ�Ⱑ 0�̰ų� �÷��̾ ��ã������
	if (EnemyObject_Actor.size() == 0 && Breath_Actor.size() == 0 || !player)
	{
		return;
	}

	//if (Monster_Actor.size() == 0 || !player)
	//{
	//	return;
	//}

	//�� ������Ʈ�����͸� ���ÿ� �Ҵ��� �� ���� �Ҵ��
	// �� ������Ʈ�� ���� �迭�� �ּҸ� ������ ��ȯ�ϸ� Ž���ϱ�
	for (auto* AEnemyObject : EnemyObject_Actor)
	{
		//�浹�ߴٸ�?
		if (player->GetIsTurn() && player->TestIntersect(AEnemyObject))
		{

			int PlayerCurrentHp = player->GetHp();
			player->SetHp(PlayerCurrentHp - 1);
		}
	}

	for (auto* ABlueEnemyObject : BlueEnemyObject_Actor)
	{
		//�浹�ߴٸ�?
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
				("������ ���� \n�Ƹ��ٿ�̾�", Vector2(3, 2), 100, true);
				Sleep(100);
				speechUI->SayTalking
				("������ �����Ͱ� \n�ɵ��� �Ǿ��", Vector2(3, 2), 100, true);
				Sleep(100);
				speechUI->SayTalking
				("�̷�����, �ʰ���\n��������...", Vector2(3, 2), 100, true);
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
				("�������� \n��Ÿ����", Vector2(3, 2), 200, false);
			}
		}
	}
	TStage_1_1.Reset();
}

//4���� ������
void GameLevel::MakeBlaster4()
{
	//4���� ������
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_0.txt",
		Color::White, Vector2(60, 0), "GasterBlaster_0"));
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_90.txt",
		Color::White, Vector2(20, 15), "GasterBlaster_90"));
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_270.txt",
		Color::White, Vector2(80, 20), "GasterBlaster_-90"));
	AddActor(new Monster("../Assets/Actor/Stage1/gasterblader_stage1_4_test.txt",
		Color::White, Vector2(49, 19), "GasterBlaster"));//�� �ȿ�����
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
	//X�� �극���� ������!
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_45.txt",
		Color::White, Vector2(68, 6), "GasterBlaster_45"));
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_-45.txt",
		Color::White, Vector2(39, 7), "GasterBlaster_-45"));
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_135.txt",
		Color::White, Vector2(68,22), "GasterBlaster")); //�� �ȿ����ϰ�
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader_small_-135.txt",
		Color::White, Vector2(40,22), "GasterBlaster")); //�� �ȿ����ϰ�
}

void GameLevel::BreathX()
{
	//X�� �극��
	AddActor(new BreathActor("../Assets/Actor/Breath/doublebless.txt",
		Color::White, Vector2(53, 16), "breath"));
}

void GameLevel::MakeBigBlaster()
{
	//���� ������
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader90.txt",
		Color::White, Vector2(20, 15), "GasterBlaster_Big_Left"));
	AddActor(new Monster("../Assets/Actor/GasterBlaster/gasterblader270.txt",
		Color::White, Vector2(80, 15), "GasterBlaster_Big_Right"));
}

void GameLevel::BreathBig()
{
	//���� ������ ��
	AddActor(new BreathActor("../Assets/Actor/Breath/bless90and270.txt",
		Color::White, Vector2(45, 16), "breath"));
}


