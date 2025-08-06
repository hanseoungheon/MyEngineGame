#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include <Windows.h>
#include "Utils/Utils.h"

Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
    switch (CtrlType)
    {
    case CTRL_CLOSE_EVENT:
        //Engine의 메모리 해제
        Engine::Get().CleanUp();
        return false;
    }

    //예외처리
    return false;   
}

Engine::Engine()
{
    instance = this;

    //콘솔 커서 끄는 Windows.h API에 들어있는 기능
    //기능 세팅하기
    CONSOLE_CURSOR_INFO info; //커서의 정보 자료형
    info.bVisible = false; //커서가 깜빡이는게 보이게 할지 여부
    info.dwSize = 1;// 커서의 크기

    //세팅한 커서 깜빡임 처리 기능을 적용시키는 메소드
    SetConsoleCursorInfo(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &info
    );

    LoadEngineSetting("EngineSettings.txt");

 
}

Engine::~Engine()
{
    CleanUp();
}


void Engine::BeginPlay()
{
    if (mainLevel)
    {
        mainLevel->BeginPlay();
    }
}

void Engine::Tick(float DeltaTime)
{
    if (mainLevel)
    {
        mainLevel->Tick(DeltaTime);
    }
}

void Engine::Run()
{
    LARGE_INTEGER currentTime;
    LARGE_INTEGER previousTime;
    //Windosw 카운터
    QueryPerformanceCounter(&currentTime);
    previousTime = currentTime;

    //하드웨어 시계의 정밀도(주파수 가져오기)
    //나중에 초로 변환시키기 위한 전처리작업
    LARGE_INTEGER freqeuncy;
    QueryPerformanceFrequency(&freqeuncy);

    //타겟 프레임
    float TargetFrameRate
        = (settings.framerate == 0.0f) ? 60.0f : settings.framerate;

    float oneFrameTime = 1.0 / TargetFrameRate;

    while (true)
    {
        if (isQuit == true)
        {
            break; //루프 종료
        }

        //프레임의 시간을 계산
        //(현재시간 - 이전시간) / 주파수
        QueryPerformanceCounter(&currentTime);
        float deltaTime =
            (currentTime.QuadPart - previousTime.QuadPart)
            / (float)freqeuncy.QuadPart;

        //입력을 최대한 빨리 처리
        controller.ProcessInput();

        //고정 프레임
        if (deltaTime >= oneFrameTime)
        {
            BeginPlay();
            Tick(deltaTime);
            Render();

            previousTime = currentTime;

            //현재 프레임의 입력을 기록 KeyDown & KeyUp을 위한 전처리.
            controller.SavePreviousKeyStates();

            if (mainLevel)
            {
                mainLevel->ProcessAddAndDestroyActors();
            }
        }
    }

    //마지막
    //모든 텍스트 색상을 원래대로 돌려놓기
    Utils::SetConsoleTextColor
    (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    //R G B 빨강 초록 파랑색 빛을 합치면 하얀색이 됨.
}

void Engine::Render()
{
    Utils::SetConsoleTextColor
    (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    //std::cout << "Render Called\n";
    if (mainLevel)
    {
        mainLevel->Render();
    }
}

Engine& Engine::Get()
{
    return *instance;
}

void Engine::AddLevel(Level* newLevel)
{
    if (mainLevel)
    {
        delete mainLevel;
    }

    mainLevel = newLevel;
}

void Engine::CleanUp()
{
    //레벨 삭제
    SafeDelete(mainLevel);
}

void Engine::Quit()
{
    isQuit = true;
}

int Engine::Width() const
{
    return settings.width;
}

int Engine::Height() const
{
    return settings.height;
}

void Engine::LoadEngineSetting(const char * fileName)
{
    char filePath[256] = {};
    sprintf_s(filePath, 256, "../Settings/%s", fileName);

    //엔진 설정 파일을 열기
    FILE* settingFile = nullptr;
    fopen_s(&settingFile,filePath, "rt");

    //파일이 존재하지않거나 오류 발생할시 예외처리
    if (settingFile == nullptr)
    {
        std::cout << "Fatal Error : Failed to load Engine Setting";
        __debugbreak();
        return;
    }

    //엔진 설정 로드하기
    //FP 포인터를 가장 뒤로 옮기기
    fseek(settingFile, 0, SEEK_END);

    //이 위치 구하기
    size_t fileSize = ftell(settingFile);

    //다시 첫 위치로 돌리기
    rewind(settingFile); //fseek(settingFile,0,SEEK_SET)와 같다.

    char* buffer = new char[fileSize + 1];
    memset(buffer, 0, fileSize + 1);

    //내용 읽기
    size_t readSize = fread(buffer, sizeof(char), fileSize, settingFile);

    //구문 해석(파싱) => 필요한 정보 해석
    char* context = nullptr;
    char* token = nullptr;

    token = strtok_s(buffer, "\n", &context);

    while (token != nullptr)
    {
        char header[10] = {};

        sscanf_s(token, "%s", header, 10);

        //헤더 문자열 비교 true 0 , false => 오른쪽이 크면 음수, 왼쪽이 크면 양수
        if (strcmp(header, "framerate") == 0)
            sscanf_s(token, "framrate = %f", &settings.framerate);

        else if (strcmp(header, "width") == 0)
            sscanf_s(token, "width = %d", &settings.width);

        else if (strcmp(header, "height") == 0)
            sscanf_s(token, "height = %d", &settings.height);

        token = strtok_s(nullptr, "\n", &context);
    }

    SafeDeleteArray(buffer); //버퍼 해제

    fclose(settingFile);
}
