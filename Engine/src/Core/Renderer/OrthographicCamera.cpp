#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace RealEngine
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        :m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f))
    {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}
