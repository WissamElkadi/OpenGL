#pragma once

#include <memory>
#include <vector>
#include <utility>

#include "Shader.h"
#include "Texture.h"
#include "Sampler.h"

namespace Render
{
	struct RenderPieplineDescriptor
	{
		Shader*   vertexShader      { nullptr };
		Shader*   fragmentShader    { nullptr };
		Shader*   geometryShader    { nullptr };
		std::vector<std::pair<Texture*, Sampler*>> textures;
	};
}
