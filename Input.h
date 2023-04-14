#pragma once

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

class Input {

	public:
		GLFWwindow* window;
		bool firstMouse = true;

		Input(GLFWwindow* window);
		void move(float& deltaTime, glm::vec3& cameraPos, glm::vec3& cameraUp, glm::vec3& cameraFront);



};
