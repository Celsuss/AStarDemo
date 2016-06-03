#include "GraphicManager.h"

GraphicManager* GraphicManager::m_Instance = new GraphicManager();

GraphicManager::GraphicManager(){}

GraphicManager::~GraphicManager(){}

GraphicManager* GraphicManager::getInstance(){
	return m_Instance;
}

void GraphicManager::initialize(){
	getInstance()->m_Window.create(sf::VideoMode(900, 600), "A* demo");
	getInstance()->m_Window.setFramerateLimit(60);		//Set max fps tp 60
}

void GraphicManager::update(){
	getInstance()->m_Window.display();
	getInstance()->m_Window.clear();
}

void GraphicManager::draw(sf::Sprite& sprite){
	getInstance()->m_Window.draw(sprite);
}

void GraphicManager::draw(sf::RectangleShape& rectangleShape){
	getInstance()->m_Window.draw(rectangleShape);
}

sf::RenderWindow* GraphicManager::getWindow(){
	return &m_Instance->m_Window;
}