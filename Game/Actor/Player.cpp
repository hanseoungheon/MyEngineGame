#include "Player.h"
#include "Engine.h"
Player::Player() : Actor("Y",Color::Red)
{
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
	//�Է� ó��
	if (Input::GetController().GetKeyDown(VK_ESCAPE))
	{
		//���� ����
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
