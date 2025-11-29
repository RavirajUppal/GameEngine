#pragma once
#include "Renderer/VertexArray.h"
#include "OpenGLBuffer.h"

namespace RealEngine{
    class OpenGLVertexArray : public VertexArray{
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() {}
        void Bind() const override;
        void Unbind() const override;
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;
        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;
        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

    private:
        uint32_t m_RendererId;
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}