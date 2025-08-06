#include "Speech_UI.h"
#include "Utils/Utils.h"
#include <Windows.h>

Speech_UI::Speech_UI(const char* filePath, Color color, const Vector2& position)
	:Actor("", color, position, true, IsString::STR_TRUE)
{
	SetSortingOrder(1);

	//타입 정의

	FILE* file = nullptr;
	fopen_s(&file, filePath, "rt");

	if (file == nullptr)
	{
		std::cout << "FatalError : Can not Read File\n";
		__debugbreak();
		return;
	}

	char buffer[4000] = {};

	while (fgets(buffer, sizeof(buffer), file))
	{
		size_t length = strlen(buffer);

		if (length > 0 && (buffer[length - 1] == '\n') ||
			buffer[length - 1] == '\r')
		{
			buffer[length] = '\0';
			if (length > 1 && buffer[length - 2] == '\r')
				buffer[length - 2] = '\0';
		}

		lines.emplace_back(buffer);
	}
	fclose(file);
}

void Speech_UI::Render()
{
	Utils::SetConsoleTextColor(color);

	Vector2 pos = GetActorPosition();

	for (size_t i = 0; i < lines.size(); ++i)
	{
		Utils::SetConsolePosition(Vector2(pos.x, pos.y + static_cast<int>(i)));
		std::cout << lines[i];
	}
}

void Speech_UI::SayTalking(const char* say, Vector2 position,DWORD talkSpeed)
{
	SetConsoleOutputCP(949);
	Vector2 StartPosition = actorPosition + position;
	Vector2 cursor = StartPosition;

	Utils::SetConsolePosition(cursor);
	//const char* say1 = "정말 아름다운";
	//char say2[] = "날이야";
	int lineoffset = 0;
	int length = static_cast<int>(strlen(say) + 1);
	for (int i = 0; i < length; i++)
	{
		if (say[i] == '\n')
		{
			lineoffset++;
			cursor = Vector2(StartPosition.x, StartPosition.y + lineoffset);
			Utils::SetConsolePosition(cursor);
			continue;
		}
		std::cout << say[i];
		Sleep(talkSpeed);
	}
	//Utils::Setconsoleposition(actorposition + vector2(3,3));
	//for (int i = 0; i < 7; i++)
	//{
	//	std::cout << say2[i];
	//	sleep(100);
	//}
	Sleep(500);
	system("cls");
	SetConsoleOutputCP(CP_UTF8);
}

void Speech_UI::BlackOut()
{
	system("cls");
	Sleep(1000);
}

//void Speech_UI::