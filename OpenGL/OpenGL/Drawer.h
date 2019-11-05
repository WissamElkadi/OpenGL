#pragma once

#include "Types.h"
#include "Mapper.h"
#include "VertexBuffer.h"
#include "RenderPipelineState.h"
#include "UniformBuffer.h"
#include "VertexDescriptor.h"
#include "Buffer.h"
#include "Sampler.h"
#include "Texture.h"

namespace Render
{
	class Drawer
	{
	private:
		RenderPipelineState*          mRenderPipelineState;
		VertexBuffer*                 mVertexBuffer;
		std::vector<UniformBuffer*>   mUniformBuffers;
		Buffer*                       mIndexBuffer;

	public:
		void drawElements(DrawingPrimitive _drawingPrimitive, Type _type, size_t count)
		{
			mRenderPipelineState->use();
			mVertexBuffer->bind();

			for (const auto& uniformBuffer : mUniformBuffers)
			{
				uniformBuffer->update(mRenderPipelineState->getId());
			}

			glDrawElements(DrawingPrimitiveMapper.at(_drawingPrimitive), count, TypeMapper.at(_type), 0);

			//mVertexBuffer->unbind();
			//mRenderPipelineState->unuse();
		}

		void draw(DrawingPrimitive _drawingPrimitive, int count)
		{
			glDrawArrays(DrawingPrimitiveMapper.at(_drawingPrimitive), 0, count);
		}

		void setRenderPipelineState(RenderPipelineState* _RenderPipelineState)
		{
			mRenderPipelineState = _RenderPipelineState;
			mRenderPipelineState->link();
		}

		void setUniformBuffers(std::vector<UniformBuffer*>& _uniformBuffers)
		{
			mUniformBuffers = _uniformBuffers;
		}

		void setViewPort(int _xOffset, int _yOffset, int _width, int _height)
		{
			glViewport(_xOffset, _yOffset, _width, _height);
		}

		void setClearColor(float _r, float _g, float _b, float _a)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void setVertexBuffer(VertexBuffer* _vertexBuffer)
		{
			mVertexBuffer = _vertexBuffer;
		}

		void setIndexBuffer(Buffer* _indexBuffer)
		{
		}
	};
}
