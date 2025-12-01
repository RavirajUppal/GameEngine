#pragma once

#include "Core.h"
#include <cstdint>
#include <string>
#include "Renderer/Shader.h"
#include "glm/gtc/matrix_transform.hpp"

namespace RealEngine
{
    class REALENGINE_API OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath = nullptr);
        ~OpenGLShader() = default;
	    void Activate() override;
	    void Delete() override;
        void PrintActiveUniforms();

        void SetVec3(const std::string& name, const glm::vec3& value) const;
	    void SetFloat4(const std::string& name, float x, float y, float z, float w) const;
	    void SetFloat3(const std::string& name, float x, float y, float z) const;
	    void SetFloat1(const std::string& name, float x) const;
	    void SetInt1(const std::string& name, int x) const;
	    void SetMat4(const std::string &name, const float *matrix) const;
	    void SetVecOfMat4(const std::string &name, const std::vector<glm::mat4>& matrix) const;
        
    private:
	    uint32_t CompileShader(uint32_t type, const char* source);
	    void CompilerErrors(unsigned int shader, const char* type);
        uint32_t m_RendererID;
    };
}