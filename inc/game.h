#pragma once
#include <SFML/Graphics.hpp>

namespace game {

	template<typename T>
	T createBuffer(const char* pathToFile)
    {
        T buffer;
        buffer.loadFromFile(pathToFile);
        return buffer;
    }
	
	struct vec2
	{
		float x, y;
	};

	class Drawing
	{
	public:
		Drawing(
			sf::Texture texture, bool is_active = false, 
			vec2 position = { 0,0 },
			vec2 speed = { 0,0 }
		);

		Drawing() = delete; //disable possibility to create object without texture
		Drawing(const Drawing& other) = default;
		Drawing& operator=(const Drawing& other) = default;
		Drawing(Drawing&& other) = default;
		Drawing& operator=(Drawing&& other) = default;

		virtual ~Drawing() = 0;

		void setPosition(vec2 position);
		vec2 getPosition() const;

		void setSpeed(vec2 speed);
		vec2 getSpeed() const;

		bool isActive() const;
		void setActiveness(bool is_active);
	private:
		sf::Sprite m_sprite;
		vec2 m_speed{};
		bool m_is_active;
	};


} //namespace game
