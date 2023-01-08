#pragma once
#include <iostream>


class Mesh {
private:
	unsigned int vbo, vao, ebo;

public:
	Mesh(const float* vertices, int size, const int* indices, int indSize);
	void cleanup();
	unsigned int getVao();
};
