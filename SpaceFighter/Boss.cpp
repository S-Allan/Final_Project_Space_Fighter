#include "Boss.h"
#include "Level.h"


// Constructor: Initialize the BioEnemyShip with base properties
Boss::Boss()
{
	// Set the movement speed of the ship
	SetSpeed(150);
	// Set maximum health to 20. Will need 20 hits to kill the boss
	SetMaxHitPoints(20);
	// Set collision detection radius to 100 units
	SetCollisionRadius(100);
}


// Update: Handle movement and visibility each frame
void Boss::Update(const GameTime& gameTime)
{
	if (IsActive())
	{
		// Calculate sinusoidal horizontal movement based on elapsed time
		// This moves the boss across the screen
		float x = sin(gameTime.GetTotalTime() * Math::PI); //boss kept flying off the screen after I added a background. Not sure why, but I had to modify this code so the boss stayed on screen
		// Scale the horizontal movement by speed and time, with amplification factor
		x *= GetSpeed() * gameTime.GetElapsedTime() * 6.0f;
		// Move the ship horizontally (x). Boss does not move down, so the Y translation stays the same.
		TranslatePosition(x, 0);

		// Deactivate the ship if it has moved off-screen
		//if (!IsOnScreen()) Deactivate(); not needed
	}

	// Call parent class update to handle common enemy behavior
	EnemyShip::Update(gameTime);
}


// Draw: Render the ship sprite with fade effect
void Boss::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		// Get the current alpha (transparency) value from the level
		const float alpha = GetCurrentLevel()->GetAlpha();
		// Draw the texture at the ship's position with fade applied, rotated 180 degrees
		spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}
void Boss::Hit(float damage) //added to end the level after boss is destroyed.
{
	bool wasActive = IsActive();

	EnemyShip::Hit(damage);
	//checks if the Boss was active at a time and is no longer active.
	if (wasActive && !IsActive())
	{
		Level* pLevel = GetCurrentLevel(); //Set the current level to pLevel.

		//uses pLevel to increment the enemy being destroyed.
		if (pLevel)
		{
			pLevel->IncrementEnemiesDestroyed();
		}
	}
}