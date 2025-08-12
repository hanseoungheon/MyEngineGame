#include "Block.h"
#include "Utils/Utils.h"
#include "Input.h"
Block::Block(const Vector2& position,const char* Tag) : Actor("[===]",Color::Intensity,position,false,IsString::STR_FALSE)
{
	SetSortingOrder(0);
	if (Tag != nullptr)
	{
		size_t length = strlen(Tag) + 1;
		NameTag = new char[length];
		strcpy_s(NameTag, length, Tag);
	}

	JumpTick = 0;
}
Block::~Block()
{
	if (NameTag != nullptr)
	{
		delete[] NameTag;
	}
}

void Block::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	JumpTick++;

	if (CheckTag("Left") && JumpTick % 2 == 0)
	{
		Vector2 newPosition = actorPosition + Vector2(-1, 0);
		SetPosition(newPosition);
	}

	if (CheckTag("Right") && JumpTick % 2 == 0)
	{
		Vector2 newPosition = actorPosition + Vector2(1, 0);
		SetPosition(newPosition);
	}

	if (Input::GetController().GetKey(VK_NUMPAD6) && JumpTick % 2 == 0)
	{
		Vector2 position = GetActorPosition();
		position.x += 1;
		SetPosition(position);
	}
}

void Block::Render()
{
	Utils::SetConsoleTextColor(color);

	Vector2 pos = GetActorPosition();
}


bool Block::CheckTag(const char* name)
{
	if (NameTag != nullptr)
	{
		if (strcmp(NameTag, name) == 0)
			return true;
	}

	return false;
}