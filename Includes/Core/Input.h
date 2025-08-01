#pragma once

#include "Core.h"

class Engine_API Input
{
	friend class Engine;

	struct KeyState
	{
		//���� �����ӿ� Ű�� �����ִ��� Ȯ��
		bool isKeyDown = false;

		//���� �����ӿ� Ű�� ���Ⱦ����� Ȯ��
		bool previouseKeyDown = false;
	};

public:
	Input();

	bool GetKey(int KeyCode);
	bool GetKeyDown(int KeyCode);
	bool GetKeyUp(int KeyCode);

	static Input& GetController();
private:
	void ProcessInput();
	void SavePreviousKeyStates();

	//Ű �Է� ���� ���� ����
	KeyState keyStates[255] = {};

	//�̱��� �Լ� => ��? ��Ʈ�ѷ��� �� �ϳ��� �����ؾ��ϴϱ�!
	static Input* instance;
};
