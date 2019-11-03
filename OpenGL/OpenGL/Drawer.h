#pragma once

#include "Types.h"
#include "Mapper.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include "RenderPipeline.h"
#include "UniformBuffer.h"

namespace Render
{
	namespace GL
	{
		class Drawer
		{
		private:
			std::unique_ptr<RenderPipeline>                   mRenderPipeline;
			std::unique_ptr<VertexBuffer>                     mVertexBuffer;
			std::vector<UniformBuffer*>                       mUniformBuffers;

		public:

			void drawElements(DrawingPrimitive _drawingPrimitive, Type _type, size_t count)
			{
				mRenderPipeline->use();
				mVertexBuffer->bind();

				for (const auto& uniformBuffer : mUniformBuffers)
				{
					uniformBuffer->update(mRenderPipeline->getId());
				}

	        	glDrawElements(DrawingPrimitiveMapper.at(_drawingPrimitive), count, TypeMapper.at(_type), 0);

				mVertexBuffer->unbind();
				mRenderPipeline->unuse();
			}

			void draw(DrawingPrimitive _drawingPrimitive, int count)
			{
				glDrawArrays(DrawingPrimitiveMapper.at(_drawingPrimitive), 0, count);
			}

			void setRenderPipeline(std::unique_ptr<RenderPipeline> _renderPipeline)
			{
				mRenderPipeline = std::move(_renderPipeline);
			}

			void setVertexBuffer(std::unique_ptr<VertexBuffer> _vertexArray)
			{
				mVertexBuffer = std::move(_vertexArray);
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
		};
	}
}
