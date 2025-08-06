#pragma once
#include <vector>
#include <iostream>
#include "Actor/Actor.h"

class MultiLine_Actor : public Actor
{
	RTTI_DECLARATIONS(MultiLine_Actor,Actor)

public:
	MultiLine_Actor(const char* filePath, Color color, const
		Vector2& position,const char * Tag = "default");

	virtual void Tick(float DeltaTime) override;

	virtual void Render() override;

	virtual void SetPosition(const Vector2& newPosition) override;

	char* GetTag() const;

	bool CheckTag(const char* name);

private:
	std::vector<std::string> lines;
	char* NameTag = nullptr;
	//int checkWidth;
	int JumpTick;
};