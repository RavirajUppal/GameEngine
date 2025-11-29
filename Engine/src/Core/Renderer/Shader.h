#pragma once

#include "Core.h"
#include <cstdint>
#include <string>
#include <fstream>

namespace RealEngine
{
    std::string get_file_contents(const char* filename);

    class REALENGINE_API Shader
    {
    public:
        Shader(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath = nullptr);
        virtual ~Shader() = default;
	    void Activate();
	    void Delete();
        void PrintActiveUniforms();
        
    private:
	    uint32_t CompileShader(uint32_t type, const char* source);
	    void CompilerErrors(unsigned int shader, const char* type);
        uint32_t m_RendererID;
    };
}