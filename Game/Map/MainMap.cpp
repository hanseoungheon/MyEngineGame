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
//	//예외처리
//	if (mapFile == nullptr)
//	{
//		std::cout << "Fatal Error : Can not Read Map File\n";
//		__debugbreak();
//		return;
//	}
//
//	//파싱 하기 
//	fseek(mapFile, 0, SEEK_END); //파일 포인터를 파일 주소의 끝 값으로 이동
//	size_t fileSize = ftell(mapFile); //파일의 크기를 저장
//	rewind(mapFile); //다시 파일 포인터를 파일 주소의 시작점으로 이동
//
//	//확인한 파일 크기를 활용해 버퍼 할당
//	char* buffer = new char[fileSize + 1];
//
//	size_t readSize = fread(buffer, sizeof(char), fileSize, mapFile);
//
//
//	//배열 순회를 위한 인덱스
//	int index = 0;
//
//	//문자열 길이
//	int size = (int)readSize;
//
//	//좌표
//	Vector2 position;
//
//	while (index < size) //인덱스가 파일 문자열 길이를 넘어가면 종료
//	{
//		//맵 문자 확인
//		char mapBlock = buffer[index++];
//
//		if (mapBlock == '\n') // 개행문자 처리
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
