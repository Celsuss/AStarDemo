#pragma once
#include "SFML/Graphics/Texture.hpp"
#include <map>
#include <string>
#include <memory>

class TextureManager{
public:
	typedef std::map<std::string, sf::Texture*> TextureMap;

	static TextureManager* getInstance();

	sf::Texture* getTexture(const std::string name);
private:
	TextureManager();
	~TextureManager();
	static TextureManager* m_Instance;

	bool loadTexture(const std::string name);

	TextureMap m_Textures;
};