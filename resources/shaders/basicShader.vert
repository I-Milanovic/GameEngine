#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 texCoord;

out vec3 outPosition;
out vec3 outVertexNormal;
out vec2 outTexCoord;

// should i calculate here model view matrix

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	vec4 mvPosition = modelViewMatrix * vec4(position, 1.0);
	gl_Position = projectionMatrix * mvPosition; //viewMatrix * modelMatrix * vec4(position, 1.0);

	outPosition = mvPosition.xyz;
	outVertexNormal = normalize(modelViewMatrix * vec4(vertexNormal, 0.0)).xyz;
	outTexCoord = texCoord;
}
