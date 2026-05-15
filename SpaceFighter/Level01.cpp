

#include "Level01.h"
#include "BioEnemyShip.h"
#include "GameplayScreen.h"

// LoadContent: Load and spawn enemies for this level
void Level01::LoadContent(ResourceManager& resourceManager)
{

	// Load the enemy ship texture
	Texture *pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");

	// Number of enemies to spawn
	const int COUNT = 21;

	// Horizontal spawn positions as screen width percentages
	double xPositions[COUNT] =
	{
		0.25, 0.2, 0.3,
		0.75, 0.8, 0.7,
		0.3, 0.25, 0.35, 0.2, 0.4,
		0.7, 0.75, 0.65, 0.8, 0.6,
		0.5, 0.4, 0.6, 0.45, 0.55
	};

	// Delays between spawning each enemy (in seconds)
	double delays[COUNT] =
	{
		0.0, 0.25, 0.25,
		3.0, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.5, 0.3, 0.3, 0.3, 0.3
	};

	// Initial level start delay
	float delay = 3.0;
	Vector2 position;
	
	for (int i = 0; i < COUNT; i++)
	{

		// Accumulate delays to spread out enemy spawns over time
		delay += delays[i];
		// Calculate spawn position (x: percentage of screen width, y: above screen)
		position.Set(xPositions[i] * Game::GetScreenWidth(), -pTexture->GetCenter().Y);

		// Create enemy ship
		BioEnemyShip *pEnemy = new BioEnemyShip();
		pEnemy->SetTexture(pTexture);
		pEnemy->SetCurrentLevel(this);
		// Initialize with position and spawn delay
		pEnemy->Initialize(position, (float)delay);
		// Add to level game objects
		AddGameObject(pEnemy);
		m_enemyCount ++ ;
	}
	m_totalEnemies = m_enemyCount; //sets the m_totalEnemies to the incremented m_enemyCount.

	// Set the background texture for this level
	SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground01.png"));
	// Call parent level initialization
	Level::LoadContent(resourceManager);
}


