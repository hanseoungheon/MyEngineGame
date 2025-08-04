#include "Player.h"
#include "Engine.h"
#include "Utils/Utils.h"
Player::Player() : Actor("Y",Color::Red,false)
{
	hp = 92;
	SetSortingOrder(1);
	IsTurn = true;
	//���� ��ġ(ȭ���� ����̸鼭 ��¦ �Ʒ���)
	int xPosition = ((Engine::Get().Width()+ LeftSide) / 2);
	int yPosition = Engine::Get().Height() - 1;

	//����
	SetPosition(Vector2(xPosition, yPosition));
}

void Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	JumpTick++;
	//�߷±���
	if (IsGravity && !Input::GetController().GetKey(VK_UP))
	{
		Vector2 playerPosition = GetActorPosition();
		playerPosition.y += 1;
		SetPosition(playerPosition);
		JumpTick = 0;
	}

	//�Է� ó��
	if (Input::GetController().GetKeyDown(VK_ESCAPE))
	{
		//���� ����
		QuitGame();
		return;
	}

	if (Input::GetController().GetKeyDown(VK_SHIFT))
	{
		IsTurn = !IsTurn;
	}

	if (IsTurn)
	{
		if (Input::GetController().GetKey(VK_LEFT))
		{
			Vector2 playerPosition = GetActorPosition();
			playerPosition.x += -1;
			SetPosition(playerPosition);
		}

		if (Input::GetController().GetKey(VK_RIGHT))
		{
			Vector2 playerPosition = GetActorPosition();
			playerPosition.x += 1;
			SetPosition(playerPosition);
		}

		if (Input::GetController().GetKey(VK_UP) && IsGravity == false
			&& JumpTick % 2 == 0)
		{
			Vector2 playerPosition = GetActorPosition();
			playerPosition.y += -1;
			SetPosition(playerPosition);
		}

		if (Input::GetController().GetKey(VK_DOWN) && IsGravity == false
			&& JumpTick % 2 == 0)
		{
			Vector2 playerPosition = GetActorPosition();
			playerPosition.y += 1;
			SetPosition(playerPosition);
		}

		if (Input::GetController().GetKey(VK_UP) && IsGravity == true
			&& JumpTick % 4 == 0)
		{
			Vector2 playerPosition = GetActorPosition();
			playerPosition.y += -1;
			SetPosition(playerPosition);
		}

		if (Input::GetController().GetKeyDown(VK_CONTROL))
		{
			ChangeToIsGravity();
		}
	}

}

void Player::ChangeToIsGravity()
{
	IsGravity = !IsGravity;

	if (IsGravity)
		SetColor(Color::Blue);
	else
		SetColor(Color::Red);
}

bool Player::GetIsTurn() const
{
	return IsTurn;
}

void Player::SetIsTurn(const bool IsTurn)
{
	this->IsTurn = IsTurn;
}

int Player::GetHp() const
{
	return hp;
}

void Player::SetHp(const int hp)
{
	this->hp = hp;
}

