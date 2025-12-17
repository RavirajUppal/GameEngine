#include "pch.h"
#include "Application.h"
#include "Logging/Log.h"
#include "Events/KeyEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Renderer.h"
#include "time.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RealEngine
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        REALENGINE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Windows = std::unique_ptr<Window>(Window::Create());
        m_Windows->SetEventCallback([this](Event& e){ this->OnEvent(e); });
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        LOG_INFO("Destroying Application {}");
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& event) { return this->OnWindowClose(event); });
        // dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        // LOG_INFO(e.ToString());
        dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& event) { return this->OnWindowResize(event); });

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            if(e.m_Handled)
                break;
            (*--it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e){
        LOG_INFO("OnWindowResize width {},  height {} ", e.GetWidth(), e.GetHeight() );
        if (e.GetWidth() == 0 || e.GetHeight() == 0){
            m_Minimised = true;
            return false;
        }
        m_Minimised = false;
        Renderer::OnWindowResize(2* e.GetWidth(), 2* e.GetHeight());
        return false;
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PopLayer(Layer *layer)
    {
        m_LayerStack.PopLayer(layer);
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
    }

    void Application::PopOverlay(Layer *layer)
    {
        m_LayerStack.PopOverlay(layer);
    }

    void Application::Run()
    {
        LOG_INFO("App running");

        while(m_Running)
        {
            float time = (float)glfwGetTime();
            TimeStep delta = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if(!m_Minimised){
                for(Layer* layer : m_LayerStack)
                    layer->OnUpdate(delta);
                
                m_ImGuiLayer->Begin();
                for(Layer* layer : m_LayerStack)
                    layer->OnImGuiRender();
                m_ImGuiLayer->End();
            }

            m_Windows->OnUpdate();
        }
    }
}
