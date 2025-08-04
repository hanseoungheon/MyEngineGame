#pragma once
#include "Level/Level.h"
#include "Utils/Timer.h"
#include "Math/Vector2.h"
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel,Level)

public:
	GameLevel();
	~GameLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SpawnEnemies(float DeltaTime);
	virtual void Render() override;

private:
	void ReadMapFile(const char* fileName);

	void ProcessCollisionPlayerAndEnemyObject();
private:

	int hp = 92; //플레이어의 체력

	//공격 오브젝트가 생성 시 계산을 위한 타이머 
	Timer enemyObejctSpawnTimer;

	//플레이어의 죽음처리를 위한 변수
	bool isPlayerDead = false;

	//플레이어 죽은 위치 정보
	Vector2 PlayerDeadPosition;


};