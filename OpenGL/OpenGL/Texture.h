#pragma once

#include <stdint.h>
#include <math.h>
#include <algorithm>

#include <glad/glad.h>

#include "Types.h"
#include "DataStructure.h"
#include "Mapper.h"
#include "TextureDescriptor.h"

namespace Render
{
	class Texture
	{
	public:
		Texture(TextureDescriptor _descriptor)
		{
			mDescriptor = _descriptor;
			
			for (const auto& ele : TextureUnitMapper)
			{
				if (ele.second.second == mTextureUnitProvider)
				{
					mTextureUnit = ele.first;
					break;
				}
			}

			mTextureUnitProvider++;
			glGenTextures(1, &mTextureId);
			// int mipmapLevel = floor(log2(std::max(_descriptor.width, _descriptor.height)));
		}

		void replaceRegion(PixelData _withPixelData)
		{
			bind();

			switch (mDescriptor.type)
			{
			case TEXTURE_1D:
				glTexImage1D(GL_TEXTURE_1D, 0, PixelFormatMapper.at(mDescriptor.format), mDescriptor.region.size.width, 0,
					PixelFormatMapper.at(_withPixelData.format), DataTypeMapper.at(_withPixelData.type), _withPixelData.data);
				if (mDescriptor.mipmapped)
				{
					glGenerateMipmap(GL_TEXTURE_1D);
				}
				break;
			case TEXTURE_2D:
				glTexImage2D(GL_TEXTURE_2D, 0, PixelFormatMapper.at(mDescriptor.format), mDescriptor.region.size.width, mDescriptor.region.size.height, 0,
					PixelFormatMapper.at(_withPixelData.format), DataTypeMapper.at(_withPixelData.type), _withPixelData.data);
				if (mDescriptor.mipmapped)
				{
					glGenerateMipmap(GL_TEXTURE_2D);
				}
				break;
			case TEXTURE_3D:
				glTexImage3D(GL_TEXTURE_3D, 0, PixelFormatMapper.at(mDescriptor.format), mDescriptor.region.size.width, mDescriptor.region.size.height,
					mDescriptor.region.size.depth, 0, PixelFormatMapper.at(_withPixelData.format), DataTypeMapper.at(_withPixelData.type), _withPixelData.data);

				if (mDescriptor.mipmapped)
				{
					glGenerateMipmap(GL_TEXTURE_3D);
				}
				break;
			default:
				break;
			}
			unbind();
		}

		void bind()
		{
			glActiveTexture(TextureUnitMapper.at(mTextureUnit).first);
			glBindTexture(TextureTypeMapper.at(mDescriptor.type), mTextureId);
		}

		void unbind()
		{
			glBindTexture(TextureTypeMapper.at(mDescriptor.type), 0);
		}

		std::string getName()
		{
			return mDescriptor.name;
		}

		int getTextureUnitIndex()
		{
			return TextureUnitMapper.at(mTextureUnit).second;
		}

		unsigned int getId()
		{
			return mTextureId;
		}

	private:
		unsigned int      mTextureId;
		TextureDescriptor mDescriptor;
		int               mCurrentTextureUnit;
		TextureUnit       mTextureUnit;
		static   int      mTextureUnitProvider;
	};

	int Texture::mTextureUnitProvider = 0;
}
