#pragma once
#include "Actor/Actor.h"

//���
//�� �� �� �� �̵� ��

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player();

	virtual void Tick(float DeltaTime) override;

private:
	bool IsTurn = true; //����� �������� ������?
};