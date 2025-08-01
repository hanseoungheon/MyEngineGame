#pragma once
#include <vector>
#include <iostream>
#include "Actor/Actor.h"

class MultiLine_Actor : public Actor
{
	RTTI_DECLARATIONS(MultiLine_Actor,Actor)

public:
	MultiLine_Actor(const char* filePath, Color color, const
		Vector2& position);

	virtual void Render() override;


private:
	std::vector<std::string> lines;


};