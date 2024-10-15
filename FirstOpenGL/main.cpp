#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

const float WINDOW_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 600.0f;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;
const std::string TEXTURE_PATH = "Assets/Texture/";
float lastX = 400, lastY = 300;
const float sensitivity = 0.1f;
float yaw = -90.0f, pitch = 0.0f;
bool firstMouse = true;
double fov = 45.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
float radius = 10.0f;

float deltaTime = 0.0f, lastFrame = 0.0f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 dir;
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(dir);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (fov >= 1.0f && fov <= 45.0f)
	{
		fov -= yoffset;
	}
	if (fov <= 1.0f) fov = 1.0f;
	if (fov >= 45.0f) fov = 45.0f;
}
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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	#pragma endregion 

	#pragma region init shader and program
	char vertexPath[] = "VertexShader.vs";
	char fragmentPath[] = "FragmentShader.fs";
	Shader ourShader(vertexPath, fragmentPath);
	ourShader.use();
	#pragma endregion 

	#pragma region model matrix

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};
	#pragma endregion

	#pragma region define shape data
	unsigned int VBO;
	glGenVertexArrays(1, &VBO);
	unsigned int VAO;
	glGenBuffers(1, &VAO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	float vertex[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};
	int indices[]{
		0, 1, 2,
		0, 3, 2
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
						5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
						5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glEnable(GL_DEPTH_TEST);
	#pragma endregion

	#pragma region load texture
	const unsigned int texture_count = 3;
	unsigned int textures[texture_count];
	std::string texture_names[]
	{
		"container.jpg",
		"awesomeface.png",
		"wall.jpg"
	};
	glGenTextures(texture_count, textures);
	int width, height, nrChannels;
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture_count"), texture_count);
	for (int i = 0; i < texture_count; ++i)
	{
		unsigned int texture = textures[i];
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		unsigned char* data = stbi_load((TEXTURE_PATH + texture_names[i]).c_str(), &width, &height,
			&nrChannels, 0);
		if (!data)
		{
			std::cout << "Failed to load texture: " <<  texture_names[i] << std::endl;
			return -1;
		}
		else
		{
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;
			else
				format = GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
						GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
			std::string uniformName = "textures[" + std::to_string(i) + "]";
			glUniform1i(glGetUniformLocation(ourShader.ID, uniformName.c_str()), i);
		}
	}
	#pragma endregion


	auto InputProcess = [&]() {
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		float cameraSpeed = 2.5f * deltaTime;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraPos += cameraSpeed * front;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraPos -= cameraSpeed * front;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cameraPos -= cameraSpeed * glm::normalize(glm::cross(front, up));
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraPos += cameraSpeed * glm::normalize(glm::cross(front, up));
		}
	};

	#pragma region mainloop
	while (!glfwWindowShouldClose(window))
	{
		InputProcess();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();
		for (int i = 0; i < texture_count; ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
		}
		
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < sizeof(cubePositions)/sizeof(glm::vec3); ++i) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
				glm::vec3(0.5f, 1.0f, 0.0f));
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle),
								glm::vec3(1.0f, 0.3f, 0.5f));
			glm::mat4 view = glm::lookAt(cameraPos, cameraPos + front, up);
			glm::mat4 projection = glm::perspective(glm::radians((float)fov), WINDOW_WIDTH / WINDOW_HEIGHT,
				NEAR_PLANE, FAR_PLANE);
			ourShader.setMat4("model", model);
			ourShader.setMat4("view", view);
			ourShader.setMat4("projection", projection);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}
	#pragma endregion 

	glfwTerminate();

	return 0;
}