#include <iostream>
//#include "Window.h"
#include "Input.h"

Input::Input(SceneRenderer& sceneRenderer, Hud& hud)
	: m_sceneRenderer(sceneRenderer), m_hud(hud) {
}

void Input::keyboardInput(GLFWwindow* windowHandle, const float& const deltaTime, double xpos, double ypos) {
	float cameraSpeed = static_cast<float>(2.5 * m_deltaTime);


	CameraAbstract& camera = m_sceneRenderer.m_scene.getCamera();

	float xPosition = static_cast<float>(xpos);
	float yPosition = static_cast<float>(ypos);

	if (m_isFirstMouse) {
		m_lastX = xPosition;
		m_lastY = yPosition;
		m_isFirstMouse = false;
	}

	float offsetX = xPosition - m_lastX;
	float offsetY =  m_lastY - yPosition;

	float spd = 0.01f;
	float flipAxisDirection = -1.0f;

	camera.moveHorizontal(offsetX * spd * flipAxisDirection);
	camera.moveVertical(offsetY * spd * flipAxisDirection);

	m_lastX = xPosition;
	m_lastY = yPosition;
}

void Input::mouseInputOld(double xpos, double ypos) {
	CameraAbstract& camera = m_sceneRenderer.m_scene.getCamera();
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

	camera.rotateYaw(0.01f * offsetX);
	camera.rotatePitch(0.01f * -offsetY);

	m_lastX = xPosition;
	m_lastY = yPosition;


}

void Input::scrollInput(double offsetX, double offsetY) {
	m_sceneRenderer.m_scene.getCamera().moveForward(offsetY * 0.5f);

}


// Calculates ndc m_position from screen coordinates
void Input::calcNDC(double xpos, double ypos, glm::vec3& vec) {
	float xPosition = static_cast<float>(xpos) - m_hud.m_sceneViewport.m_screenPos.x;
	float yPosition = static_cast<float>(ypos) - m_hud.m_sceneViewport.m_screenPos.y;

	float viewportWidth = m_hud.m_sceneViewport.m_viewPortSize.x;
	float viewportHeight = m_hud.m_sceneViewport.m_viewPortSize.y;

//	QuatCamera& m_quatCamera = m_sceneRenderer.m_scene.m_quatCamera;

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



