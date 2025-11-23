#pragma once

#include "Core.h"

namespace RealEngine {
    class REALENGINE_API Application{
    public:
        Application();
        virtual ~Application();
        virtual void Run();
    private:
    };

    Application* CreateApplication();
}