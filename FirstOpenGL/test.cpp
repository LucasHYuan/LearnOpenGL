#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//int main()
//{
	//glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//if (window == NULL) {
	//	std::cout << "Failed to create GLFW window" << std::endl;
	//	glfwTerminate();
	//	return -1;
	//}
	//glfwMakeContextCurrent(window);


	//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	//{
	//	std::cout << "Failed to initialize GLAD" << std::endl;
	//	return -1;
	//}

	//glfwSetFramebufferSizeCallback(window, frambuffer_size_callback);

	//glViewport(0, 0, 800, 600);

	//float vertax[] = {
	//	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
	//	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
	//};

	//unsigned int indices[] = {
	//	0, 1, 3,
	//	1, 2, 3
	//};
	//
	//float v[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	-0.5f, 0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	-0.5f, 0.5f, 0.0f,
	//	0.5f, 0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f
	//};

	//

	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);
	//unsigned int VBO;
	//glGenBuffers(1, &VBO);
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);

	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertax), vertax, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//int success;
	//char log[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, log);
	//	std::cout << "failure on vertex shader" << std::endl;
	//	std::cout << log << std::endl;
	//}

	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success) 
	//{
	//	std::cout << "failure on fragment shader" << std::endl;
	//	glGetShaderInfoLog(vertexShader, 512, NULL, log);
	//	std::cout << log << std::endl;
	//}

	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, log);
	//	std::cout << "failure on link program" << std::endl;
	//	std::cout << log << std::endl;
	//}
	////glUseProgram(shaderProgram);
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	//
	////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//
	//while (!glfwWindowShouldClose(window))
	//{
	//	processInputKey(window);

	//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	glUseProgram(shaderProgram);

	//	glBindVertexArray(VAO);
	//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	glBindVertexArray(0);

	//	
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}


	//glfwTerminate();
//	return 0;
//
//}
