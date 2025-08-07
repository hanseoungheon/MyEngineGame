#include "Block.h"

Block::Block(const Vector2& position,const char* Tag) : Actor("[===]",Color::Intensity,position,false,IsString::STR_TRUE)
{
	SetSortingOrder(0);
	if (Tag != nullptr)
	{
		size_t length = strlen(Tag) + 1;
		NameTag = new char[length];
		strcpy_s(NameTag, length, Tag);
	}
}

void Block::Tick(float DeltaTime)
{
	if (CheckTag("Left") == true)
	{
		Vector2 newPosition = actorPosition + Vector2(-1, 0);
		SetPosition(newPosition);
	}

	if (CheckTag("Right") == true)
	{
		Vector2 newPosition = actorPosition + Vector2(1, 0);
		SetPosition(newPosition);
	}
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