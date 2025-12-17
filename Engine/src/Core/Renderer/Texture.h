#pragma once

#include <cstdint>

namespace RealEngine
{
    enum class ImageFormat
	{
		None = 0,
		R8,
		RGB8,
		RGBA8,
		RGBA16F
	};

	struct TextureSpecification
	{
		uint32_t Width = 1;
		uint32_t Height = 1;
		ImageFormat Format = ImageFormat::RGBA8;
		bool GenerateMips = true;
	};

    class Texture{
        public:
            virtual ~Texture() = default;
            virtual uint32_t GetWidth() const = 0;
            virtual uint32_t GetHeight() const = 0;
            virtual void Bind(uint32_t slot = 0) const = 0;
            virtual void Unbind() const = 0;
            virtual void SetData(const void* data, uint32_t size) = 0;
            virtual uint32_t GetRendererId() const = 0;
            virtual const TextureSpecification& GetSpecification() const = 0;
            virtual bool operator==(const Texture& tex) const = 0;
    };

    class Texture2D : public Texture{
        public:
            static std::shared_ptr<Texture2D> Create(const char* path); 
            static std::shared_ptr<Texture2D> Create(TextureSpecification specification);
    };
}