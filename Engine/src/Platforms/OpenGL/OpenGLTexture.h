#pragma once

#include "Renderer/Texture.h"

namespace RealEngine{
    class OpenGLTexture : public Texture2D{
        public:
            OpenGLTexture(const char* path);
            ~OpenGLTexture();
            uint32_t GetWidth() const override { return m_Width; }
            uint32_t GetHeight() const override { return m_Height; }
            void Bind(uint32_t slot) const override;
            void Unbind() const override;
        private:
            uint32_t m_RenderId;
            uint32_t m_Width;
            uint32_t m_Height;
            uint32_t m_Slot;
    };
}