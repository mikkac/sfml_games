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

	//Create background texture and sprite
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/Background.png");

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	//Create tree texture and sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");

	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		// clear everything from the last frame
		window.clear();

		// draw, update scene
		window.draw(spriteBackground);
		window.draw(spriteTree);

		window.display();
	}
	return 0;
}

