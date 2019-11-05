#pragma once

#include "Types.h"
#include "DataStructure.h"

namespace Render
{
	struct TextureDescriptor
	{
		Region        region;
		PixelFormat   format;
		TextureType   type;
		std::string   name;
		bool          mipmapped;
	};
}