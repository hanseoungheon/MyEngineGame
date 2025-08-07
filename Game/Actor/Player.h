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
	bool IsTurn = true; //����� �������� ������?
	bool IsGravity = false; //�Ķ���(�߷�����) ��������?
	int JumpTick = 0;
	bool IsMoving = false;
	int TestMoving;
};