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

    // void Run()
    // {
    //     LOG_CLIENT_INFO("FirstGame Running");
    // }

};

RealEngine::Application* RealEngine::CreateApplication()
{
    LOG_CLIENT_INFO("FirstGame created");
    return new FirstGame();
}