#pragma once
#include "Core.h"
#include "Renderer/Buffer.h"

namespace RealEngine
{
    class REALENGINE_API OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;
        void SetLayout(const BufferLayout& layout) override;
        const BufferLayout& GetLayout() const override;

    private:
        uint32_t m_RendererID;
        BufferLayout m_BufferLayout;
    };

    class REALENGINE_API OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer() {}
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;

        inline uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}