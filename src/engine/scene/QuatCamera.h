#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "CameraAbstract.h"

enum CameraMovement1 {
    FORWARD1,
    BACKWARD1,
    LEFT1,
    RIGHT1
};

class QuatCamera : public CameraAbstract {

public:
    QuatCamera(glm::vec3 pos);
    ~QuatCamera();

    virtual void moveForward(const float distance) override;
    virtual void moveHorizontal(const float distance) override;
    virtual void moveVertical(const float distance) override;

    virtual void rotateYaw(const float radians) override;
    virtual void rotatePitch(const float radians) override;
    virtual void rotateRoll(const float radians) override;

public:
    virtual glm::vec3 getPosition() const override;
    virtual glm::vec3 getForwardVector() const override;

    virtual float getAngleYaw() const override;
    virtual float getAnglePitch() const override;
    virtual float getAngleRoll() const override;

    virtual glm::mat4 getViewMatrix() const override;

public:
    glm::vec3 m_position = glm::vec3(0.0f);
    glm::quat m_orientation;
    glm::quat m_quatPitch;
    glm::quat m_quatYaw;

};
