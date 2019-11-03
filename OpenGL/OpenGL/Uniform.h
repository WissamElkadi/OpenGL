#pragma once

#include<string>

#include<glad/glad.h>

#include "Types.h"
#include "UniformBuffer.h"
namespace Render
{
	namespace GL
	{
		template<typename T>
		class Uniform : public UniformBuffer
		{
		private:
			T*          mValue;
			std::string mName;
			UniformType mUniformType;

		public:
			Uniform(std::string _name, UniformType _uniformType)
			{
				mName = _name;
				mUniformType = _uniformType;
			}

			Uniform(std::string _name, UniformType _uniformType, T* _value)
			{
				mName = _name;
				mUniformType = _uniformType;
				mValue = _value;
			}

			template<typename T>
			void updateValue(T* _value)
			{
				mValue = _value;
			}

			template<typename T>
			void updateValue(int _programId, T* _value)
			{
				int uniformLocation = glGetUniformLocation(_programId, mName.c_str());

				switch (mUniformType)
				{
				case UniformType::FLOAT_1:
					glUniform1f(uniformLocation, *_value);
					break;
				case UniformType::FLOAT_2:
					glUniform2f(uniformLocation, _value[0], _value[1]);
					break;
				case UniformType::FLOAT_3:
					glUniform3f(uniformLocation, _value[0], _value[1], _value[2]);
					break;
				case UniformType::FLOAT_4:
					glUniform4f(uniformLocation, _value[0], _value[1], _value[2], _value[3]);
					break;
				case UniformType::INT_1:
					glUniform1i(uniformLocation, *_value);
					break;
				case UniformType::INT_2:
					glUniform2i(uniformLocation, _value[0], _value[1]);
					break;
				case UniformType::INT_3:
					glUniform3i(uniformLocation, _value[0], _value[1], _value[2]);
					break;
				case UniformType::INT_4:
					glUniform4i(uniformLocation, _value[0], _value[1], _value[2], _value[3]);
					break;
				case UniformType::VEC_FLOAT_1:
					glUniform1fv(uniformLocation, 1, value);
					break;
				case UniformType::VEC_FLOAT_2:
					glUniform2fv(uniformLocation, 1, value);
					break;
				case UniformType::VEC_FLOAT_3:
					glUniform3fv(uniformLocation, 1, value);
					break;
				case UniformType::VEC_FLOAT_4:
					glUniform4fv(uniformLocation, 1, value);
					break;
				case UniformType::VEC_INT_1:
					glUniform1iv(uniformLocation, 1, value);
					break;
				case UniformType::VEC_INT_2:
					glUniform2iv(uniformLocation, 1, value);
					break;
				case UniformType::VEC_INT_3:
					glUniform3iv(uniformLocation, 1, value);
					break;
				case UniformType::VEC_INT_4:
					glUniform4iv(uniformLocation, 1, value);
					break;
				case UniformType::MAT_FLOAT_2X2:
					glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, value);
					break;
				case UniformType::MAT_FLOAT_3X3:
					glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, value);
					break;
				case UniformType::MAT_FLOAT_4X4:
					glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value);
					break;
				default:
					break;
				}
			}

		    UniformType getUniformType() override
			{
				return mUniformType;
			}

			void update(int _programId)
			{
				updateValue(_programId, mValue);
			}

		};
	}
}
