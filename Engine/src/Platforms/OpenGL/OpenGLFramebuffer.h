#pragma once
#include <memory>
#include "Renderer/Framebuffer.h"

namespace RealEngine{
    class OpenGLFramebuffer : public Framebuffer{
        public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer();

        void Invalidate();

        void Resize(uint32_t width, uint32_t height) override;
		int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		void ClearAttachment(uint32_t attachmentIndex, int value) override;

		uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override;

        const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
        void Bind() const override;
        void Unbind() const override;
    private:
		uint32_t m_RendererID = 0;
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTexture> m_ColorAttachmentSpecifications;
		FramebufferTexture m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
    };
}