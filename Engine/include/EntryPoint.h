#pragma once
#include "Logging/Log.h"


extern RealEngine::Application* RealEngine::CreateApplication();

int main(int argc, char** argv)
{
    RealEngine::Log::Init();
    LOG_INFO("Entry Point");
    auto app = RealEngine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}