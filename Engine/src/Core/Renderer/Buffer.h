#pragma once
#include <cstdint>
#include "Core.h"
#include "Logging/Log.h"

namespace RealEngine
{
    enum class ShaderDataType{
        Int,
        Float,
        Vec2,
        Vec3,
        Vec4,
        Mat3,
        Mat4,
        Bool
    };

    static uint32_t GetShaderDataTypeSize(const ShaderDataType& type){
        switch(type){
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Vec2:   return 4 * 2;
            case ShaderDataType::Vec3:   return 4 * 3;
            case ShaderDataType::Vec4:   return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Bool:   return 1;
        }
        // LOG_ERROR("Unknown Shader data type {}", type);
        REALENGINE_ASSERT(false, "Unknown Shader data type");
        return 0;
    }

    struct BufferElement{
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement() {}

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Type(type), Name(name), Size(GetShaderDataTypeSize(type)), Normalized(normalized)
        {
        }

        uint32_t GetCount() const{
            switch (Type)
            {
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Vec2:   return 2;
                case ShaderDataType::Vec3:   return 3;
                case ShaderDataType::Vec4:   return 4;
                case ShaderDataType::Mat3:   return 3 * 3;
                case ShaderDataType::Mat4:   return 4 * 4;
                case ShaderDataType::Bool:   return 1;
            }
        }
    };

    class BufferLayout{
        public:
            BufferLayout() {}
            BufferLayout(std::initializer_list<BufferElement> elements)
                :m_Elements(elements)
            {
                CalculateOffsetAndStride();
            }

            std::vector<BufferElement>::iterator begin() {return m_Elements.begin();}
            std::vector<BufferElement>::iterator end() {return m_Elements.end();}
            std::vector<BufferElement>::const_iterator begin() const {return m_Elements.begin();}
            std::vector<BufferElement>::const_iterator end() const {return m_Elements.end();}


            const std::vector<BufferElement>& GetElements() const {
                return m_Elements;
            }
            uint32_t GetOffset(const std::string& name) const{
                auto it = std::find_if(m_Elements.begin(), m_Elements.end(), [name](const BufferElement& ele){ return ele.Name == name;});
                if (it != m_Elements.end()){
                    return it->Offset;
                }
                else{
                    LOG_ERROR("No such element is present in Buffer layout {}", name);
                    return 0;
                }
            }
            uint32_t GetStride() const{
                return m_Stride;
            }
        private:
            void CalculateOffsetAndStride(){
                uint32_t offset = 0;
                m_Stride = 0;
                for(BufferElement& ele : m_Elements){
                    ele.Offset = offset;
                    offset += ele.Size;
                    m_Stride += ele.Size;
                }
            }
            std::vector<BufferElement> m_Elements;
            uint32_t m_Stride;
    };

    class REALENGINE_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };

    class REALENGINE_API IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t count);
    };
}