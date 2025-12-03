#pragma once

#include "Core.h"
#include "glm/glm.hpp"

namespace RealEngine
{
    class REALENGINE_API Shader
    {
    public:
        virtual ~Shader() = default;
	    virtual void Bind() const = 0;
	    virtual void Unbind() const = 0;
	    virtual void Delete() const = 0;
		virtual const std::string& GetName() const = 0;

        virtual void SetVec3(const std::string& name, const glm::vec3& value) const = 0;
	    virtual void SetFloat4(const std::string& name, float x, float y, float z, float w) const = 0;
	    virtual void SetFloat3(const std::string& name, float x, float y, float z) const = 0;
	    virtual void SetFloat1(const std::string& name, float x) const = 0;
	    virtual void SetInt1(const std::string& name, int x) const = 0;
	    virtual void SetMat4(const std::string &name, const float *matrix) const = 0;
	    virtual void SetVecOfMat4(const std::string &name, const std::vector<glm::mat4>& matrix) const = 0;

        static std::shared_ptr<Shader> Create(const std::string& name, std::string_view vertexFilePath, std::string_view fragmentFilePath, std::string_view geometryFilePath = "");
    };

	class ShaderLibrary
	{
	public:
		ShaderLibrary() = default;
		~ShaderLibrary() = default;
		void Add(const std::string& name, const std::shared_ptr<Shader>& shader);
		void Add(const std::shared_ptr<Shader>& shader);
		std::shared_ptr<Shader> Load(const std::string& name, std::string_view vertexFilePath, std::string_view fragmentFilePath, std::string_view geometryFilePath = {});
		std::shared_ptr<Shader> Get(const std::string& name);
		bool Exist(const std::string& name);

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}