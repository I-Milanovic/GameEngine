#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


struct Quaternion {
    float cosine; // cosine of half the rotation angle
    glm::vec3 axis; // unit vector scaled by sine of half the angle
};


class ArcballCamera {

public:
    ArcballCamera(glm::vec3 pos);
    float z_axis(float, float);
    glm::vec3 getUnitVector(glm::vec3);
    float dotProduct();
    void rotation();
    void replace();

public:
    glm::vec3 position = glm::vec3(0.0f, -1.0f, -3.0f);
    glm::vec3 startPos;
    glm::vec3 currentPos = startPos;
    glm::vec3 startPosUnitVector;
    glm::vec3 currentPosUnitVector;

    Quaternion currentQuaternion;
    Quaternion lastQuaternion = { 0.0f, glm::vec3(1.0f, 0.0f, 0.0f) };

    float cosValue, cosValue_2;
    float theta;
    float angle = 180.0f;
    glm::vec3 rotationalAxis = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 rotationalAxis_2;

   
public:
    const float RADIUS = 1.0f; // radius of the sphere
    bool flag = false; // a signal for mouse click.

};
