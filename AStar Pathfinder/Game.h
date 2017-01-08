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
	Goal* getGoal() const;
	static bool getDebugging();
private:
	void update();
	void initialize();
	void initializeText();
	void deleteGameObjects();
	void handleEvents();
	void createAIAndGoal();
	void updateDeltaTime();

	GameObjectVector m_GameObjects;
	sf::Text m_Text;
	sf::Text m_DTimerText;
	sf::Clock m_Clock;
	sf::Time m_LastTime;
	float m_DeltaTime;
	bool m_Restart;
	static bool m_Debug;
};