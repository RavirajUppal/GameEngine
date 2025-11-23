#pragma once
#include "Log.h"

extern RealEngine::Application* RealEngine::CreateApplication();

int main(int argc, char** argv)
{
    RealEngine::Log::Init();
    LOG_CORE_INFO("RealEngine Initialized");
    auto app = RealEngine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}