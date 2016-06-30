#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics.hpp"

class GraphicManager{
public:
	typedef std::vector<sf::Drawable*>DrawableList;

	static GraphicManager* getInstance();
	void initialize();
	void update();

	void draw(sf::Text& text);
	void draw(sf::Sprite& sprite);
	void draw(sf::RectangleShape& rectangleShape);
	sf::RenderWindow* getWindow();
	sf::Font* getFont();
private:
	GraphicManager();
	~GraphicManager();
	static GraphicManager* m_Instance;

	void drawBackGround();
	void drawNormalGround();
	void drawForeGround();

	sf::Font m_Font;
	sf::RenderWindow m_Window;
	DrawableList m_Background;
	DrawableList m_NormalGround;
	DrawableList m_Foreground;
};