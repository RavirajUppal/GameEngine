#include "OpenGLTexture.h"
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Logging/Log.h"

namespace RealEngine
{
    OpenGLTexture::OpenGLTexture(const char *path)
    {
        int widthImg, heightImg, numColCh;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *bytes = stbi_load(path, &widthImg, &heightImg, &numColCh, 0);
        REALENGINE_ASSERT(bytes, "Failed to load texture!!");
        m_Width = widthImg;
        m_Height = heightImg;

        glGenTextures(1, &m_RenderId);
        // glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, m_RenderId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if (numColCh == 4)
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                bytes);
        else if (numColCh == 3)
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                bytes);
        else if (numColCh == 1)
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                bytes);
        else
            LOG_ERROR("Automatic Texture type recognition failed");

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(bytes);
        Unbind();
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_RenderId);
    }

    void OpenGLTexture::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RenderId);
    }

    void OpenGLTexture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}