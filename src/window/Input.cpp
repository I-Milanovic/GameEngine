#include <iostream>
//#include "Window.h"
#include "Input.h"

Input::Input(SceneRenderer& sceneRenderer, Hud& hud)
	: m_sceneRenderer(sceneRenderer), m_hud(hud) {
}

void Input::keyboardInput(GLFWwindow* windowHandle, const float& const deltaTime, double xpos, double ypos) {
	float cameraSpeed = static_cast<float>(2.5 * m_deltaTime);

	//if (glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_PRESS)
	//	m_sceneRenderer.m_scene().m_quatCamera.cameraMove(CameraMovement1::FORWARD1, deltaTime);
 //   if (glfwGetKey(windowHandle, GLFW_KEY_S) == GLFW_PRESS)
	//	m_sceneRenderer.m_scene().m_quatCamera.cameraMove(CameraMovement1::BACKWARD1, deltaTime);
 //   if (glfwGetKey(windowHandle, GLFW_KEY_A) == GLFW_PRESS)
	//	m_sceneRenderer.m_scene().m_quatCamera.cameraMove(CameraMovement1::LEFT1, deltaTime);
 //   if (glfwGetKey(windowHandle, GLFW_KEY_D) == GLFW_PRESS)
	//	m_sceneRenderer.m_scene().m_quatCamera.cameraMove(CameraMovement1::RIGHT1, deltaTime);

	QuatCamera& m_quatCamera = m_sceneRenderer.m_scene.m_quatCamera;
	float xPosition = static_cast<float>(xpos);
	float yPosition = static_cast<float>(ypos);

	if (m_isFirstMouse) {
		m_lastX = xPosition;
		m_lastY = yPosition;
		m_isFirstMouse = false;
		//calcNDC(xpos, ypos, m_quatCamera.startPos);
	}

	float offsetX = xPosition - m_lastX;
	float offsetY = m_lastY - yPosition; // reversed since y-coordinate go from bottom to top

//	std::cout << offsetX << " " << offsetY << std::endl;

	m_sceneRenderer.m_scene.m_quatCamera.cameraMove(offsetX, offsetY, deltaTime);

	m_lastX = xPosition;
	m_lastY = yPosition;
}

//static glm::vec3 dir = glm::vec3(1.0f, 0.0f, 0.0f);

void Input::mouseInputOld(double xpos, double ypos) {
	QuatCamera& m_quatCamera = m_sceneRenderer.m_scene.m_quatCamera;
	float xPosition = static_cast<float>(xpos);
	float yPosition = static_cast<float>(ypos);

	if (m_isFirstMouse) {
		m_lastX = xPosition;
		m_lastY = yPosition;
		m_isFirstMouse = false;
		//calcNDC(xpos, ypos, m_quatCamera.startPos);
	}

	float offsetX = xPosition - m_lastX;
	float offsetY = m_lastY - yPosition; // reversed since y-coordinate go from bottom to top

	m_quatCamera.pitch += 0.01f * -offsetY;
	m_quatCamera.yaw += 0.01f * offsetX;

	m_quatCamera.rotation();

	m_lastX = xPosition;
	m_lastY = yPosition;


}
// Calculates ndc position from screen coordinates
void Input::calcNDC(double xpos, double ypos, glm::vec3& vec) {
	float xPosition = static_cast<float>(xpos) - m_hud.m_sceneViewport.m_screenPos.x;
	float yPosition = static_cast<float>(ypos) - m_hud.m_sceneViewport.m_screenPos.y;

	float viewportWidth = m_hud.m_sceneViewport.m_viewPortSize.x;
	float viewportHeight = m_hud.m_sceneViewport.m_viewPortSize.y;

	QuatCamera& m_quatCamera = m_sceneRenderer.m_scene.m_quatCamera;

	//vec.x = xPosition / viewportWidth;
	//vec.y = yPosition / viewportHeight;
	//vec.z = m_quatCamera.z_axis(m_quatCamera.startPos.x, m_quatCamera.startPos.y);

	vec.x = ((xPosition - (viewportWidth / 2)) / (viewportWidth / 2));
	vec.y = (((viewportHeight / 2) - yPosition) / (viewportHeight / 2));
//	vec.z = m_quatCamera.z_axis(m_quatCamera.startPos.x, m_quatCamera.startPos.y);
	vec.z = 0;


//	std::cout << vec.x << " " << vec.y << " " << vec.y << std::endl;
}


