// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

#include <glad/glad.h> 

#include <GLFW/glfw3.h>

#include "Shader.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "Drawer.h"
#include "Uniform.h"
#include "UniformBuffer.h"


const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

std::vector<float> vertices = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f,  // bottom left
	   -0.5f,  0.5f, 0.0f   // top left 
};
std::vector<unsigned int> indices = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
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


	std::unique_ptr<Render::GL::Shader> vertexShader = std::make_unique<Render::GL::Shader>("C:/Users/mohammew/Documents/Wissam/OpenGL/OpenGL/OpenGL/res/triangle.ver.glsl", ShaderType::VERTEX);
	std::unique_ptr<Render::GL::Shader> fragmentShader = std::make_unique<Render::GL::Shader>("C:/Users/mohammew/Documents/Wissam/OpenGL/OpenGL/OpenGL/res/triangle.frag.glsl", ShaderType::FRAGMENT);

	std::unique_ptr<Render::GL::RenderPipeline> renderPipeline = std::make_unique<Render::GL::RenderPipeline>();

	renderPipeline->vertexShader = std::move(vertexShader);
	renderPipeline->fragmentShader = std::move(fragmentShader);

	std::unique_ptr<Render::GL::VertexBuffer> vertexBuffer = std::make_unique<Render::GL::VertexBuffer>(vertices, indices);

	std::vector<Render::GL::UniformBuffer*> uniformBuffers;
	std::vector<float> color = { 0.f, 1.0f, 0.0f, 1.0f };
	std::unique_ptr<Render::GL::UniformBuffer> colorUniformBuffer = std::make_unique<Render::GL::Uniform<float>>("ourColor", UniformType::FLOAT_4, color.data());
    uniformBuffers.push_back(colorUniformBuffer.get());

	std::unique_ptr<Render::GL::Drawer> triangleDrawer = std::make_unique<Render::GL::Drawer>();
	triangleDrawer->setViewPort(0, 0, 800, 600);
	triangleDrawer->setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	triangleDrawer->setVertexBuffer(std::move(vertexBuffer));
	triangleDrawer->setRenderPipeline(std::move(renderPipeline));
	triangleDrawer->setUniformBuffers(uniformBuffers);

	std::vector<float> red = { 1.0f, 0.0f, 0.0f, 1.0f };

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// draw our first triangle
		triangleDrawer->drawElements(DrawingPrimitive::TRIANGLES, Type::UNSIGNED_INT, indices.size());
		dynamic_cast<Render::GL::Uniform<float>*>(colorUniformBuffer.get())->updateValue(red.data());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
