#include "MultiLine_UI.h"
#include "Utils/Utils.h"
#include <Windows.h>
MultiLine_UI::MultiLine_UI(const char* filePath, Color color,
	const Vector2& position,UI_Type type,const char* Tag)
	: Actor("", color, position,true,IsString::STR_TRUE)
{
	SetSortingOrder(1);

	//타입 정의
	UItype = type;

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

		if (length > 0 && (buffer[length -1] == '\n') ||
			buffer[length - 1] == '\r')
		{
			buffer[length] = '\0';
			if (length > 1 && buffer[length - 2] == '\r')
				buffer[length - 2] = '\0';
		}

		lines.emplace_back(buffer);
	}
	fclose(file);

	if (Tag != nullptr)
	{
		size_t length = strlen(Tag) + 1;
		NameTag = new char[length];
		strcpy_s(NameTag, length, Tag);
	}
}

MultiLine_UI::~MultiLine_UI()
{
	if (NameTag != nullptr)
	{
		delete[] NameTag;
	}
}

void MultiLine_UI::Render()
{
	Utils::SetConsoleTextColor(color);

	Vector2 pos = GetActorPosition();

	for (size_t i = 0; i < lines.size(); ++i)
	{
		Utils::SetConsolePosition(Vector2(pos.x, pos.y + static_cast<int>(i)));
		std::cout << lines[i];
	}
}



UI_Type MultiLine_UI::GetUIType()
{
	return UItype;
}

