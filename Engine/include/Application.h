#pragma once

#include "Core.h"
#include "Event.h"
#include "Window.h"
#include "ApplicationEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

namespace RealEngine {
    class REALENGINE_API Application{
    public:
        Application();
        virtual ~Application();
        static Application& Get() { return *s_Instance; }
        virtual void Run();
        virtual void OnEvent(Event& e);
        virtual bool OnWindowClose(WindowCloseEvent& e);
        virtual void PushLayer(Layer* layer);
        virtual void PopLayer(Layer* layer);
        virtual void PushOverlay(Layer* layer);
        virtual void PopOverlay(Layer* layer);
        Window& GetWindow() { return *m_Windows; }
    private:
        bool m_Running = true;
        std::unique_ptr<Window> m_Windows;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_LayerStack;
        static Application* s_Instance;
    };

    Application* CreateApplication();
}