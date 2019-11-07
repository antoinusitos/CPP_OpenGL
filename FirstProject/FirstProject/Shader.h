#pragma once

// include glad to get all the required OpenGL headers
#include <glad/glad.h>
//#include <glm/glm.hpp>

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

		// print compile errors if any 
		// -----------
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success); 
		if(!success) 
		{ 
			glGetShaderInfoLog(vertex, 512, NULL, infoLog); std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std:: endl; 
		};

		// fragment shader
		// -----------
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
		glCompileShader(fragment);

		// print compile errors if any 
		// -----------
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog); std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		// shader program
		// -----------
		myID = glCreateProgram();
		glAttachShader(myID, vertex);
		glAttachShader(myID, fragment);
		glLinkProgram(myID);

		// check link error
		// -----------
		glGetProgramiv(myID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(myID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

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
	/*void setVec2(const std::string &aName, const glm::vec2 &aValue) const
	{
		glUniform2fv(glGetUniformLocation(myID, aName.c_str()), 1, &aValue[0]);
	}*/
	void setVec2(const std::string &aName, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(myID, aName.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	/*void setVec3(const std::string &aName, const glm::vec3 &aValue) const
	{
		glUniform3fv(glGetUniformLocation(myID, aName.c_str()), 1, &aValue[0]);
	}*/
	void setVec3(const std::string &aName, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(myID, aName.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	/*void setVec4(const std::string &aName, const glm::vec4 &aValue) const
	{
		glUniform4fv(glGetUniformLocation(myID, aName.c_str()), 1, &aValue[0]);
	}*/
	void setVec4(const std::string &aName, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(myID, aName.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	/*void setMat2(const std::string &aName, const glm::mat2 &aMat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(myID, aName.c_str()), 1, GL_FALSE, &aMat[0][0]);
	}*/
	// ------------------------------------------------------------------------
	/*void setMat3(const std::string &aName, const glm::mat3 &aMat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(myID, aName.c_str()), 1, GL_FALSE, &aMat[0][0]);
	}*/
	// ------------------------------------------------------------------------
	/*void setMat4(const std::string &aName, const glm::mat4 &aMat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(myID, aName.c_str()), 1, GL_FALSE, &aMat[0][0]);
	}*/
};

