#include "GameLevel.h"
#include "Actor/Player.h"
GameLevel::GameLevel()
{
	AddActor(new Player());
}

GameLevel::~GameLevel()
{
	
}

void GameLevel::BeginPlay()
{
	Super::BeginPlay();
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
