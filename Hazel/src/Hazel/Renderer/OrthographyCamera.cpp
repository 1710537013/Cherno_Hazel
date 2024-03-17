#include "hzpch.h"
#include "OrthographyCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	OrthographyCamera::OrthographyCamera(float left, float right, float bottom, float top)
		:m_ProjectionMat(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMat(1.0f)
	{
		m_ViewProjectionMat = m_ProjectionMat * m_ViewMat;
	}

	void OrthographyCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMat = glm::inverse(transform);

		m_ViewProjectionMat = m_ProjectionMat * m_ViewMat;
	}

}

