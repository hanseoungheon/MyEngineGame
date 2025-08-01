#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/MultiLine_Actor.h"
#include <Windows.h>
#include <iostream>

GameLevel::GameLevel()
{
	AddActor(new Player());
	AddActor(new MultiLine_Actor("../Assets/sans_unicode.txt", Color::White, Vector2(45, 0)));
}

GameLevel::~GameLevel()
{
	
}

void GameLevel::BeginPlay()
{
	Super::BeginPlay();	SetConsoleOutputCP(CP_UTF8);
	//FILE* rendering_SANS = nullptr;
	//fopen_s(&rendering_SANS, "../Assets/sans_unicode.txt", "rt");

	//if (rendering_SANS == nullptr)
	//{
	//	std::cout << "Fatal_Error: Cannot Read FILE -> sans_unicode.txt\n";
	//}
}

void GameLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void GameLevel::SpawnEnemies(float DeltaTime)
{
}

void GameLevel::Render()
{
	Super::Render();
}

void GameLevel::ProcessCollisionPlayerAndEnemyObject()
{
}
