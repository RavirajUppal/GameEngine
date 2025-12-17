#pragma once

#include "Renderer/Texture.h"
#include <glad/glad.h>

namespace RealEngine{
    class OpenGLTexture : public Texture2D{
        public:
            OpenGLTexture(const char* path);
            OpenGLTexture(TextureSpecification specification);
            ~OpenGLTexture();
            uint32_t GetWidth() const override { return m_Width; }
            uint32_t GetHeight() const override { return m_Height; }
            void Bind(uint32_t slot) const override;
            void Unbind() const override;
            void SetData(const void* data, uint32_t size) override;
            const TextureSpecification& GetSpecification() const override { return m_Specification; }
            uint32_t GetRendererId() const override { return m_RendererId; }
            bool operator==(const Texture& tex) const override{
                return m_RendererId == tex.GetRendererId();
            }
        private:
            uint32_t m_RendererId;
            TextureSpecification m_Specification;
            GLenum m_InternalFormat;
            GLenum m_DataFormat;
            uint32_t m_Width;
            uint32_t m_Height;
            uint32_t m_Slot;
    };
}