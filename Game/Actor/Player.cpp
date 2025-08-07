#include "Player.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include <iostream>
Player::Player() : Actor("Y",Color::Red,Vector2::Zero,false,IsString::STR_FALSE)
{
	hp = 92;
	SetSortingOrder(3);
	IsTurn = true;
	//시작 위치(화면의 가운데이면서 살짝 아랫쪽)
	int xPosition = ((Engine::Get().Width()+ LeftSide) / 2);
	int yPosition = Engine::Get().Height() - 1;

	//설정
	SetPosition(Vector2(xPosition, yPosition));
	TestMoving = 0;
}

void Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TestMoving = (IsMoving) ? 1 : 0;
	//std::cout << TestMoving;
	//std::cout << hp;
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

	//if (Input::GetController().GetKeyDown(VK_NUMPAD2))
	//{
	//	LeftSide += 11;
	//}

	if (Input::GetController().GetKeyDown(VK_TAB))
	{
		IsTurn = !IsTurn;
		IsVisible = !IsVisible;
		Vector2 playerPosition = GetActorPosition();
		//playerPosition.x++;
		//SetPosition(playerPosition);
		//playerPosition.x--;
		//SetPosition(playerPosition);
		//playerPosition.x--;
		//SetPosition(playerPosition);
		//playerPosition.x++;
		//SetPosition(playerPosition);
		playerPosition.x = ((Engine::Get().Width() + LeftSide) / 2 + 1);
		playerPosition.y = Engine::Get().Height() - 2;
		SetPosition(playerPosition);
		//IsGravity = true;
		//SetColor(Color::Blue);
	}

	if (Input::GetController().GetKey(VK_BACK))
	{
		--hp;
	}

	if (Input::GetController().GetKey(VK_RETURN))
	{
		hp = 80;
	}

	if (Input::GetController().GetKey(VK_LBUTTON))
	{
		if (hp < 92)
		{
			++hp;
		}
	}

	if (IsTurn)
	{
		//이동 키 매핑
		if (Input::GetController().GetKey(VK_LEFT) && JumpTick % 4 == 0)
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
			&& JumpTick % 4 == 0)
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

bool Player::GetIsMoving() const
{
	return IsMoving;
}

