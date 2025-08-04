#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/MultiLine_Actor.h"
#include "Actor/Wall_Length.h"
#include "Actor/Wall_Width.h"
#include <Windows.h>
#include <iostream>

GameLevel::GameLevel()
{
	//�÷��̾� �� ���� ����
	ReadMapFile("map.txt");

	//���� ������
	AddActor(new MultiLine_Actor("../Assets/sans_unicode.txt", 
		Color::White, Vector2(48, 0)));
	
	//�÷��̾� ������
	AddActor(new Player());
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

