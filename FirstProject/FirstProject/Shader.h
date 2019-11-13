#pragma once

// include glad to get all the required OpenGL headers
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// the program ID
	unsigned int myID;

	// constructor reads and build shaders
	Shader(const GLchar* aVertexPath, const GLchar* aFragmentPath)
	{
		// 1. retreive the vertex/fragment source code from filePath
		// -----------
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		// ensure ifstream objects can throw exceptions
		// -----------
		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// open files
			// -----------
			vertexShaderFile.open(aVertexPath);
			fragmentShaderFile.open(aFragmentPath);
			std::stringstream vertexShaderStream;
			std::stringstream fragmentShaderStream;

			// read file's buffer contents into streams
			// -----------
			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			// close file handlers
			// -----------
			vertexShaderFile.close();
			fragmentShaderFile.close();

			// convert stream into string
			// -----------
			vertexCode = vertexShaderStream.str();
			fragmentCode = fragmentShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vertexShaderCode = vertexCode.c_str();
		const char* fragmentShaderCode = fragmentCode.c_str();

		// 2. compile shader
		// -----------
		unsigned int vertex;
		unsigned int fragment;
		int success;
		char infoLog[512];

		// vertex shader
		// -----------
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexShaderCode, NULL);
		glCompileShader(vertex);

		CheckCompileErrors(vertex, "VERTEX");

		// fragment shader
		// -----------
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
		glCompileShader(fragment);

		CheckCompileErrors(fragment, "FRAGMENT");

		// shader program
		// -----------
		myID = glCreateProgram();
		glAttachShader(myID, vertex);
		glAttachShader(myID, fragment);
		glLinkProgram(myID);

		CheckCompileErrors(myID, "PROGRAM");

		// Delete the shaders objects as we no longer need them
		// -----------
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	// use/activate the shader
	// ------------------------------------------------------------------------
	void Use()
	{
		glUseProgram(myID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void SetBool(const std::string &aName, bool aValue) const
	{
		glUniform1i(glGetUniformLocation(myID, aName.c_str()), (int)aValue);
	}
	// ------------------------------------------------------------------------
	void SetInt(const std::string &aName, int aValue) const
	{
		glUniform1i(glGetUniformLocation(myID, aName.c_str()), aValue);
	}
	// ------------------------------------------------------------------------
	void SetFloat(const std::string &aName, float aValue) const
	{
		glUniform1f(glGetUniformLocation(myID, aName.c_str()), aValue);
	}
	// ------------------------------------------------------------------------
	void SetVec2(const std::string &aName, const glm::vec2 &aValue) const
	{
		glUniform2fv(glGetUniformLocation(myID, aName.c_str()), 1, &aValue[0]);
	}
	void SetVec2(const std::string &aName, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(myID, aName.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void SetVec3(const std::string &aName, const glm::vec3 &aValue) const
	{
		glUniform3fv(glGetUniformLocation(myID, aName.c_str()), 1, &aValue[0]);
	}
	void SetVec3(const std::string &aName, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(myID, aName.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void SetVec4(const std::string &aName, const glm::vec4 &aValue) const
	{
		glUniform4fv(glGetUniformLocation(myID, aName.c_str()), 1, &aValue[0]);
	}
	void SetVec4(const std::string &aName, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(myID, aName.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void SetMat2(const std::string &aName, const glm::mat2 &aMat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(myID, aName.c_str()), 1, GL_FALSE, &aMat[0][0]);
	}
	// ------------------------------------------------------------------------
	void SetMat3(const std::string &aName, const glm::mat3 &aMat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(myID, aName.c_str()), 1, GL_FALSE, &aMat[0][0]);
	}
	// ------------------------------------------------------------------------
	void SetMat4(const std::string &aName, const glm::mat4 &aMat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(myID, aName.c_str()), 1, GL_FALSE, &aMat[0][0]);
	}

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void CheckCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};

