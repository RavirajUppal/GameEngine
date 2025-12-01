#include <fstream>
#include <glad/glad.h>
#include "Logging/Log.h"
#include "OpenGLShader.h"

namespace RealEngine
{
    static std::string get_file_contents(const char *filename)
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

    OpenGLShader::OpenGLShader(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
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

    uint32_t OpenGLShader::CompileShader(uint32_t type, const char *source)
    {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        return shader;
    }

    void OpenGLShader::Activate()
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Delete()
    {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::CompilerErrors(unsigned int shader, const char *type)
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

    void OpenGLShader::SetVec3(const std::string &name, const glm::vec3 &value) const
    {
        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        if (loc != -1)
        {
            glUniform3fv(loc, 1, &value[0]);
        }
        else
        {
            LOG_ERROR("Warning: uniform {} not found. ", name);
        }
    }

    // Overload for individual floats
    void OpenGLShader::SetFloat4(const std::string &name, float x, float y, float z, float w) const
    {
        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        if (loc != -1)
        {
            glUniform4f(loc, x, y, z, w);
        }
        else
        {
            LOG_ERROR("Warning: uniform {} not found. ", name);
        }
    }

    void OpenGLShader::SetFloat3(const std::string &name, float x, float y, float z) const
    {
        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        if (loc != -1)
        {
            glUniform3f(loc, x, y, z);
        }
        else
        {
            LOG_ERROR("Warning: uniform {} not found. ", name);
        }
    }

    void OpenGLShader::SetFloat1(const std::string &name, float x) const
    {
        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        if (loc != -1)
        {
            glUniform1f(loc, x);
        }
        else
        {
            LOG_ERROR("Warning: uniform {} not found. ", name);
        }
    }

    void OpenGLShader::SetInt1(const std::string &name, int x) const
    {
        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        if (loc != -1)
        {
            glUniform1i(loc, x);
        }
        else
        {
            LOG_ERROR("Warning: uniform {} not found. ", name);
        }
    }

    void OpenGLShader::SetMat4(const std::string &name, const float *matrix) const
    {
        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        if (loc != -1)
        {
            // Upload 4x4 matrix, no transpose (OpenGL expects column-major order)
            glUniformMatrix4fv(loc, 1, GL_FALSE, matrix);
        }
        else
        {
            LOG_ERROR("Warning: uniform {} not found. ", name);
        }
    }

    void OpenGLShader::SetVecOfMat4(const std::string &name, const std::vector<glm::mat4> &matrixVec) const
    {
        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        if (loc != -1)
        {
            // Upload 4x4 matrix, no transpose (OpenGL expects column-major order)
            glUniformMatrix4fv(loc, matrixVec.size(), GL_FALSE, &matrixVec[0][0][0]);
        }
        else
        {
            LOG_ERROR("Warning: uniform {} not found. ", name);
        }
    }

    void OpenGLShader::PrintActiveUniforms()
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

            LOG_INFO(" #{}  name={}  location={}  type={}  size={}  ", i, name, location, type, size);
        }
    }
}