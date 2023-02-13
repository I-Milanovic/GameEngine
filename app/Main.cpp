#include "../Window.h"

int main() {
	Window* window = new Window();
	window->init();
	delete(window);
}