#pragma once

namespace Hazel {

	class OrthographyCamera
	{
	public:
		//默认 near 和far的值
		OrthographyCamera(float left, float right, float bottom, float top);

	public:
		const glm::mat4& GetProjMatrix() { return m_ProjectionMat; }
		const glm::mat4& GetViewMatrix() { return m_ViewMat; }
		const glm::mat4& GetViewProjMatrix() { return m_ViewMat; }

		void SetPos(const glm::vec3& pos) { m_Position = pos; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		const glm::vec3& GetPos() { return m_Position; }
		float GetRotation() { return m_Rotation; }

	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMat;
		glm::mat4 m_ViewMat;
		glm::mat4 m_ViewProjectionMat;

		glm::vec3 m_Position = { 0,0,0 };
		float m_Rotation = 0.0f;
	};

}


