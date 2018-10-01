#include "pch.h"
#include <SFML/Graphics.hpp>

const int WIDTH = 1920;
const int HEIGHT = 1080;
using namespace sf;
int main()
{ 
	//Create window
	VideoMode vm(WIDTH, HEIGHT);
	RenderWindow window(vm, "Timber", Style::Fullscreen);

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		// clear everything from the last frame
		window.clear();

		// draw, update scene

		window.display();
	}
	return 0;
}

