//This program sets up directx and then draws 2 triangles, one is orange and the other is yellow, we use 2 different fragment shaders to get the different colors


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

void setUpVBOAndVAO(unsigned int& VAO, unsigned int& VBO, const float* vertices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Bind vertex array object then bind and set vertex buffer(s), and then configure vertex attributes
	glBindVertexArray(VAO);

	//copy out vertices array in a buffer for opengl to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//then set our vertex attribute pointers, 
	//this tells opengl how to interpret our data we give it (which is the vertices array)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//note that this is allowed, the call to glVertexAttribPointer registered VBO as
	//the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//you can unbind the VAO afterwards so other VAO calls wont accidentally modify this VAO but this rarely happens
	glBindVertexArray(0);
}

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* orangeShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* yellowShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

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
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad:load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	//build and compile shader program
	//vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Fragment shader
	unsigned int orangeShader;
	unsigned int yellowShader;
	unsigned int orangeShaderProgram;
	unsigned int yellowShaderProgram;

	//Orange shader program
	//----------------------------------------------------------------------------------------
	orangeShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(orangeShader, 1, &orangeShaderSource, NULL);
	glCompileShader(orangeShader);
	//link shaders
	orangeShaderProgram = glCreateProgram();
	glAttachShader(orangeShaderProgram, vertexShader);
	glAttachShader(orangeShaderProgram, orangeShader);
	glLinkProgram(orangeShaderProgram);

	//Yellow shader Program
	//-----------------------------------------------------------------------------------------
	yellowShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowShader, 1, &yellowShaderSource, NULL);
	glCompileShader(yellowShader);
	//Link shaders
	yellowShaderProgram = glCreateProgram();
	glAttachShader(yellowShaderProgram, vertexShader);
	glAttachShader(yellowShaderProgram, yellowShader);
	glLinkProgram(yellowShaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(orangeShader);
	glDeleteShader(yellowShader);

	//set up our vertex data and buffers and configure vertex attributes
	const float firstTriangle[] = {
		-0.6f,	 -0.7f, 0.0f,	//left
		-0.3f,	 -0.7f, 0.0f,	//right
		-0.45f, -0.4f, 0.0f,	//top
	};

	const float secondTriangle[] = {
		0.6f,  -0.7f, 0.0f,		//right
		0.3f,  -0.7f, 0.0f,		//left
		0.45f, -0.4f, 0.0f		//top
	};

	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	//First triangle setup
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//We dont need to unbind because we vind another thing right after this


	//Second triangle setup
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Use orange shader
		glUseProgram(orangeShaderProgram);
		//Draw the first triangle
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Use Yellow Shader
		glUseProgram(yellowShaderProgram);
		//Draw second triangle
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(orangeShaderProgram);

	glfwTerminate();
	return 0;
}