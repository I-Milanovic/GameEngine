#include <iostream>
#include "Window.h"
#include "Input.h"

Input::Input(SceneRenderer& scene) : m_scene(scene) {
}

void Input::keyboardInput(GLFWwindow* windowHandle, const float& const const deltaTime, glm::vec3& cameraPos) {
	float cameraSpeed = static_cast<float>(2.5 * deltaTime);

 //   GLFWwindow* windowHandle = m_window.getWindowHandle();

    if (glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_PRESS)
        m_scene.getCamera().cameraMove(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(windowHandle, GLFW_KEY_S) == GLFW_PRESS)
        m_scene.getCamera().cameraMove(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(windowHandle, GLFW_KEY_A) == GLFW_PRESS)
        m_scene.getCamera().cameraMove(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(windowHandle, GLFW_KEY_D) == GLFW_PRESS)
        m_scene.getCamera().cameraMove(CameraMovement::RIGHT, deltaTime);
}


void Input::mouseInput(double xpos, double ypos) {
	float xPosition = static_cast<float>(xpos);
	float yPosition = static_cast<float>(ypos);

	if (m_isFirstMouse) {
		m_lastX = xPosition;
		m_lastY = yPosition;
		m_isFirstMouse = false;
	}

	float offsetX = xPosition - m_lastX;
	float offsetY = m_lastY - yPosition; // reversed since y-coordinate go from bottom to top

	m_lastX = xPosition;
	m_lastY = yPosition;

	m_scene.getCamera().cameraRotate(offsetX, offsetY);

}

void Input::scrollInput(double offsetX, double offsetY) {
	m_scene.getCamera().cameraZoom(static_cast<float>(offsetY));
}

void Input::keyInput() {

}
