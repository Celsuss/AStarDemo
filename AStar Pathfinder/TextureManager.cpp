#include "TextureManager.h"

TextureManager* TextureManager::m_Instance = new TextureManager();

TextureManager::TextureManager(){}

TextureManager::~TextureManager(){}

TextureManager* TextureManager::getInstance(){
	return m_Instance;
}

sf::Texture* TextureManager::getTexture(std::string name){
	sf::Texture* tex = m_Textures[name];
	if (tex == nullptr){
		if (loadTexture(name))
			return m_Textures[name];
		else
			return nullptr;
	}
	return tex;
}

bool TextureManager::loadTexture(std::string name){
	sf::Texture* tex = new sf::Texture;
	tex->loadFromFile("Assets/" + name + ".png");

	if (tex == nullptr)
		return false;
	m_Textures[name] = tex;
	return true;
}