#pragma once

class Mesh {

public:
	Mesh(const float* vertices, int size, const int* indices, int indSize);
	void cleanup();
	inline unsigned int getVao() { return vao; };
private:
	unsigned int vbo, vao, ebo;
};