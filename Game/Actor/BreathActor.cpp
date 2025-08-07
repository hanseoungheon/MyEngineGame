#include "BreathActor.h"
#include "Utils/Utils.h"
#include "Input.h"

BreathActor::BreathActor(const char* filePath, Color color, 
	const Vector2& position, const char* Tag)
	: Actor("", color, position, false, IsString::STR_TRUE)
{
	SetSortingOrder(1);
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
		width += length;
	}
	fclose(file);

	if (Tag != nullptr)
	{
		size_t length = strlen(Tag) + 1;
		NameTag = new char[length];
		strcpy_s(NameTag, length, Tag);
	}

	width = width / static_cast<int>(lines.size());

	if (width < 1)
		width = 1;

	height = static_cast<int>(lines.size());
	//¾ÈÁö¿öÁü? 
	JumpTick = 0;
}

BreathActor::~BreathActor()
{
	if (NameTag != nullptr)
	{
		delete[] NameTag;
	}
}

void BreathActor::Tick(float DeltaTime)
{
	if (Input::GetController().GetKey(VK_NUMPAD9))
	{
		IsVisible = !IsVisible;
	}
	JumpTick++;
}

void BreathActor::Render()
{
	Utils::SetConsoleTextColor(color);

	Vector2 pos = GetActorPosition();

	for (size_t i = 0; i < lines.size(); ++i)
	{
		Utils::SetConsolePosition(Vector2(pos.x, pos.y + static_cast<int>(i)));
		std::cout << lines[i];
	}
}

void BreathActor::SetPosition(const Vector2& newPosition)
{
	return;
}

char* BreathActor::GetTag() const
{
	return NameTag;
}

bool BreathActor::CheckTag(const char* name)
{
	if (NameTag != nullptr)
	{
		if (std::strcmp(NameTag, name) == 0)
			return true;
	}

	return false;
}



