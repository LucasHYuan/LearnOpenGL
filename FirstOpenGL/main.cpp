#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void InputProcess(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main()
{

	#pragma region init and create window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		//check window
		std::cout << "Window init failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//check GLAD
		std::cout << "GLAD init failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, windowResizeCallback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	#pragma endregion 
	#pragma region create related data
	float vertex[] = {
		-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.3f, 0.6f, 0.2f
	};
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	#pragma endregion
	#pragma region init shader and program
	char vertexPath[] = "VertexShader.vs";
	char fragmentPath[] = "FragmentShader.fs";
	Shader ourShader(vertexPath, fragmentPath);
	#pragma endregion 
	#pragma region mainloop
	while (!glfwWindowShouldClose(window))
	{
		InputProcess(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}
	#pragma endregion 

	glfwTerminate();

	return 0;
}