#version 330 core

const int MAX_WEIGHTS = 4;
const int MAX_BONES = 150;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;
layout (location = 5) in vec4 boneWeights;
layout (location = 6) in ivec4 boneIndices;

// TODO see if it's better to have bone struct
out vec3 outPosition;
out vec3 outVertexNormal;
out vec2 outTexCoord;
out vec3 outTangent;
out vec3 outBitangent;

// TODO should i calculate here model view matrix

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 bonesMatrices[MAX_BONES];

void main() {

	vec4 initPos = vec4(0, 0, 0, 0);
	vec4 initNormal = vec4(0, 0, 0, 0);
	vec4 initTangent = vec4(0, 0, 0, 0);
	vec4 initBitangent = vec4(0, 0, 0, 0);


	int count = 0;
	for(int i = 0; i < MAX_WEIGHTS; i++) {
		float weight = boneWeights[i];
		if(weight > 0){
			count++;
			int boneIndex = boneIndices[i];
			vec4 tmpPos = bonesMatrices[boneIndex] * vec4(position, 1.0);
			initPos += weight * tmpPos;

			vec4 tmpNormal = bonesMatrices[boneIndex] * vec4(vertexNormal, 0.0);
			initNormal += weight * tmpNormal;

			vec4 tmpTangent = bonesMatrices[boneIndex] * vec4(tangent, 0.0);
			initTangent += weight * tmpTangent;

			vec4 tmpBitangent = bonesMatrices[boneIndex] * vec4(bitangent, 0.0);
			initTangent += weight * tmpBitangent;
		}
	}

	if(count == 0) {
	
		initPos = vec4(position, 1.0);
		initNormal = vec4(vertexNormal, 0.0);
		initTangent = vec4(tangent, 0.0);
		initBitangent = vec4(bitangent, 0.0);
	}

	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	vec4 mvPosition = modelViewMatrix * initPos;
	gl_Position = projectionMatrix * mvPosition; //viewMatrix * modelMatrix * vec4(position, 1.0);

	outPosition = mvPosition.xyz;
	outVertexNormal = normalize(modelViewMatrix * initNormal).xyz;
	outTangent = normalize(modelViewMatrix * initTangent).xyz;
	outBitangent = normalize(modelViewMatrix * initBitangent).xyz;
	outTexCoord = texCoord;
}