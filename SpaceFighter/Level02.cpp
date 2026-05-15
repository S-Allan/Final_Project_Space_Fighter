

#include "Level02.h"
#include "Boss.h"
#include "BioEnemyShip.h"
#include "BossAmmo.h"



void Level02::LoadContent(ResourceManager& resourceManager)
{
	
	// Setup boss
	Texture* pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyboss.png"); //Boss doesn't load and nor does playership. Bullet does load, though? NVM. Spawning off screen. Set the texture for Boss.
	Texture* pAmmo = resourceManager.Load<Texture>("Textures\\Bullet.png"); //set the texture for pAmmo
	//changing the starting location of the boss seems to have worked.
	const int COUNT = 22;

	double xPositions[COUNT] =
	{
		0.25, 0.2, 0.3,
		0.75, 0.8, 0.7,
		0.3, 0.25, 0.35, 0.2, 0.4,
		0.7, 0.75, 0.65, 0.8, 0.6,
		0.5, 0.4, 0.6, 0.45, 0.55, .6
	};
	
	double delays[COUNT] =
	{
		0.0 , 0.25, 0.25,
		3.0, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.5, 0.3, 0.3, 0.3, 0.3, 0.3
	};
	
	float delay = 1.0; // start delay
	Vector2 position;

		position.Set(750, 100); //set enemy location. Must set so enemy boss actually loads!!!

		Boss* pBoss = new Boss(); //adds the Boss onto the heap.
		pBoss->SetTexture(pTexture); //loads the boss texture onto pBoss
		pBoss->SetCurrentLevel(this); //allows the boss to be loaded into the level.
		pBoss->Initialize(position, (float)delay); //spawns boss into location
		AddGameObject(pBoss);

			for (int i = 0; i < COUNT; i++)
			{
				delay += delays[i];
				// Calculate spawn position (x: percentage of screen width, y: above screen)
				position.Set(xPositions[i] * Game::GetScreenWidth(), 200);

				BossAmmo* pEnemyAmmo = new BossAmmo(); //create ammo and place it over BioEnemyShip.
				pEnemyAmmo->SetTexture(pAmmo); //load ammo for the boss
				pEnemyAmmo->SetCurrentLevel(this); //allows the ammo to be loaded into the level
				pEnemyAmmo->Initialize(position, (float)delay); //spawns ammo into the location
				AddGameObject(pEnemyAmmo); //load into the game.
			}
			m_totalEnemies = 1; //set m_totalEnemies to the number of Bosses. In this case, only one. This is so the level ends with the Boss's death and the dead boss can't keep firing bullets!
	SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground02.png")); //copied from Level01.cpp and changed to SpaceBackground02.png
	Level::LoadContent(resourceManager);
}

