// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

#include <glad/glad.h> 

#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexBuffer.h"
#include "Drawer.h"
#include "Uniform.h"
#include "UniformBuffer.h"
#include "Device.h"
#include "Texture.h"
#include "Sampler.h"

//std::vector<float> vertices = {
//		0.5f,  0.5f, 0.0f,  // top right
//		0.5f, -0.5f, 0.0f,  // bottom right
//	   -0.5f, -0.5f, 0.0f,  // bottom left
//	   -0.5f,  0.5f, 0.0f   // top left 
//};

std::vector<unsigned int> indices = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

std::vector<float> vertices = {
     // positions		  // coordinates
	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   0.0f, 1.0f	// top left 
};

std::vector<float> textCoordinates = {
	 // coordinates
	 1.0f, 1.0f,   // top right
	 1.0f, 0.0f,   // bottom right
	 0.0f, 0.0f,   // bottom left
	 0.0f, 1.0f	   // top left 
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	int width, height, channel;
	auto imageDataBuffer = Render::FileReader::loadImageData("C:/Users/mohammew/Documents/Wissam/OpenGL/OpenGL/OpenGL/res/wall.jpg", width, height, channel);
	
	Render::TextureDescriptor textureDecriptor;
	textureDecriptor.mipmapped = false;
	textureDecriptor.type = TextureType::TEXTURE_2D;
	textureDecriptor.format = PixelFormat::RGB;
	textureDecriptor.region = Region::regionMake2D(0, 0, width, height);
	textureDecriptor.name = "ourTexture";

	std::unique_ptr<Render::Texture> texture = std::make_unique<Render::Texture>(textureDecriptor);

	PixelData pixelData(imageDataBuffer, PixelFormat::RGB, DataType::UNSIGNED_BYTE);
	texture->replaceRegion(pixelData);

	Render::FileReader::unloadImageData(imageDataBuffer);

	Render::SamplerDescriptor samplerDescriptor;
	samplerDescriptor.textureType = TextureType::TEXTURE_2D;
	samplerDescriptor.sWrap       = TextureWrap::REPEAT;
	samplerDescriptor.tWrap       = TextureWrap::REPEAT;
	samplerDescriptor.magFilter   = TextureFilter::LINEAR;
	samplerDescriptor.minFilter   = TextureFilter::LINEAR;

	std::unique_ptr<Render::Sampler> textureSampler = std::make_unique<Render::Sampler>(samplerDescriptor);

	std::unique_ptr<Render::Shader> vertexShader = std::make_unique<Render::Shader>("C:/Users/mohammew/Documents/Wissam/OpenGL/OpenGL/OpenGL/res/triangle.ver.glsl", ShaderType::VERTEX);
	std::unique_ptr<Render::Shader> fragmentShader = std::make_unique<Render::Shader>("C:/Users/mohammew/Documents/Wissam/OpenGL/OpenGL/OpenGL/res/triangle.frag.glsl", ShaderType::FRAGMENT);


	// Vertex Buffer Descriptor
	Render::VertexDescriptor vertexDescriptor;
	vertexDescriptor.attributes.resize(2);
	vertexDescriptor.layouts.resize(1);

	vertexDescriptor.attributes[0].type = Type::FLOAT;
	vertexDescriptor.attributes[0].count = 3;
	vertexDescriptor.attributes[0].bufferIndex = 0;
	vertexDescriptor.attributes[0].offset = 0;
	vertexDescriptor.attributes[1].type = Type::FLOAT;
	vertexDescriptor.attributes[1].count = 2;
	vertexDescriptor.attributes[1].bufferIndex = 0;
	vertexDescriptor.attributes[1].offset = MemoryLayout<MemoryFormat::FLOAT3>::stride();

	vertexDescriptor.layouts[0].stride = MemoryLayout<MemoryFormat::FLOAT3>::stride() + MemoryLayout<MemoryFormat::FLOAT2>::stride();

	std::vector<std::vector<float>>verticesList;
	verticesList.push_back(vertices);
	std::unique_ptr<Render::VertexBuffer> vertexBuffer = std::make_unique<Render::VertexBuffer>(vertexDescriptor, verticesList, indices);

	std::vector<Render::UniformBuffer*> uniformBuffers;
	std::vector<float> color = { 0.f, 1.0f, 0.0f, 1.0f };
	std::unique_ptr<Render::UniformBuffer> colorUniformBuffer = std::make_unique<Render::Uniform<float>>("ourColor", MemoryFormat::FLOAT4, color.data());
    uniformBuffers.push_back(colorUniformBuffer.get());

	std::unique_ptr<Render::RenderPieplineDescriptor> renderPieplineDescriptor = std::make_unique<Render::RenderPieplineDescriptor>();
	renderPieplineDescriptor->vertexShader = vertexShader.get();
	renderPieplineDescriptor->fragmentShader = fragmentShader.get();
	renderPieplineDescriptor->textures = { { texture.get() , textureSampler.get()} };

	std::unique_ptr<Render::RenderPipelineState> renderPipelineState = std::make_unique<Render::RenderPipelineState>(renderPieplineDescriptor.get());

	std::unique_ptr<Render::Drawer> triangleDrawer = std::make_unique<Render::Drawer>();
	triangleDrawer->setViewPort(0, 0, 800, 600);
	triangleDrawer->setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	triangleDrawer->setVertexBuffer(vertexBuffer.get());
	triangleDrawer->setRenderPipelineState(renderPipelineState.get());
	triangleDrawer->setUniformBuffers(uniformBuffers);

	std::vector<float> red = { 1.0f, 0.0f, 0.0f, 1.0f };

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// draw our first triangle
		triangleDrawer->drawElements(DrawingPrimitive::TRIANGLES, Type::UNSIGNED_INT, indices.size());
		//dynamic_cast<Render::Uniform<float>*>(colorUniformBuffer.get())->updateValue(red.data());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
