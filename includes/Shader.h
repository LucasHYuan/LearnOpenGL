#pragma once
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader {
public:
	unsigned int ID;
	
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		#pragma region read shader code from file
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		#pragma endregion
		#pragma region complie shaders and link
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
					infoLog << std::endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
				infoLog << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" <<
				infoLog << std::endl;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		#pragma endregion
	}

	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) 
	{
		Shader shader(vertexPath, fragmentPath);
		std::string geometryCode;
		std::ifstream gShaderFile;
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;

			gShaderStream << gShaderFile.rdbuf();

			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}
		
		const char* gShaderCode = geometryCode.c_str();
		unsigned int geometry;
		int success;
		char infoLog[512];

		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);

		glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(geometry, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" <<
				infoLog << std::endl;
		}
		ID = shader.ID;
		glAttachShader(ID, geometry);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" <<
				infoLog << std::endl;
		}
		glDeleteShader(geometry);
	}

	void use()
	{
		glUseProgram(ID);
	}
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setMat4(const std::string& name, glm::mat4 value) const {
		int modelLoc = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(value));
	}

	void setVec3(const std::string& name, glm::vec3 vec) const {
		unsigned int location = glGetUniformLocation(ID, name.c_str());
		glUniform3fv(location, 1, glm::value_ptr(vec));
	}
	
	void setVec3(const std::string& name, float f1, float f2, float f3) const {
		unsigned int location = glGetUniformLocation(ID, name.c_str());
		glm::vec3 vec(f1, f2, f3);
		glUniform3fv(location, 1, glm::value_ptr(vec));
	}
private:
};