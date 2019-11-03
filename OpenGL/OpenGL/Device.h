#pragma once

#include <glad/glad.h>

namespace Render
{
	namespace GL
	{
		class Device
		{
			static int getMaxVertexAttributes()
			{
				int maxVertexAttributes;
				glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes);
				return maxVertexAttributes;
			}
		};
	}
}