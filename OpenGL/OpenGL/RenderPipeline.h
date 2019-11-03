#pragma once

#include <memory>

#include "Shader.h"

namespace Render
{
	namespace GL
	{
		class RenderPipeline
		{
		private:
			int mShaderProgramId;

			bool mLinked = false;

		public:
			std::unique_ptr<Shader> vertexShader;
			std::unique_ptr<Shader> fragmentShader;
			std::unique_ptr<Shader> geometryShader;

			void link()
			{
				mShaderProgramId = glCreateProgram();

				glAttachShader(mShaderProgramId, vertexShader->getShaderId());
				glAttachShader(mShaderProgramId, fragmentShader->getShaderId());

				if (geometryShader)
					glAttachShader(mShaderProgramId, geometryShader->getShaderId());

				glLinkProgram(mShaderProgramId);

				// check for linking errors
				int success;
				char infoLog[512];
				glGetProgramiv(mShaderProgramId, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(mShaderProgramId, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
				}

				vertexShader.reset();
				fragmentShader.reset();

				if (geometryShader)
					geometryShader.reset();

				mLinked = true;
			}

			void use()
			{
				if (!mLinked)
				{
					link();
				}

				glUseProgram(mShaderProgramId);
			}


			void unuse()
			{
				glUseProgram(0);
			}

			int getId()
			{
				return mShaderProgramId;
			}
		};
	}
}
