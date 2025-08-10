#include "Player.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include <iostream>
Player::Player() : Actor("Y",Color::Red,Vector2::Zero,false,IsString::STR_FALSE)
{
	hp = 92;
	SetSortingOrder(3);
	IsTurn = true;
	//IsVisible = true;
	//���� ��ġ(ȭ���� ����̸鼭 ��¦ �Ʒ���)
	int xPosition = ((Engine::Get().Width()+ LeftSide) / 2);
	int yPosition = Engine::Get().Height() - 1;

	//����
	SetPosition(Vector2(xPosition, yPosition));
	TestMoving = 0;
	//ChangeToIsGravity();
}

void Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	JumpTick++; //ƽ�� �޾Ƽ� �������� �޾Ƽ� ƽ�� ������ �ϴ� �뵵
	//std::cout << "IsMoving :" << IsMoving;
	//IsOnTheBlock = false;
	

	//�߷±���
	if (IsGravity && !IsOnTheBlock && !Input::GetController().GetKey(VK_UP) && JumpTick % 2 == 0)
	{
		Vector2 playerPosition = GetActorPosition();
		playerPosition = playerPosition + velocity;

		SetPosition(playerPosition);
	}

	//�Է� ó��
	if (Input::GetController().GetKeyDown(VK_ESCAPE))
	{
		//���� ����
		QuitGame();
		return;
	}

	//if (Input::GetController().GetKeyDown(VK_NUMPAD2))
	//{
	//	LeftSide += 11;
	//}

	//if (Input::GetController().GetKeyDown(VK_TAB))
	//{
	//	IsTurn = !IsTurn;
	//	IsVisible = !IsVisible;
	//	Vector2 playerPosition = GetActorPosition();
	//	playerPosition.x++;
	//	SetPosition(playerPosition);
	//	playerPosition.y--;
	//	SetPosition(playerPosition);
	//	playerPosition.x = ((Engine::Get().Width() + LeftSide) / 2 + 1);
	//	playerPosition.y = Engine::Get().Height() - 2;
	//	SetPosition(playerPosition);
	//	//IsGravity = true;
	//	//SetColor(Color::Blue);
	//}	

	if (Input::GetController().GetKey(VK_BACK))
	{
		--hp;
	}

	//if (Input::GetController().GetKey(VK_RETURN))
	//{
	//	hp = 80;
	//}

	if (Input::GetController().GetKey(VK_LBUTTON))
	{
		if (hp < 92)
		{
			++hp;
		}
	}
	//IsMoving = false;
	if (IsTurn)
	{
		//�̵� Ű ����
		if (Input::GetController().GetKey(VK_LEFT) && JumpTick % 6 == 0)
		{
			IsMoving = true;
			Vector2 playerPosition = GetActorPosition();
			playerPosition.x += -1;
			SetPosition(playerPosition);
		}

		if (Input::GetController().GetKey(VK_RIGHT) && JumpTick % 4 == 0)
		{
			IsMoving = true;
			Vector2 playerPosition = GetActorPosition();
			playerPosition.x += 1;
			SetPosition(playerPosition);

		}

		if (Input::GetController().GetKey(VK_UP) && IsGravity == false
			&& JumpTick % 4 == 0)
		{
			IsMoving = true;
			Vector2 playerPosition = GetActorPosition();
			playerPosition.y += -1;
			SetPosition(playerPosition);
		}

		if (Input::GetController().GetKey(VK_DOWN) && IsGravity == false
			&& JumpTick % 4 == 0)
		{
			IsMoving = true;
			Vector2 playerPosition = GetActorPosition();
			playerPosition.y += 1;
			SetPosition(playerPosition);
		}

		if (Input::GetController().GetKey(VK_UP) && IsGravity == true
			&& JumpTick % 6 == 0)
		{
			IsMoving = true;
			Vector2 playerPosition = GetActorPosition();
			playerPosition.y += -1;
			SetPosition(playerPosition);
		}

		if (Input::GetController().GetKeyUp(VK_LEFT))
		{
			IsMoving = false;
		}

		if (Input::GetController().GetKeyUp(VK_RIGHT))
		{
			IsMoving = false;
		}

		if (Input::GetController().GetKeyUp(VK_UP))
		{
			IsMoving = false;
		}

		if (Input::GetController().GetKeyUp(VK_DOWN))
		{
			IsMoving = false;
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

void Player::SettingToGravity(bool SetGravity)
{
	IsGravity = SetGravity;

	if (IsGravity)
		SetColor(Color::Blue);
	else
		SetColor(Color::Red);
}

bool Player::GetIsTurn() const
{
	return IsTurn;
}

void Player::SetIsTurn(bool IsTurn)
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

bool Player::GetIsMoving() const
{
	return IsMoving;
}

void Player::SetIsOnTheBlock(const bool IsOnTheBlock)
{
	this->IsOnTheBlock = IsOnTheBlock;
}

bool Player::GetDieCheck() const
{
	return DieCheck;
}

void Player::SetDieCheck(const bool DieCheck)
{
	this->DieCheck = DieCheck;
}

void Player::SwitchTurn()
{
	IsTurn = !IsTurn;
	IsVisible = !IsVisible;

	Vector2 playerPosition = GetActorPosition();
	playerPosition.x++;
	SetPosition(playerPosition);
	playerPosition.y--;
	SetPosition(playerPosition);

	playerPosition.x = ((Engine::Get().Width() + LeftSide) / 2 + 1);
	playerPosition.y = Engine::Get().Height() - 2;
	SetPosition(playerPosition);
}

