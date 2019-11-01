#pragma once

#include <unordered_map>

#include <glad/glad.h> 

#include "Types.h"

namespace Render
{
	namespace GL
	{
		std::unordered_map<Type, GLenum> TypeMapper =
		{
	        {Type::BYTE           ,  GL_BYTE          },
			{Type::UNSIGNED_BYTE  ,  GL_UNSIGNED_BYTE },
	        {Type::SHORT          ,  GL_SHORT         },
	        {Type::UNSIGNED_SHORT ,  GL_UNSIGNED_SHORT},
	        {Type::INT            ,  GL_INT           },
	        {Type::UNSIGNED_INT   ,  GL_UNSIGNED_INT  },
	        {Type::FLOAT		  ,  GL_FLOAT         }

		};

		std::unordered_map<ShaderType, GLenum> ShaderTypeMapper =
		{
			{ShaderType::VERTEX   ,GL_VERTEX_SHADER  },
			{ShaderType::GEOMETRY ,GL_GEOMETRY_SHADER},
			{ShaderType::FRAGMENT ,GL_FRAGMENT_SHADER}
		};


		std::unordered_map<DrawingPrimitive, GLenum> DrawingPrimitiveMapper =
		{
			{ DrawingPrimitive::POINTS         ,  GL_POINTS 		    },
			{ DrawingPrimitive::LINES          ,  GL_LINES 		        },
			{ DrawingPrimitive::LINE_LOOP      ,  GL_LINE_LOOP 	        },
			{ DrawingPrimitive::LINE_STRIP     ,  GL_LINE_STRIP  	    },
			{ DrawingPrimitive::TRIANGLES      ,  GL_TRIANGLES    	    },
			{ DrawingPrimitive::TRIANGLE_STRIP ,  GL_TRIANGLE_STRIP     },
			{ DrawingPrimitive::TRIANGLE_FAN   ,  GL_TRIANGLE_FAN       }
		};

	}
}
