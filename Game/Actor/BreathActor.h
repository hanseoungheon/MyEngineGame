#pragma once
#pragma once
#include <vector>
#include <iostream>
#include "Actor/Actor.h"

class BreathActor : public Actor
{
	RTTI_DECLARATIONS(BreathActor, Actor)

public:
	BreathActor(const char* filePath, Color color, const
		Vector2& position, const char* Tag = "default");

	virtual void Tick(float DeltaTime) override;

	virtual void Render() override;

	virtual void SetPosition(const Vector2& newPosition) override;

	char* GetTag() const;

	bool CheckTag(const char* name);


private:
	std::vector<std::string> lines;
	char* NameTag = nullptr;
	//int checkWidth;

};