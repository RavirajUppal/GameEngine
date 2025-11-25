#pragma once

#include "Core.h"
#include "Event.h"
#include "Window.h"
#include "ApplicationEvent.h"

namespace RealEngine {
    class REALENGINE_API Application{
    public:
        Application();
        virtual ~Application();
        virtual void Run();
        virtual void OnEvent(Event& e);
        virtual bool OnWindowClose(WindowCloseEvent& e);
    private:
        bool m_Running = true;
        std::unique_ptr<Window> m_Windows;
    };

    Application* CreateApplication();
}