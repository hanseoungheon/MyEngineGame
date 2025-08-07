#pragma once
#include "Actor/Actor.h"

class Block : public Actor
{
	RTTI_DECLARATIONS(Block,Actor)

public:
	Block(const Vector2& position,const char* Tag);
	~Block();

	virtual void Tick(float DeltaTime) override;


	bool CheckTag(const char* name);
private:
	char* NameTag = nullptr;
};