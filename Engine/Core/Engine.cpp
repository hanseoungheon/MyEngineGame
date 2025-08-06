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
        //Engine�� �޸� ����
        Engine::Get().CleanUp();
        return false;
    }

    //����ó��
    return false;   
}

Engine::Engine()
{
    instance = this;

    //�ܼ� Ŀ�� ���� Windows.h API�� ����ִ� ���
    //��� �����ϱ�
    CONSOLE_CURSOR_INFO info; //Ŀ���� ���� �ڷ���
    info.bVisible = false; //Ŀ���� �����̴°� ���̰� ���� ����
    info.dwSize = 1;// Ŀ���� ũ��

    //������ Ŀ�� ������ ó�� ����� �����Ű�� �޼ҵ�
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
    //Windosw ī����
    QueryPerformanceCounter(&currentTime);
    previousTime = currentTime;

    //�ϵ���� �ð��� ���е�(���ļ� ��������)
    //���߿� �ʷ� ��ȯ��Ű�� ���� ��ó���۾�
    LARGE_INTEGER freqeuncy;
    QueryPerformanceFrequency(&freqeuncy);

    //Ÿ�� ������
    float TargetFrameRate
        = (settings.framerate == 0.0f) ? 60.0f : settings.framerate;

    float oneFrameTime = 1.0 / TargetFrameRate;

    while (true)
    {
        if (isQuit == true)
        {
            break; //���� ����
        }

        //�������� �ð��� ���
        //(����ð� - �����ð�) / ���ļ�
        QueryPerformanceCounter(&currentTime);
        float deltaTime =
            (currentTime.QuadPart - previousTime.QuadPart)
            / (float)freqeuncy.QuadPart;

        //�Է��� �ִ��� ���� ó��
        controller.ProcessInput();

        //���� ������
        if (deltaTime >= oneFrameTime)
        {
            BeginPlay();
            Tick(deltaTime);
            Render();

            previousTime = currentTime;

            //���� �������� �Է��� ��� KeyDown & KeyUp�� ���� ��ó��.
            controller.SavePreviousKeyStates();

            if (mainLevel)
            {
                mainLevel->ProcessAddAndDestroyActors();
            }
        }
    }

    //������
    //��� �ؽ�Ʈ ������ ������� ��������
    Utils::SetConsoleTextColor
    (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    //R G B ���� �ʷ� �Ķ��� ���� ��ġ�� �Ͼ���� ��.
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
    //���� ����
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

    //���� ���� ������ ����
    FILE* settingFile = nullptr;
    fopen_s(&settingFile,filePath, "rt");

    //������ ���������ʰų� ���� �߻��ҽ� ����ó��
    if (settingFile == nullptr)
    {
        std::cout << "Fatal Error : Failed to load Engine Setting";
        __debugbreak();
        return;
    }

    //���� ���� �ε��ϱ�
    //FP �����͸� ���� �ڷ� �ű��
    fseek(settingFile, 0, SEEK_END);

    //�� ��ġ ���ϱ�
    size_t fileSize = ftell(settingFile);

    //�ٽ� ù ��ġ�� ������
    rewind(settingFile); //fseek(settingFile,0,SEEK_SET)�� ����.

    char* buffer = new char[fileSize + 1];
    memset(buffer, 0, fileSize + 1);

    //���� �б�
    size_t readSize = fread(buffer, sizeof(char), fileSize, settingFile);

    //���� �ؼ�(�Ľ�) => �ʿ��� ���� �ؼ�
    char* context = nullptr;
    char* token = nullptr;

    token = strtok_s(buffer, "\n", &context);

    while (token != nullptr)
    {
        char header[10] = {};

        sscanf_s(token, "%s", header, 10);

        //��� ���ڿ� �� true 0 , false => �������� ũ�� ����, ������ ũ�� ���
        if (strcmp(header, "framerate") == 0)
            sscanf_s(token, "framrate = %f", &settings.framerate);

        else if (strcmp(header, "width") == 0)
            sscanf_s(token, "width = %d", &settings.width);

        else if (strcmp(header, "height") == 0)
            sscanf_s(token, "height = %d", &settings.height);

        token = strtok_s(nullptr, "\n", &context);
    }

    SafeDeleteArray(buffer); //���� ����

    fclose(settingFile);
}
