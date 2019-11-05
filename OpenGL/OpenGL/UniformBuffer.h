#pragma once

#include "Types.h"

namespace Render
{
	class UniformBuffer
	{
	public:
		virtual MemoryFormat getMemoryFormat() = 0;
		virtual void update(int _shaderProgramId) = 0;
	};
}
