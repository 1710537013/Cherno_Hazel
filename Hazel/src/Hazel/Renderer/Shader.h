#pragma once
#include <string>

class Shader
{
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	void Bind() const;
	void UnBind() const;
	~Shader();
private:
	uint32_t m_ShaderID;
};

