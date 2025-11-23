#include "Application.h"
#include "Log.h"

namespace RealEngine
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        LOG_CORE_INFO("Application Running");
    }
}
