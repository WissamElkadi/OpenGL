#pragma once

#include "Shader.h"

namespace Render
{
	namespace GL
	{
		class ShaderProgram
		{
		private:
			int mShaderProgramId;

		public:
			ShaderProgram(std::unique_ptr<Shader> _vertexShader, std::unique_ptr<Shader> _fragmentShader)
			{
				mShaderProgramId = glCreateProgram();
				glAttachShader(mShaderProgramId, _vertexShader->getShaderId());
				glAttachShader(mShaderProgramId, _fragmentShader->getShaderId());
				glLinkProgram(mShaderProgramId);

				// check for linking errors
				int success;
				char infoLog[512];
				glGetProgramiv(mShaderProgramId, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(mShaderProgramId, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
				}

				_vertexShader.reset();
				_fragmentShader.reset();
			}


			void use()
			{
				glUseProgram(mShaderProgramId);
			}
		};

	}
}
