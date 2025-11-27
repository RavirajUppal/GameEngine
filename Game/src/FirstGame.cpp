#include"RealEngine.h"

class FirstGame : public RealEngine::Application
{
public:
    FirstGame()
    {
    }

    ~FirstGame()
    {

    }

    void Run() override
    {
        RealEngine::Application::Run();
    }

};

RealEngine::Application* RealEngine::CreateApplication()
{
    LOG_INFO("FirstGame created");

    return new FirstGame();
}