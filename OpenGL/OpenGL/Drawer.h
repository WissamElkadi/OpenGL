#pragma once

#include "Types.h"
#include "Mapper.h"
#include "VertexArrayObject.h"
#include "ShaderProgram.h"

namespace Render
{
	namespace GL
	{
		class Drawer
		{
		public:

			static void drawElements(DrawingPrimitive _drawingPrimitive, Type _type, int count)
			{
				glDrawElements(DrawingPrimitiveMapper.at(_drawingPrimitive), count, TypeMapper.at(_type), 0);
			}

			static void draw(DrawingPrimitive _drawingPrimitive, int count)
			{
				glDrawArrays(DrawingPrimitiveMapper.at(_drawingPrimitive), 0, count);
			}
		};
	}
}
