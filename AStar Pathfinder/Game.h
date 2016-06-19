#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include <vector>

class Goal;
class GameObject;

class Game{
public:
	typedef std::vector<GameObject*>GameObjectVector;

	Game();
	~Game();
	void run();

	GameObjectVector* getGameObjects();
	Goal* getGoal();
private:
	void update();
	void initialize();
	void handleEvents();
	void createWalls();
	void createSurrondingWalls();
	void createRandomWalls();
	void updateDeltaTime();

	GameObjectVector m_GameObjects;
	sf::Font m_Font;
	sf::Text m_Text;
	sf::Text m_DTimerText;
	sf::Clock m_Clock;
	sf::Time m_LastTime;
	float m_DeltaTime;
};