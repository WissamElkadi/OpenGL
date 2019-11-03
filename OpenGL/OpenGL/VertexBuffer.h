#pragma once

#include <vector>

#include <glad/glad.h>

namespace Render
{
	namespace GL
	{
		class VertexBuffer
		{
		private:
			unsigned int mVBO, mVAO, mEBO;

		public:
			VertexBuffer(const std::vector<float>& _vertices, const std::vector<unsigned int>& _indices)
			{
				glGenVertexArrays(1, &mVAO);
				glGenBuffers(1, &mVBO);
				glGenBuffers(1, &mEBO);

				// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
				glBindVertexArray(mVAO);

				glBindBuffer(GL_ARRAY_BUFFER, mVBO);
				glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int) , _indices.data(), GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

				glEnableVertexAttribArray(0);

				// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
				//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

				// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
				// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
				glBindVertexArray(0);
			}


			void bind()
			{
				glBindVertexArray(mVAO);
			}

			void unbind()
			{
				glBindVertexArray(0);
			}
		};
	}
}
