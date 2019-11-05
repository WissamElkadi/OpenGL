#pragma once

#include <memory>

#include "DataStructure.h"
#include "Types.h"

namespace Render
{
	struct SamplerDescriptor
	{
		TextureType    textureType;
		TextureFilter  magFilter;
		TextureFilter  minFilter;
		TextureWrap    sWrap;
		TextureWrap    tWrap;
		TextureWrap    rWrap;
		Color          borderColor;
	};
}
