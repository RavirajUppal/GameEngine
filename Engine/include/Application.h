#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Platforms/OpenGL/OpenGLVertexArray.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"
#include "Renderer/Shader.h"


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

        std::shared_ptr<Shader> shader;
        std::shared_ptr<VertexArray> vao;
        std::shared_ptr<VertexBuffer> vbo;
        std::shared_ptr<IndexBuffer> ibo;
    };

    Application* CreateApplication();
}