static double oldX = 0, oldY = 0;

void Input::mouseInput(double xpos, double ypos) {
	if (!m_hud.m_sceneViewport.m_isHovered)
		return;
	float xPosition = static_cast<float>(xpos) - m_hud.m_sceneViewport.m_screenPos.x;
	float yPosition = static_cast<float>(ypos) - m_hud.m_sceneViewport.m_screenPos.y;
	
	float viewportWidth = m_hud.m_sceneViewport.m_viewPortSize.x;
	float viewportHeight = m_hud.m_sceneViewport.m_viewPortSize.y;

	double normalizedX = -1.0 + 2.0 * (double)xPosition / (double)viewportWidth;
	double normalizedY = 1.0 - 2.0 * (double)yPosition / (double)viewportHeight;

	//std::cout << normalizedX << " " << normalizedY << std::endl;
}

void Input::deltaMove(double xpos, double ypos) {

	oldX = xpos - oldX;
	oldY -= ypos;
//	std::cout << oldX << " " << oldY << std::endl;
	oldX = xpos;
	oldY = ypos;
}

void Input::dragAction(double startXPos, double startYPos){
//	if (!m_hud.m_sceneViewport.m_isHovered)
//		return;
//	float xPosition = static_cast<float>(startXPos) - m_hud.m_sceneViewport.m_screenPos.x;
//	float yPosition = static_cast<float>(startYPos) - m_hud.m_sceneViewport.m_screenPos.y;
//
//	float viewportWidth = m_hud.m_sceneViewport.m_viewPortSize.x;
//	float viewportHeight = m_hud.m_sceneViewport.m_viewPortSize.y;
//
//
//	ArcballCamera& arcCamera = m_sceneRenderer.m_scene.getArcCamera();
//	// convert to NDC, then assign to startPos.
//	arcCamera.startPos.x = ((xPosition - (viewportWidth / 2)) / (viewportWidth / 2)) * arcCamera.RADIUS;
//	arcCamera.startPos.y = (((viewportHeight / 2) - yPosition) / (viewportHeight / 2)) * arcCamera.RADIUS;
//	arcCamera.startPos.z = arcCamera.z_axis(arcCamera.startPos.x, arcCamera.startPos.y);
//
////	std::cout << arcCamera.startPos.x << " " << arcCamera.startPos.y << " "<< arcCamera.startPos.z << std::endl;
//
//
//	arcCamera.flag = true;
}

void Input::moveAction(double xpos, double ypos) {
	//if (!m_hud.m_sceneViewport.m_isHovered)
	//	return;
	//float xPosition = static_cast<float>(xpos) - m_hud.m_sceneViewport.m_screenPos.x;
	//float yPosition = static_cast<float>(ypos) - m_hud.m_sceneViewport.m_screenPos.y;
	////std::cout << xPosition << " " << yPosition << std::endl;

	//float viewportWidth = m_hud.m_sceneViewport.m_viewPortSize.x;
	//float viewportHeight = m_hud.m_sceneViewport.m_viewPortSize.y;

	//ArcballCamera& arcCamera = m_sceneRenderer.m_scene.getArcCamera();
	//if (arcCamera.flag == false)
	//	return;

	//// get the screen coordintates when mouse clicks
	//arcCamera.currentPos.x = ((xPosition - (viewportWidth / 2)) / (viewportWidth / 2)) * arcCamera.RADIUS;
	//arcCamera.currentPos.y = (((viewportHeight / 2) - yPosition) / (viewportHeight / 2)) * arcCamera.RADIUS;
	//arcCamera.currentPos.z = arcCamera.z_axis(arcCamera.currentPos.x, arcCamera.currentPos.y);

	////std::cout << arcCamera.currentPos.x << " " << arcCamera.currentPos.y << " "<< arcCamera.currentPos.z << std::endl;

	//arcCamera.rotation();
}

void Input::arcReplace() {
//	m_sceneRenderer.m_scene().getArcCamera().replace();
//	m_sceneRenderer.m_scene().getArcCamera().flag = false;

	m_sceneRenderer.m_scene.m_quatCamera.replace();
}


void Input::scrollInput(double offsetX, double offsetY) {
//	m_sceneRenderer.m_scene.getCamera().cameraZoom(static_cast<float>(offsetY));
}

void Input::keyInput() {

}
