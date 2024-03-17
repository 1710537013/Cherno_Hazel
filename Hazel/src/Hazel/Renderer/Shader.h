#pragma once

namespace Hazel {


	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		void Bind() const;
		void UnBind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		~Shader();
	private:
		uint32_t m_ShaderID;
	};

}


