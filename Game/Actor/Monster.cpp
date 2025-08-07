#include "Monster.h"
#include "Utils/Utils.h"
#include "Input.h"
Monster::Monster(const char* filePath, Color color,
	const Vector2& position, const char* Tag)
	: Actor("", color, position, false, IsString::STR_TRUE)
{
	SetSortingOrder(2);
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
	//안지워짐? 
}

void Monster::Tick(float DeltaTime)
{
	if (Input::GetController().GetKey(VK_NUMPAD4))
	{
		actorPosition.x += -1;
		SetPosition(actorPosition);
	}
	if (Input::GetController().GetKey(VK_NUMPAD6))
	{
		actorPosition.x += 1;
		SetPosition(actorPosition);
	}

	++JumpTick;

	//4방향 블래스터
	if (CheckTag("GasterBlaster_0"))
	{
		if (actorPosition.y < 10)
		{
			actorPosition.y += 1;
			SetPosition(actorPosition);
		}
	}

	if (CheckTag("GasterBlaster_-90"))
	{
		if (actorPosition.x > 66)
		{
			actorPosition.x += -2;
			SetPosition(actorPosition);
		}
	}

	if (CheckTag("GasterBlaster_90"))
	{
		if (actorPosition.x < 40)
		{
			actorPosition.x += 2;
			SetPosition(actorPosition);
		}
	}

	//X자 블래스터
	if (CheckTag("GasterBlaster_45"))
	{
		if (!(actorPosition == Vector2(64, 10)))
		{
			actorPosition.x += -1;
			actorPosition.y += 1;
			SetPosition(actorPosition);
		}
		else
		{
			GasterBlasterCanMoving = false;
		}

	}

	if (CheckTag("GasterBlaster_-45"))
	{
		if (!(actorPosition == Vector2(43, 11)))
		{
			actorPosition.x += 1;
			actorPosition.y += 1;
			SetPosition(actorPosition);
		}
	}

	//대형 블래스터 빔
	if (CheckTag("GasterBlaster_Big_Left"))
	{
		if (actorPosition.x < 35)
		{
			actorPosition.x += 1;
			//actorPosition.y += 1;
			SetPosition(actorPosition);
		}
		else
		{
			GasterBlasterCanMoving = false;
		}
	}

	if (CheckTag("GasterBlaster_Big_Right"))
	{
		if (actorPosition.x > 67)
		{
			actorPosition.x += -1;
			SetPosition(actorPosition);
		}
	}

}

void Monster::Render()
{
	Utils::SetConsoleTextColor(color);

	Vector2 pos = GetActorPosition();

	for (size_t i = 0; i < lines.size(); ++i)
	{
		Utils::SetConsolePosition(Vector2(pos.x, pos.y + static_cast<int>(i)));
		std::cout << lines[i];
	}
}

void Monster::SetPosition(const Vector2& newPosition)
{
	return;
}


char* Monster::GetTag() const
{
	return NameTag;
}

bool Monster::CheckTag(const char * name)
{
	if (NameTag != nullptr)
	{
		if (std::strcmp(NameTag, name) == 0)
			return true;
	}

	return false;
}

bool Monster::GetGasterBlasterCanMoving() const
{
	return GasterBlasterCanMoving;
}
