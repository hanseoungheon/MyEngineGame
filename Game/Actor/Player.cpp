#include "Player.h"
#include "Engine.h"
#include "Utils/Utils.h"
Player::Player() : Actor("Y",Color::Red,false)
{
	hp = 92;
	SetSortingOrder(1);
	IsTurn = true;
	//시작 위치(화면의 가운데이면서 살짝 아랫쪽)
	int xPosition = ((Engine::Get().Width()+ LeftSide) / 2);
	int yPosition = Engine::Get().Height() - 1;

	//설정
	SetPosition(Vector2(xPosition, yPosition));
}

void Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	JumpTick++;
	//중력구현
	if (IsGravity && !Input::GetController().GetKey(VK_UP))
	{
		Vector2 playerPosition = GetActorPosition();
		playerPosition.y += 1;
		SetPosition(playerPosition);
		JumpTick = 0;
	}

	//입력 처리
	if (Input::GetController().GetKeyDown(VK_ESCAPE))
	{
		//게임 종료
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

