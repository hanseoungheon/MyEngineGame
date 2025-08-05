#pragma once
#include "Level/Level.h"
#include "Utils/Timer.h"
#include "UI/MultiLine_UI.h"
#include "Math/Vector2.h"
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel,Level)

public:
	GameLevel();
	~GameLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void ControllMainUI(MultiLine_UI* mainUI);
	void SpawnEnemies(float DeltaTime);
	virtual void Render() override;

private:
	void ReadMapFile(const char* fileName);

	void UIController();
	void ProcessCollisionPlayerAndEnemyObject();
private:
	bool PlayerIsTurn = true;
	int UI_OperateNumber = 0;
	int hp = 92; //�÷��̾��� ü��

	//���� ������Ʈ�� ���� �� ����� ���� Ÿ�̸� 
	Timer enemyObejctSpawnTimer;

	//�÷��̾��� ����ó���� ���� ����
	bool isPlayerDead = false;

	//�÷��̾� ���� ��ġ ����
	Vector2 PlayerDeadPosition;

	//UI��Ʈ�ѷ�
	int UIcontroller; 

	int PlayerHp;

};