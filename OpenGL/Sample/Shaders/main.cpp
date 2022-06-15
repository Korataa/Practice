#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../Utility/Shader.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GLFW window creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad:load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//set up our vertex data and buffers and configure vertex attributes
	const float vertices[] = {
		//positions				//colors
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	//bottom right
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	//bottom left
		 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f	//top
	};

	//Create Shader program
	Shader ourShader("ShaderFiles/shader.vs", "ShaderFiles/shader.fs");

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Bind vertex array object then bind and set vertex buffer(s), and then configure vertex attributes
	glBindVertexArray(VAO);

	//copy out vertices array in a buffer for opengl to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);						//This gives us a stride value of 6 times the size of a float in bytes (= 24 bytes). 
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));		//last param is offset, we calc it by getting half of the stride value (= 12 bytes)
	glEnableVertexAttribArray(1);

	//note that this is allowed, the call to glVertexAttribPointer registered VBO as
	//the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//you can unbind the VAO afterwards so other VAO calls wont accidentally modify this VAO but this rarely happens
	glBindVertexArray(0);


	while(!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Activate shader
		ourShader.use();

		//draw the object
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		ourShader.setFloat("ourColor", greenValue);
		ourShader.setFloat("rightOffset", 0.5f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}