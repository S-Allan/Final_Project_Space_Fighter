#pragma once

#include "Level.h"

/** @brief The first level of the game. */
class Level01 :	public Level
{
private:
	int m_enemyCount = 0;
public:
	/** @brief Instantiate a level object. */
	Level01() { }
	virtual ~Level01() { }

	/** @brief Load the content for the level, including game objects and resources.
		@param resourceManager A reference to the game's resource manager,
		used for loading and managing game assets (resources). */
	virtual void LoadContent(ResourceManager& resourceManager);
};

