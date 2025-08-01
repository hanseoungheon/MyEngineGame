#pragma once
#include "Actor/Actor.h"

//기능
//좌 우 상 하 이동 끝

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player();

	virtual void Tick(float DeltaTime) override;

private:
	bool IsTurn = true; //샌즈랑 전투중인 턴인지?
};