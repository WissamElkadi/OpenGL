#pragma once

#include<iostream>

#include <glad/glad.h>

#include "Types.h"
#include "Mapper.h"

namespace Render
{
	namespace GL
	{

		class Shader
		{
		protected:
			int          mShaderId;

		public:
			Shader(const char* _shaderSource, ShaderType _shaderType)
			{
				mShaderId = glCreateShader(ShaderTypeMapper.at(_shaderType));
				glShaderSource(mShaderId, 1, &_shaderSource, NULL);
				glCompileShader(mShaderId);

				// check for shader compile errors
				int success;
				char infoLog[512];
				glGetShaderiv(mShaderId, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(mShaderId, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
				}
			}

			int getShaderId() const
			{
				return mShaderId;
			}

			void deleteShader()
			{
				glDeleteShader(mShaderId);
			}

			~Shader()
			{
				glDeleteShader(mShaderId);
			}

		};
	}
}
