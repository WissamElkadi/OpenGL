#pragma once

#include "Types.h"

namespace Render
{
	namespace GL
	{
		class UniformBuffer
		{
		public:
			virtual UniformType getUniformType() = 0;
			virtual void update(int _shaderProgramId) = 0;
		};
	}
}
