#pragma once
#pragma once
#include <vector>
#include <iostream>
#include "Actor/Actor.h"

class Monster : public Actor
{
	RTTI_DECLARATIONS(Monster, Actor)

public:
	Monster(const char* filePath, Color color, const
		Vector2& position, const char* Tag = "default");

	virtual void Tick(float DeltaTime) override;

	virtual void Render() override;

	virtual void SetPosition(const Vector2& newPosition) override;

	char* GetTag() const;

	bool CheckTag(const char* name);

	bool GetGasterBlasterCanMoving() const;
private:
	std::vector<std::string> lines;
	char* NameTag = nullptr;
	//int checkWidth;
	int JumpTick;
	bool GasterBlasterCanMoving = true;

};