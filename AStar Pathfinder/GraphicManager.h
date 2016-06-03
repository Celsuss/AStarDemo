#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics.hpp"

class GraphicManager{
public:
	typedef std::vector<sf::Drawable*>DrawableList;

	static GraphicManager* getInstance();
	static void initialize();
	static void update();

	static void draw(sf::Sprite& sprite);
	static void draw(sf::RectangleShape& rectangleShape);
	static sf::RenderWindow* getWindow();
private:
	GraphicManager();
	~GraphicManager();
	static GraphicManager* m_Instance;

	static void drawBackGround();
	static void drawNormalGround();
	static void drawForeGround();

	sf::RenderWindow m_Window;
	DrawableList m_Background;
	DrawableList m_NormalGround;
	DrawableList m_Foreground;
};