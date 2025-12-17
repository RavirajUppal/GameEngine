#include "Renderer.h"
#include "Renderer/Renderer2D.h"
#include "glm/gtc/type_ptr.hpp"

namespace RealEngine{

    std::unique_ptr<Renderer::SceneData> Renderer::m_SceneData = std::make_unique<SceneData>();

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Shutdown()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> &vertexArray)
    {
        shader->Bind();
        shader->SetMat4("u_ViewProjection", glm::value_ptr(m_SceneData->ViewProjectionMatrix));
        RenderCommand::DrawIndexed(vertexArray);
    }
    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewPort(0, 0, width, height);
    }
}