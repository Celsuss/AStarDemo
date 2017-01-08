#include "GraphicManager.h"
#include <iostream>

GraphicManager* GraphicManager::m_Instance = new GraphicManager();

GraphicManager::GraphicManager(){}

GraphicManager::~GraphicManager(){}

GraphicManager* GraphicManager::getInstance(){
	return m_Instance;
}

// Initialize the window and font
void GraphicManager::initialize(){
	m_Window.create(sf::VideoMode(900, 600), "A* demo");
	m_Window.setFramerateLimit(60);		//Set max fps tp 60
	if (!m_Font.loadFromFile("Assets/arial.ttf"))
		std::cout << "Failed to load font" << std::endl;
}

// Update the screen
void GraphicManager::update(){
	m_Window.display();
	m_Window.clear();
}

// Draw text
void GraphicManager::draw(const sf::Text& text){
	m_Window.draw(text);
}

// Draw sprite
void GraphicManager::draw(const sf::Sprite& sprite){
	m_Window.draw(sprite);
}

// Draw rectangle shape
void GraphicManager::draw(const sf::RectangleShape& rectangleShape){
	m_Window.draw(rectangleShape);
}

// Returns the window
sf::RenderWindow* GraphicManager::getWindow(){
	return &m_Window;
}

// Returns the font
sf::Font* GraphicManager::getFont(){
	return &m_Font;
}