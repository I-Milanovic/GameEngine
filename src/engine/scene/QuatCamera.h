#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


enum CameraMovement1 {
    FORWARD1,
    BACKWARD1,
    LEFT1,
    RIGHT1
};

class QuatCamera {

public:
    QuatCamera(glm::vec3 pos);
    void rotation();
    void cameraMove(float offsetX, float offsetY, float deltaTime);
    void replace();

    void updateViewMatrix();
public:
    float pitch = 0, yaw = 0;
    glm::vec3 position = glm::vec3(0.0f);
    glm::mat4 viewMat = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);

private:
    void updateOrientation();
    glm::quat orientation = glm::quat();
    float m_movementSpeed = 1.0f;
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);


};
