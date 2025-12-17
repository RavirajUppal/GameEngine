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
        OpenGLShader(const std::string& name, std::string_view vertexFilePath, std::string_view fragmentFilePath, std::string_view geometryFilePath = nullptr);
        ~OpenGLShader();
	    void Bind() const override;
	    void Unbind() const override;
	    void Delete() const override;
		const std::string& GetName() const override { return m_Name; }
		
        void SetVec3(const std::string& name, const glm::vec3& value) const override;
	    void SetFloat4(const std::string& name, float x, float y, float z, float w) const override;
	    void SetFloat3(const std::string& name, float x, float y, float z) const override;
	    void SetFloat1(const std::string& name, float x) const override;
		void SetFloat1Array(const std::string& name, float* value, uint32_t count) const override;
	    void SetInt1(const std::string& name, int x) const override;
		void SetInt1Array(const std::string& name, int* value, uint32_t count) const override;
	    void SetMat4(const std::string &name, const float *matrix) const override;
	    void SetVecOfMat4(const std::string &name, const std::vector<glm::mat4>& matrix) const override;
        
        void PrintActiveUniforms() override;
    private:
	    uint32_t CompileShader(uint32_t type, const char* source);
	    bool CompilerErrors(unsigned int shader, const char* type);
		std::string m_Name;
        uint32_t m_RendererID;
    };
}