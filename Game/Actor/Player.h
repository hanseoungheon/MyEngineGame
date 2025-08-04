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
private:
	Color PlayerColor = Color::Red;
	bool IsTurn = true; //����� �������� ������?
	bool IsGravity = false; //�Ķ���(�߷�����) ��������?
	int JumpTick = 0;
};