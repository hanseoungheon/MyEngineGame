#pragma once
#include <vector>
#include <iostream>
#include "Actor/Actor.h"

enum class UI_Type : int
{
	FIGHT = 0,
	ACTOR = 1,
	ITEM = 2,
	MERCY = 3,
	NONE = 4,
};

class MultiLine_UI : public Actor
{
	RTTI_DECLARATIONS(MultiLine_UI,Actor)

public:
	MultiLine_UI(const char* filePath, Color color, const
		Vector2& position,UI_Type type,const char * Tag = "default");

	virtual void Render() override;

	UI_Type GetUIType();

	char* GetTag() const;

private:
	std::vector<std::string> lines;

	UI_Type UItype;

	char* NameTag = nullptr;
};