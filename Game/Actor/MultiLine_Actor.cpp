#include "MultiLine_Actor.h"
#include "Utils/Utils.h"
#include "Input.h"
#include "Engine.h"
MultiLine_Actor::MultiLine_Actor(const char* filePath, Color color,
	const Vector2& position,const char* Tag)
	: Actor("", color, position,false,IsString::STR_TRUE)
{
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
		if (length > 0 && 
			(buffer[length -1] == '\n' || buffer[length - 1] == '\r'))
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

	for (auto& line : lines) {
		while (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
			line.pop_back();
		}
	}

	JumpTick = 0;
}

MultiLine_Actor::~MultiLine_Actor()
{
	if (NameTag != nullptr)
	{
		delete[] NameTag;
	}
}


void MultiLine_Actor::Tick(float DeltaTime)
{
	if (actorPosition.x < 40 || actorPosition.x > Engine::Get().Width() - width + 2)
	{
		Destroy();
		return;
	}

	//Á¡ÇÁÆ½
	JumpTick++;

	if (Input::GetController().GetKey(VK_NUMPAD4) && JumpTick % 2 == 0)
	{
		Vector2 newPosition = actorPosition + Vector2(-1, 0);
		SetPosition(newPosition);
	}

	if (Input::GetController().GetKey(VK_NUMPAD5))
	{
		Destroy();
	}
	if (Input::GetController().GetKey(VK_NUMPAD6) && JumpTick % 2 == 0)
	{
		Vector2 newPosition = actorPosition + Vector2(1, 0);
		SetPosition(newPosition);
	}

	if ((CheckTag("Right") || CheckTag("BlueBoneRight")) && JumpTick % 3 == 0)
	{
		Vector2 newPosition = actorPosition + Vector2(1, 0);
		SetPosition(newPosition);
	}
	if ((CheckTag("Stick")) && JumpTick % 2 == 0)
	{
		Vector2 newPosition = actorPosition + Vector2(1, 0);
		SetPosition(newPosition);
	}

	if ((CheckTag("Left") || CheckTag("BlueBoneLeft")) && JumpTick % 3 == 0)
	{
		Vector2 newPosition = actorPosition + Vector2(-1, 0);
		SetPosition(newPosition);
	}

	//if (CheckTag("BluBoneLeft") && JumpTick % 3 == 0)
	//{
	//	Vector2 newPosition = actorPosition + Vector2(-1, 0);
	//	SetPosition(newPosition);
	//}

}

void MultiLine_Actor::Render()
{
	Utils::SetConsoleTextColor(color);

	Vector2 pos = GetActorPosition();

	for (size_t i = 0; i < lines.size(); ++i)
	{
		Utils::SetConsolePosition(Vector2(pos.x, pos.y + static_cast<int>(i)));
		std::cout << lines[i];
	}
}

void MultiLine_Actor::SetPosition(const Vector2& newPosition)
{
	Vector2 oldPosition = actorPosition;

	int maxlength = 0;

	for (auto& line : lines)
	{
		int len = static_cast<int>(line.length());

		if (len > maxlength)
			maxlength = len;
	}

	for (int i = 0; i < height; ++i)
	{
		Utils::SetConsolePosition(Vector2((short)oldPosition.x, (short)(oldPosition.y + i)));

		for (int j = 0; j <= maxlength; ++j)
		{
			std::cout << ' ';
		}
	}

	actorPosition = newPosition;
}


char* MultiLine_Actor::GetTag() const
{
	return NameTag;
}

bool MultiLine_Actor::CheckTag(const char* name)
{
	if (NameTag != nullptr)
	{
		if (std::strcmp(NameTag, name) == 0)
			return true;
	}

	return false;
}