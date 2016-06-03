#include "GraphicManager.h"

GraphicManager* GraphicManager::m_Instance = new GraphicManager();

GraphicManager::GraphicManager(){}

GraphicManager::~GraphicManager(){}

GraphicManager* GraphicManager::getInstance(){
	return m_Instance;
}

void GraphicManager::initialize(){
	getInstance()->m_Window.create(sf::VideoMode(1200, 900), "InvasionZx2");
	getInstance()->m_Window.setFramerateLimit(60);		//Set max fps tp 60
}

void GraphicManager::update(){
	drawBackGround();
	drawNormalGround();
	drawForeGround();

	getInstance()->m_Window.display();
	getInstance()->m_Window.clear();
}

void GraphicManager::draw(sf::Sprite sprite){
	
}

sf::RenderWindow* GraphicManager::getWindow(){
	return &m_Instance->m_Window;
}