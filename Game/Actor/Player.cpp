#include "Player.h"
#include "Engine.h"
Player::Player() : Actor("Y",Color::Red)
{
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
	//입력 처리
	if (Input::GetController().GetKeyDown(VK_ESCAPE))
	{
		//게임 종료
		QuitGame();
		return;
	}

	if (Input::GetController().GetKey(VK_LEFT) && IsTurn == true)
	{
		Vector2 playerPosition = GetActorPosition();
		playerPosition.x += -1;
		SetPosition(playerPosition);
	}

	if (Input::GetController().GetKey(VK_RIGHT) && IsTurn == true)
	{
		Vector2 playerPosition = GetActorPosition();
		playerPosition.x += 1;
		SetPosition(playerPosition);
	}

	if (Input::GetController().GetKey(VK_UP) && IsTurn == true)
	{
		Vector2 playerPosition = GetActorPosition();
		playerPosition.y += -1;
		SetPosition(playerPosition);
	}

	if (Input::GetController().GetKey(VK_DOWN) && IsTurn == true)
	{
		Vector2 playerPosition = GetActorPosition();
		playerPosition.y += 1;
		SetPosition(playerPosition);
	}
}
