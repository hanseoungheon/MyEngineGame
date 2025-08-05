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
	SetConsoleTitle(L"�� UnderTale");
	//�÷��̾� �� ���� ����
	ReadMapFile("map.txt");

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
	//���� UI
	AddActor(new MultiLine_UI("../Assets/UI/fight.txt",
		Color::Yellow, Vector2(39, 25),UI_Type::FIGHT,"MainUI"));
	//�ൿ UI
	AddActor(new MultiLine_UI("../Assets/UI/act.txt",
		Color::Yellow, Vector2(49, 25),UI_Type::ACTOR,"MainUI"));
	//������ UI
	AddActor(new MultiLine_UI("../Assets/UI/item.txt",
		Color::Yellow, Vector2(59, 25),UI_Type::ITEM,"MainUI"));
	//�ں� UI
	AddActor(new MultiLine_UI("../Assets/UI/mercy.txt",
		Color::Yellow, Vector2(69, 25),UI_Type::MERCY,"MainUI"));

	//ĳ���� ���� UI
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
}

void GameLevel::UIController()
{
	//�÷��̾ ������ �����ͼ� ������ ����

	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();

		if (player != nullptr)
		{
			PlayerIsTurn = player->GetIsTurn();
			PlayerHp = player->GetHp();
		}

		//�÷��̾ ���� �ƴҶ� UI�����ϰ� ����
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

		if (EnemyObject != nullptr) //�� ������Ʈ �߰�
		{
			EnemyObject_Actor.emplace_back(EnemyObject); // �迭�� �߰�
			continue;
		}

		if (player == nullptr) //�÷��̾ ��ã������
		{
			player = actor->As<Player>(); // ã��
		}
	}

	//�� ������Ʈ�� ���� �迭�� ũ�Ⱑ 0�̰ų� �÷��̾ ��ã������
	if (EnemyObject_Actor.size() == 0 || !player)
	{
		return;
	}

	//�� ������Ʈ�����͸� ���ÿ� �Ҵ��� �� ���� �Ҵ��
	// �� ������Ʈ�� ���� �迭�� �ּҸ� ������ ��ȯ�ϸ� Ž���ϱ�
	for (auto* EnemyObject : EnemyObject_Actor)
	{
		//�浹�ߴٸ�?
		if (player->GetIsTurn() && player->TestIntersect(EnemyObject))
		{
			
			//std::cout << "IsDameged";
			int PlayerCurrentHp = player->GetHp();
			player->SetHp(PlayerCurrentHp - 1);
		}
	}
}

