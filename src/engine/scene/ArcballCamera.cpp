#include "ArcballCamera.h"
#include <iostream>


ArcballCamera::ArcballCamera(glm::vec3 pos) : position(pos){
}

float ArcballCamera::z_axis(float x, float y) {
	float z = 0;
	if (sqrt((x * x) + (y * y)) <= RADIUS) 
		z = (float)sqrt((RADIUS * RADIUS) - (x * x) - (y * y));
	return z;
}

glm::vec3 ArcballCamera::getUnitVector(glm::vec3 vector) {
	float magnitude1;
	glm::vec3 unitVector;
	magnitude1 = (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
	magnitude1 = sqrt(magnitude1);
	if (magnitude1 == 0) {
		unitVector.x = 0;
		unitVector.y = 0;
		unitVector.z = 0;
	}
	else {
		unitVector.x = vector.x / magnitude1; // if magnitude 0, then this func gives 'nan' error.
		unitVector.y = vector.y / magnitude1; 
		unitVector.z = vector.z / magnitude1; 

	}
	return unitVector;
}

float ArcballCamera::dotProduct() {
	float result = (startPosUnitVector.x * currentPosUnitVector.x) +
		(startPosUnitVector.y * currentPosUnitVector.y) +
		(startPosUnitVector.z * currentPosUnitVector.z);
	return result;
}

void ArcballCamera::replace() {
	lastQuaternion.cosine = cosValue_2;
	lastQuaternion.axis = rotationalAxis_2;
}

void ArcballCamera::rotation() {
	startPosUnitVector = getUnitVector(startPos);
	currentPosUnitVector = getUnitVector(currentPos);
	currentQuaternion.axis = glm::cross(startPos, currentPos);
	currentQuaternion.axis = getUnitVector(currentQuaternion.axis);

	// calculating rotation angle
	cosValue = dotProduct(); // q0 is cosine of the angle here.
	if (cosValue > 1) cosValue = 1; // when dot product gives '1' as result, it doesn't 
	//equal to 1 actually. It equals to just like 1.00000001
	theta = (acos(cosValue) * 180 / 3.1416); // theta is the angle now.
	std::cout << theta << std::endl;
	currentQuaternion.cosine = cos((theta / 2) * 3.1416 / 180); // currentQuaternion.cosine is cos of half the nagle now

	currentQuaternion.axis.x = currentQuaternion.axis.x * sin((theta / 2) * 3.1416 / 180);
	currentQuaternion.axis.y = currentQuaternion.axis.y * sin((theta / 2) * 3.1416 / 180);
	currentQuaternion.axis.z = currentQuaternion.axis.z * sin((theta / 2) * 3.1416 / 180);


	cosValue_2 = (currentQuaternion.cosine * lastQuaternion.cosine) -
		glm::dot(currentQuaternion.axis, lastQuaternion.axis);

	glm::vec3 temporaryVector;
	temporaryVector = glm::cross(currentQuaternion.axis, lastQuaternion.axis);

	rotationalAxis_2.x = (currentQuaternion.cosine * lastQuaternion.axis.x) +
		(lastQuaternion.cosine * currentQuaternion.axis.x) +
		temporaryVector.x;


	rotationalAxis_2.y = (currentQuaternion.cosine * lastQuaternion.axis.y) +
		(lastQuaternion.cosine * currentQuaternion.axis.y) +
		temporaryVector.y;

	rotationalAxis_2.z = (currentQuaternion.cosine * lastQuaternion.axis.z) +
		(lastQuaternion.cosine * currentQuaternion.axis.z) +
		temporaryVector.z;

	
	angle = (acos(cosValue_2) * 180 / 3.1416) * 2;



	rotationalAxis.x = rotationalAxis_2.x / sin((angle / 2) * 3.1416 / 180);
	rotationalAxis.y = rotationalAxis_2.y / sin((angle / 2) * 3.1416 / 180);
	rotationalAxis.z = rotationalAxis_2.z / sin((angle / 2) * 3.1416 / 180);

}