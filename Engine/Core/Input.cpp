#include "Input.h"
#include <Windows.h>
Input::Input()
{
    //�̱��� �Լ��� ���� this Ű���� ���!
    instance = this;
}

void Input::ProcessInput()
{
    for (int ix = 0; ix < 255; ++ix)
    {
        keyStates[ix].isKeyDown
            = GetAsyncKeyState(ix) && 0x8000;
        //�� ���̺귯�� �޼ҵ�� �ش� Ű�� ���ȴ���, ������ �������� �ִ���,
        //�˻��ϴ� �޼ҵ� API�̴�. 0x8000Ű�� ���� �����ִ���
        //0x0001�� Ű�� ������ ���� ���� �ִ���
        //true�� ��ȯ�� �´»���, false�� �ƴ� ����
    }
}

void Input::SavePreviousKeyStates()
{
    for (int ix = 0; ix < 255; ++ix)
    {
        //������ ���� Ű �����س��¿뵵
        keyStates[ix].previouseKeyDown
            = keyStates[ix].isKeyDown;
    }
}


bool Input::GetKey(int KeyCode)
{
    return keyStates[KeyCode].isKeyDown;
}

bool Input::GetKeyDown(int KeyCode)
{
    return !keyStates[KeyCode].previouseKeyDown
        && keyStates[KeyCode].isKeyDown;
    //���� �����ӿ� �������ʾҰ�, ���� ������������ KeyDown
}

bool Input::GetKeyUp(int KeyCode)
{
    return keyStates[KeyCode].previouseKeyDown
        && !keyStates[KeyCode].isKeyDown;
}

Input& Input::GetController()
{
    return *instance;
}



