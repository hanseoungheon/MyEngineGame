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

	void ChangeToIsGravity();

	bool GetIsTurn() const;
	void SetIsTurn(bool IsTurn);

	int GetHp() const;
	void SetHp(const int hp);

	bool GetIsMoving() const;

	void SwitchTurn();
private:
	int hp;
	Color PlayerColor = Color::Red;
	bool IsTurn = true; //샌즈랑 전투중인 턴인지?
	bool IsGravity = false; //파란색(중력적용) 상태인지?
	int JumpTick = 0;
	bool IsMoving = false;
	int TestMoving;
};