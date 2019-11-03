#pragma once

#include <fstream>
#include <sstream>
#include <iostream>

namespace Render
{
	namespace GL
	{
		class FileReader
		{
		public:
			static std::string getContent(const char* shaderPath)
			{
				// 1. retrieve the vertex/fragment source code from filePath
				std::string content;
				std::ifstream iFile;
				// ensure ifstream objects can throw exceptions:
				iFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

				try
				{
					// open files
					iFile.open(shaderPath);
					std::stringstream contentStream;
					// read file's buffer contents into streams
					contentStream << iFile.rdbuf();
					// close file handlers
					iFile.close();
					// convert stream into string
					content = contentStream.str();
				}
				catch (std::ifstream::failure e)
				{
					std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
				}

				return content;
			}
		};
	}
}