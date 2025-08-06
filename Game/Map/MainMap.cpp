//#include "MainMap.h"
//#include <iostream>
//#include "Actor/Wall_Length.h"
//#include "Actor/Wall_Width.h"
//MainMap::MainMap(const char* fileName)
//{
//
//	sprintf_s(filePath, 256, "../Assets/Map/%s", fileName);
//
//
//}
//
//void MainMap::Rending()
//{
//	FILE* mapFile = nullptr;
//	fopen_s(&mapFile, filePath, "rt");
//
//	//����ó��
//	if (mapFile == nullptr)
//	{
//		std::cout << "Fatal Error : Can not Read Map File\n";
//		__debugbreak();
//		return;
//	}
//
//	//�Ľ� �ϱ� 
//	fseek(mapFile, 0, SEEK_END); //���� �����͸� ���� �ּ��� �� ������ �̵�
//	size_t fileSize = ftell(mapFile); //������ ũ�⸦ ����
//	rewind(mapFile); //�ٽ� ���� �����͸� ���� �ּ��� ���������� �̵�
//
//	//Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�
//	char* buffer = new char[fileSize + 1];
//
//	size_t readSize = fread(buffer, sizeof(char), fileSize, mapFile);
//
//
//	//�迭 ��ȸ�� ���� �ε���
//	int index = 0;
//
//	//���ڿ� ����
//	int size = (int)readSize;
//
//	//��ǥ
//	Vector2 position;
//
//	while (index < size) //�ε����� ���� ���ڿ� ���̸� �Ѿ�� ����
//	{
//		//�� ���� Ȯ��
//		char mapBlock = buffer[index++];
//
//		if (mapBlock == '\n') // ���๮�� ó��
//		{
//			++position.y;
//			position.x = 0;
//
//			continue;
//		}
//
//		switch (mapBlock)
//		{
//		case '|':
//			AddActor(new Wall_Length(position, Color::White));
//			break;
//		case '_':
//			AddActor(new Wall_Width(position, Color::White));
//			break;
//		}
//
//		++position.x;
//	}
//
//	delete[] buffer;
//
//	fclose(mapFile);
//}
//void MainMap::DeleteMap()
//{
//	for (Actor* actor : actors)
//	{
//		if (actor != nullptr)
//		{
//			DestoryActor(actor);
//		}
//	}
//}
