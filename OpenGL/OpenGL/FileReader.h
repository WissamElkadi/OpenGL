#pragma once

#include <fstream>
#include <sstream>
#include <iostream>

#include <stb_image.h>

namespace Render
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

		static unsigned char* loadImageData(const char* imagePath, int& _width, int& _height, int& _nrChannels)
		{
			unsigned char *_dataBuffer = stbi_load(imagePath, &_width, &_height, &_nrChannels, 0);

			return _dataBuffer;
		}

		static void unloadImageData(unsigned char *_dataBuffer)
		{
			stbi_image_free(_dataBuffer);

		}
	};
}