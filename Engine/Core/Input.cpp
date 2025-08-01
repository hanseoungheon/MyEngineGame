#include "Input.h"
#include <Windows.h>
Input::Input()
{
    //싱글톤 함수를 위해 this 키워드 사용!
    instance = this;
}

void Input::ProcessInput()
{
    for (int ix = 0; ix < 255; ++ix)
    {
        keyStates[ix].isKeyDown
            = GetAsyncKeyState(ix) && 0x8000;
        //위 라이브러리 메소드는 해당 키가 눌렸는지, 이전에 눌린적이 있는지,
        //검사하는 메소드 API이다. 0x8000키가 현재 눌려있는지
        //0x0001은 키가 이전에 눌린 적이 있는지
        //true를 반환시 맞는상태, false는 아닌 상태
    }
}

void Input::SavePreviousKeyStates()
{
    for (int ix = 0; ix < 255; ++ix)
    {
        //이전에 눌린 키 저장해놓는용도
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
    //이전 프레임에 눌리지않았고, 지금 누르고있으면 KeyDown
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



