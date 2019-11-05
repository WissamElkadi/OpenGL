#pragma once

#include <vector>

#include <glad/glad.h>

#include "DataStructure.h"

namespace Render
{
	class Buffer
	{
	public:
		Buffer() = delete;

		Buffer(void** _content)
		{
			mContent = *_content;
		}

		void* data()
		{
			return mContent;
		}
	private:
		void* mContent;
	};
}
