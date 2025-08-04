#include "GameLevel.h"

#include "Actor/Player.h"
#include "Actor/MultiLine_Actor.h"
#include "Actor/Wall_Length.h"
#include "Actor/Wall_Width.h"


#include "UI/Stat_UI.h"

#include "Input.h"
#include <Windows.h>
#include <iostream>

GameLevel::GameLevel()
{
	SetConsoleTitle(L"�� UnderTale");
	//�÷��̾� �� ���� ����
	ReadMapFile("map.txt");

	//���� ������
	AddActor(new MultiLine_Actor("../Assets/sans_unicode.txt", 
		Color::White, Vector2(48, 0)));
	
	//�÷��̾� ������
	AddActor(new Player());

	//UI
	//���� UI
	AddActor(new MultiLine_UI("../Assets/UI/fight.txt",
		Color::Yellow, Vector2(39, 25),UI_Type::FIGHT));
	//�ൿ UI
	AddActor(new MultiLine_UI("../Assets/UI/act.txt",
		Color::Yellow, Vector2(49, 25),UI_Type::ACTOR));
	//������ UI
	AddActor(new MultiLine_UI("../Assets/UI/item.txt",
		Color::Yellow, Vector2(59, 25),UI_Type::ITEM));
	//�ں� UI
	AddActor(new MultiLine_UI("../Assets/UI/mercy.txt",
		Color::Yellow, Vector2(69, 25),UI_Type::MERCY));

	//ĳ���� ���� UI
	AddActor(new Stat_UI("CHARA",Color::White,Vector2(33,23)));
	AddActor(new Stat_UI("LV19",Color::White,Vector2(40,23)));
	AddActor(new Stat_UI("HP ||||||||||||",Color::White,Vector2(46,23)));
	AddActor(new Stat_UI("KR",Color::White,Vector2(62,23)));
	AddActor(new Stat_UI("92 / 92",Color::White,Vector2(65,23)));

	//for (Actor* actor : actors)
	//{
	//	Player* player = actor->As<Player>();
	//	player->SetHp(92);	
	//}

	UIcontroller = 1;
	//testUImode = false;
}

GameLevel::~GameLevel()
{
	
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

	//�׽�Ʈ �뵵
	//std::cout << UIcontroller;
	
	//�÷��̾ ������ �����ͼ� ������ ����
	for (Actor* actor : actors)
	{
		Player* player = actor->As<Player>();

		if (player != nullptr)
		{
			PlayerIsTurn = player->GetIsTurn();
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
	}

	if (!PlayerIsTurn &&Input::GetController().GetKeyDown(VK_LEFT))
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

void GameLevel::SpawnEnemies(float DeltaTime)
{
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
}

void GameLevel::ProcessCollisionPlayerAndEnemyObject()
{
}

