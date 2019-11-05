#pragma once

#include<string>

#include<glad/glad.h>

#include "Types.h"
#include "UniformBuffer.h"
namespace Render
{
	template<typename T>
	class Uniform : public UniformBuffer
	{
	private:
		T*          mValue;
		std::string mName;
		MemoryFormat mMemoryFormat;

	public:
		Uniform(std::string _name, MemoryFormat _MemoryFormat)
		{
			mName = _name;
			mMemoryFormat = _MemoryFormat;
		}

		Uniform(std::string _name, MemoryFormat _MemoryFormat, T* _value)
		{
			mName = _name;
			mMemoryFormat = _MemoryFormat;
			mValue = _value;
		}

		template<typename T>
		void updateValue(T* _value)
		{
			mValue = _value;
		}

		template<typename T>
		void updateValue(int _programId, const T* _value)
		{
			int uniformLocation = glGetUniformLocation(_programId, mName.c_str());

			switch (mMemoryFormat)
			{
			case MemoryFormat::FLOAT1:
				glUniform1f(uniformLocation, *_value);
				break;
			case MemoryFormat::FLOAT2:
				glUniform2f(uniformLocation, _value[0], _value[1]);
				break;
			case MemoryFormat::FLOAT3:
				glUniform3f(uniformLocation, _value[0], _value[1], _value[2]);
				break;
			case MemoryFormat::FLOAT4:
				glUniform4f(uniformLocation, _value[0], _value[1], _value[2], _value[3]);
				break;
			case MemoryFormat::INT1:
				glUniform1i(uniformLocation, *_value);
				break;
			case MemoryFormat::INT2:
				glUniform2i(uniformLocation, _value[0], _value[1]);
				break;
			case MemoryFormat::INT3:
				glUniform3i(uniformLocation, _value[0], _value[1], _value[2]);
				break;
			case MemoryFormat::INT4:
				glUniform4i(uniformLocation, _value[0], _value[1], _value[2], _value[3]);
				break;
			case MemoryFormat::VEC_FLOAT_1:
				glUniform1fv(uniformLocation, 1, _value);
				break;
			case MemoryFormat::VEC_FLOAT_2:
				glUniform2fv(uniformLocation, 1, _value);
				break;
			case MemoryFormat::VEC_FLOAT_3:
				glUniform3fv(uniformLocation, 1, _value);
				break;
			case MemoryFormat::VEC_FLOAT_4:
				glUniform4fv(uniformLocation, 1, _value);
				break;
				/*case MemoryFormat::VEC_INT_1:
					glUniform1iv(uniformLocation, 1, _value);
					break;
				case MemoryFormat::VEC_INT_2:
					glUniform2iv(uniformLocation, 1, _value);
					break;
				case MemoryFormat::VEC_INT_3:
					glUniform3iv(uniformLocation, 1, _value);
					break;
				case MemoryFormat::VEC_INT_4:
					glUniform4iv(uniformLocation, 1, _value);
					break;*/
			case MemoryFormat::MAT_FLOAT_2X2:
				glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, _value);
				break;
			case MemoryFormat::MAT_FLOAT_3X3:
				glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, _value);
				break;
			case MemoryFormat::MAT_FLOAT_4X4:
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, _value);
				break;
			default:
				break;
			}
		}

		MemoryFormat getMemoryFormat() override
		{
			return mMemoryFormat;
		}

		void update(int _programId)
		{
			updateValue(_programId, mValue);
		}

	};
}
