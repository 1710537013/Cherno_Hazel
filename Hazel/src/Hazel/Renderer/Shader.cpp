#include "hzpch.h"
#include "Shader.h"
#include"GLFW/glfw3.h"
#include <glad/glad.h>

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* vertexSource = vertexSrc.c_str();
	const GLchar* fragSource = fragmentSrc.c_str();
	glShaderSource(vertexShader, 1, &vertexSource, 0);
	glCompileShader(vertexShader);
	// check success
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		HZ_CORE_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{0}", infoLog);
	}

	glShaderSource(fragmentShader, 1, &fragSource, 0);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		HZ_CORE_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{0}", infoLog);
	}

	m_ShaderID = glCreateProgram();

	glAttachShader(m_ShaderID, vertexShader);
	glAttachShader(m_ShaderID, fragmentShader);
	glLinkProgram(m_ShaderID);

	glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_ShaderID, 512, NULL, infoLog);
		HZ_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{0}", infoLog);
	}


	glDetachShader(m_ShaderID,vertexShader);
	glDetachShader(m_ShaderID, fragmentShader);
}

void Shader::Bind() const
{
	glUseProgram(m_ShaderID);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderID);
}
