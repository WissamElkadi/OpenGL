#pragma once

#include<vector>

#include "DataStructure.h"

namespace Render
{
	struct VertexDescriptor
	{
		std::vector<VertexAttribute>     attributes;
		std::vector<VertexLayout>        layouts;
	};
}
