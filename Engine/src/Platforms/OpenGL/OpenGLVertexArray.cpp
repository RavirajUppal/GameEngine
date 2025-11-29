#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace RealEngine
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Vec2:     return GL_FLOAT;
			case ShaderDataType::Vec3:     return GL_FLOAT;
			case ShaderDataType::Vec4:     return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		REALENGINE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererId);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererId);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
    {
        REALENGINE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererId);
        vertexBuffer->Bind();
        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for(const auto& ele : layout){
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                ele.GetCount(), 
                ShaderDataTypeToOpenGLBaseType(ele.Type),
                ele.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (void*)(uintptr_t)ele.Offset);
            index++;
        }
        m_vertexBuffer.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
    {
        glBindVertexArray(m_RendererId);
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }

    const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
    {
        return m_vertexBuffer;
    }
    const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }
}