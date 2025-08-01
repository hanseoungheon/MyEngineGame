#pragma once
#include "Core.h"
#include "Input.h"
#include <Windows.h>

class Level; //���漱��

struct EngineSetting
{
	//�ܼ�ȭ�� ���� ũ��
	int width = 0;

	//�ܼ�ȭ�� ���� ũ��
	int height = 0;

	//Ÿ�� ������ �ӵ�
	float framerate = 0.0f;
};
class Engine_API Engine
{
public:
	Engine();

	virtual ~Engine();

	void Run();

	static Engine& Get(); //�̱��� ���� �Լ�!

	void AddLevel(Level* newLevel);

	virtual void CleanUp();

	void Quit();

	int Width() const;
	int Height() const;

private:
	void BeginPlay();
	void Tick(float DeltaTime = 0.0f);
	void Render();

	//���� ���� �ε� �Լ�
	void LoadEngineSetting();

private:
	//���� ���� �÷���
	bool isQuit = false;

	Level* mainLevel = nullptr;

	Input controller;

	static Engine* instance;
	//������ �� �Ѱ��� �����ؾ��ϰ� �� ������ �Ѱ��ؾ��ϴϱ� �̱��� ����

	EngineSetting settings;
};