#pragma once
#include "Actor/Actor.h"

class ActorWall_Width : public Actor
{
	RTTI_DECLARATIONS(ActorWall_Width, Actor)

public:
	ActorWall_Width(const Vector2& position, Color color);
private:
};

