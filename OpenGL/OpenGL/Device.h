#pragma once

#include <memory>

#include <glad/glad.h>

#include "RenderPipelineState.h"
#include "RenderPieplineDescriptor.h"

namespace Render
{
	class Device
	{
	public:
		static int getMaxVertexAttributes()
		{
			int maxVertexAttributes;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes);
			return maxVertexAttributes;
		}

		static std::unique_ptr<RenderPipelineState> makeRenderPipelineState(RenderPieplineDescriptor* _renderPieplineDescriptor)
		{
			std::unique_ptr<RenderPipelineState> state = std::make_unique<RenderPipelineState>(_renderPieplineDescriptor);
			return std::move(state);
		}
	};
}