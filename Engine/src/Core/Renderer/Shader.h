#pragma once

#include "Core.h"
#include <cstdint>
#include <string>
#include <fstream>

namespace RealEngine
{
    class REALENGINE_API Shader
    {
    public:
        virtual ~Shader() = default;
	    virtual void Activate() = 0;
	    virtual void Delete() = 0;

        static Shader* Create(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath = nullptr);
    };
}