#include "pch.h"
#include "Application.h"
#include "Log.h"
#include "ApplicationEvent.h"


namespace RealEngine
{
    Application::Application()
    {
        m_Windows = std::unique_ptr<Window>(Window::Create());
        m_Windows->SetEventCallback([this](Event& e){ this->OnEvent(e); });
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        LOG_CORE_INFO(e.ToString());
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }

    void Application::Run()
    {
        LOG_CORE_INFO("Application Running");
        while(m_Running)
        {
            m_Windows->OnUpdate();
        }
    }
}
