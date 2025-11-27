#include"RealEngine.h"

class FirstGame : public RealEngine::Application
{
public:
    FirstGame()
    {
        LOG_INFO("FirstGame Initialized");
    }

    ~FirstGame()
    {
        LOG_INFO("FirstGame Destroyed");
    }

    void Run() override
    {
        RealEngine::Application::Run();

        LOG_INFO("FirstGame Running");
    }

};

RealEngine::Application* RealEngine::CreateApplication()
{
    LOG_INFO("FirstGame created");
    
    return new FirstGame();
}