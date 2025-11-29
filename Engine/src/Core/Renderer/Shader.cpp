#include "Shader.h"
#include <glad/glad.h>
#include "Logging/Log.h"

namespace RealEngine
{
    std::string get_file_contents(const char *filename)
    {
        std::ifstream in(filename, std::ios::in | std::ios::binary);
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return (contents);
        }
        throw std::runtime_error("Failed to open file: " + std::string(filename));
    }

    Shader::Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;

        std::string defineStr = "\n#define USE_GEOMETRY\n";

        try
        {
            vertexCode = get_file_contents(vertexPath);
            fragmentCode = get_file_contents(fragmentPath);
            if (geometryPath != nullptr)
            {
                geometryCode = get_file_contents(geometryPath);
                size_t pos = vertexCode.find('\n');
                vertexCode.insert(pos + 1, defineStr);
            }
        }
        catch (const std::exception &e)
        {
            LOG_ERROR("Shader file loading error: {}", e.what());
        }

        GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode.c_str());
        CompilerErrors(vertexShader, "VERTEX");

        GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
        CompilerErrors(fragmentShader, "FRAGMENT");

        GLuint geometryShader = 0;
        if (!geometryCode.empty())
        {
            geometryShader = CompileShader(GL_GEOMETRY_SHADER, geometryCode.c_str());
            CompilerErrors(geometryShader, "GEOMETRY");
        }

        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);
        if (geometryShader != 0)
            glAttachShader(m_RendererID, geometryShader);
        glLinkProgram(m_RendererID);
        CompilerErrors(m_RendererID, "PROGRAM");

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if (geometryShader != 0)
            glDeleteShader(geometryShader);

        LOG_INFO("Shaders compiled successfully!!!");
    }

    uint32_t Shader::CompileShader(uint32_t type, const char *source)
    {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        return shader;
    }

    void Shader::Activate()
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Delete()
    {
        glDeleteProgram(m_RendererID);
    }

    void Shader::CompilerErrors(unsigned int shader, const char *type)
    {
        GLint hasCompiled;
        std::string program = "PROGRAM";
        // Character array to store error message in
        char infoLog[1024];
        if (type != program)
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
            if (hasCompiled == GL_FALSE)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                LOG_ERROR("SHADER_COMPILATION_ERROR for: {} : {}", type, infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
            if (hasCompiled == GL_FALSE)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                LOG_ERROR("SHADER_LINKING_ERROR for: {} : {}", type, infoLog);
            }
        }
    }

    void Shader::PrintActiveUniforms()
    {
        GLint count;
        glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORMS, &count);

        LOG_INFO("Active uniforms in shader : {} ", m_RendererID);
        for (GLint i = 0; i < count; ++i)
        {
            char name[256];
            GLsizei length;
            GLint size;
            GLenum type;

            glGetActiveUniform(m_RendererID, (GLuint)i, sizeof(name), &length, &size, &type, name);

            GLint location = glGetUniformLocation(m_RendererID, name);

            LOG_INFO(" #{}  name={}  location={}  type={}  size={}  ",i , name, location, type, size);
        }
    }
}