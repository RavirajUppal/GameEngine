#include "pch.h"
#include "Application.h"
#include "Log.h"
#include <glad/glad.h>

namespace RealEngine
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        REALENGINE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Windows = std::unique_ptr<Window>(Window::Create());
        m_Windows->SetEventCallback([this](Event& e){ this->OnEvent(e); });
    }

    Application::~Application()
    {
        m_LayerStack.~LayerStack();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        // dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return this->OnWindowClose(e); });
        LOG_INFO(e.ToString());

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if(e.m_Handled)
                break;
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PopLayer(Layer *layer)
    {
        m_LayerStack.PopLayer(layer);
        layer->OnDetach();
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::PopOverlay(Layer *layer)
    {
        m_LayerStack.PopOverlay(layer);
        layer->OnDetach();
    }

    void Application::Run()
    {
        LOG_INFO("App running");
        while(m_Running)
        {
            m_Windows->OnUpdate();
            for(Layer* layer : m_LayerStack)
                layer->OnUpdate();
        }
    }
}
