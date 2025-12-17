#include "OpenGLTexture.h"
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Logging/Log.h"

namespace RealEngine
{

	static GLenum ImageFormatToGLDataFormat(ImageFormat format)
	{
		switch (format)
		{
            case ImageFormat::R8:      return GL_RED;
			case ImageFormat::RGB8:    return GL_RGB;
			case ImageFormat::RGBA8:   return GL_RGBA;
			case ImageFormat::RGBA16F: return GL_RGBA;
            // default:                   return GL_RGB;
		}
		REALENGINE_ASSERT(false);
		return 0;
	}
	
	static GLenum ImageFormatToGLInternalFormat(ImageFormat format)
	{
		switch (format)
		{
            case ImageFormat::R8:      return GL_R8;
		    case ImageFormat::RGB8:    return GL_RGB8;
		    case ImageFormat::RGBA8:   return GL_RGBA8;
			case ImageFormat::RGBA16F: return GL_RGBA16F;
            // default:                   return GL_RGB;
		}
		REALENGINE_ASSERT(false);
		return 0;
	}


    OpenGLTexture::OpenGLTexture(const char *path)
    {
        int widthImg, heightImg, numColCh;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *bytes = stbi_load(path, &widthImg, &heightImg, &numColCh, 0);
        REALENGINE_ASSERT(bytes, "Failed to load texture!!");
        m_Width = widthImg;
        m_Height = heightImg;

        glGenTextures(1, &m_RendererId);
        // glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, m_RendererId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        switch (numColCh)
        {
        case 4:
            m_InternalFormat = GL_RGBA8;
            m_DataFormat = GL_RGBA;
            break;
        case 3:
            m_InternalFormat = GL_RGB8;
            m_DataFormat = GL_RGB;
            break;
        case 1:
            m_InternalFormat = GL_R8;
            m_DataFormat = GL_RED;
            break;
        default:
            LOG_ERROR("Unsupported image color chanel : {} ", numColCh);
        }

        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, widthImg, heightImg, 0, m_DataFormat, GL_UNSIGNED_BYTE, bytes);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(bytes);
        Unbind();
    }

    OpenGLTexture::OpenGLTexture(TextureSpecification specification)
        :m_Specification(specification), m_Width(specification.Width), m_Height(specification.Height)
    {
        m_InternalFormat = ImageFormatToGLInternalFormat(m_Specification.Format);
		m_DataFormat = ImageFormatToGLDataFormat(m_Specification.Format);

        glGenTextures(1, &m_RendererId);
        glBindTexture(GL_TEXTURE_2D, m_RendererId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, nullptr);
        Unbind();
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_RendererId);
    }

    void OpenGLTexture::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererId);
    }

    void OpenGLTexture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    void OpenGLTexture::SetData(const void *data, uint32_t size)
    {
        glBindTexture(GL_TEXTURE_2D, m_RendererId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }
}