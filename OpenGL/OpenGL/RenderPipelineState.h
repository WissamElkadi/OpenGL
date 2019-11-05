#pragma once

#include <memory>

#include "Shader.h"
#include "RenderPieplineDescriptor.h"
#include "Texture.h"
#include "Sampler.h"

namespace Render
{
	class RenderPipelineState
	{
	private:
		int mShaderProgramId;
		bool mLinked = false;
		RenderPieplineDescriptor* mRenderPieplineDescriptor;

		void updateTextures()
		{
			for (const auto& tex : mRenderPieplineDescriptor->textures)
			{
				auto texture = tex.first;
				auto sampler = tex.second;

				texture->bind();
				sampler->bind();
				int uniformPosition = glGetUniformLocation(mShaderProgramId, texture->getName().c_str());

				glUniform1i(uniformPosition, texture->getTextureUnitIndex());
			}
		}

	public:

		RenderPipelineState(RenderPieplineDescriptor* _renderPieplineDescriptor)
		{
			mRenderPieplineDescriptor = _renderPieplineDescriptor;
		}

		void link()
		{
			mShaderProgramId = glCreateProgram();

			glAttachShader(mShaderProgramId, mRenderPieplineDescriptor->vertexShader->getShaderId());
			glAttachShader(mShaderProgramId, mRenderPieplineDescriptor->fragmentShader->getShaderId());

			if (mRenderPieplineDescriptor->geometryShader)
				glAttachShader(mShaderProgramId, mRenderPieplineDescriptor->geometryShader->getShaderId());

			glLinkProgram(mShaderProgramId);

			// check for linking errors
			int success;
			char infoLog[512];
			glGetProgramiv(mShaderProgramId, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(mShaderProgramId, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			}

			updateTextures();
		}

		void use()
		{
			for (const auto& tex : mRenderPieplineDescriptor->textures)
			{
				auto texture = tex.first;
				texture->bind();
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
