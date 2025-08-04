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

	int hp = 92; //�÷��̾��� ü��

	//���� ������Ʈ�� ���� �� ����� ���� Ÿ�̸� 
	Timer enemyObejctSpawnTimer;

	//�÷��̾��� ����ó���� ���� ����
	bool isPlayerDead = false;

	//�÷��̾� ���� ��ġ ����
	Vector2 PlayerDeadPosition;


};