#include "pch.h"
#include "Application.h"
#include "Logging/Log.h"
#include <glad/glad.h>
#include "Events/KeyEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

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
        PushLayer(m_ImGuiLayer);
        
        shader = std::make_shared<Shader>(SHADER_DIR "Default.vert", SHADER_DIR "Default.frag");
        float vertices[3 * 7] ={
            -0.5f, -0.5, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.5, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
        };

        vao.reset(VertexArray::Create());

        vbo.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            {ShaderDataType::Vec3, "a_Position"},
            {ShaderDataType::Vec4, "a_Color"}
        };
        vbo->SetLayout(layout);

        uint32_t indices[] = {0, 1, 2};
        ibo.reset(IndexBuffer::Create(indices, sizeof(indices)/ sizeof(uint32_t)));

        vao->AddVertexBuffer(vbo);
        vao->SetIndexBuffer(ibo);
        shader->Activate();
        shader->PrintActiveUniforms();
    }

    Application::~Application()
    {
        LOG_INFO("Destroying Application {}");
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        // dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return this->OnWindowClose(e); });
        // LOG_INFO(e.ToString());

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
            glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            RenderCommand::SetClearColor({0.3f, 0.4f, 0.5f, 1.0f});
            RenderCommand::Clear();

            Renderer::BeginScene();

            shader->Activate();
            Renderer::Submit(vao);

            Renderer::EndScene();

            for(Layer* layer : m_LayerStack)
            layer->OnUpdate();
            
            m_ImGuiLayer->Begin();
            for(Layer* layer : m_LayerStack)
            layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Windows->OnUpdate();
        }
    }
}
