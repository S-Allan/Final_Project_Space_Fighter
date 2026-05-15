
#include "BioEnemyShip.h"
#include "Level.h"


// Constructor: Initialize the BioEnemyShip with base properties
BioEnemyShip::BioEnemyShip()
{
	// Set the movement speed of the ship
	SetSpeed(150);
	// Set maximum health to 1 hit point (one-hit kill)
	SetMaxHitPoints(1);
	// Set collision detection radius to 20 units
	SetCollisionRadius(20);
}

void BioEnemyShip::Hit(float damage)
{
	bool wasActive = IsActive();
	EnemyShip::Hit(damage);

	if(wasActive && !IsActive())
	{
		Level* pLevel = GetCurrentLevel();
		if (pLevel)
		{
			pLevel->QueueEnemyDestruction();
		}
	}
}

// Update: Handle movement and visibility each frame
void BioEnemyShip::Update(const GameTime& gameTime)
{
	if (IsActive())
	{
		// Calculate sinusoidal horizontal movement based on elapsed time
		// This creates a wave-like side-to-side motion pattern
		float x = sin(gameTime.GetTotalTime() * Math::PI + GetIndex());
		// Scale the horizontal movement by speed and time, with amplification factor
		x *= GetSpeed() * gameTime.GetElapsedTime() * 1.4f;
		// Move the ship horizontally (x) and downward (y) each frame
		TranslatePosition(x, GetSpeed() * gameTime.GetElapsedTime());

		// Deactivate the ship if it has moved off-screen
		if (!IsOnScreen())
		{
			Deactivate();

			Level* pLevel = GetCurrentLevel();
			if (pLevel)
			{
				pLevel->QueueEnemyDestruction();
			}
		}
	}

	// Call parent class update to handle common enemy behavior
	EnemyShip::Update(gameTime);
}


// Draw: Render the ship sprite with fade effect
void BioEnemyShip::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		// Get the current alpha (transparency) value from the level
		const float alpha = GetCurrentLevel()->GetAlpha();
		// Draw the texture at the ship's position with fade applied, rotated 180 degrees
		spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}
