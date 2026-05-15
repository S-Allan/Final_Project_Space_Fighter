//copied from bioenemyship.cpp
#include "BossAmmo.h"
#include "Level.h"


// Constructor: Initialize the BioEnemyShip with base properties
BossAmmo::BossAmmo()
{
	// Set the movement speed of the ship
	SetSpeed(500);
	// Set maximum health to 1 hit point (one-hit kill)
	SetMaxHitPoints(1);
	// Set collision detection radius to 20 units
	SetCollisionRadius(20);
}


// Update: Handle movement and visibility each frame
void BossAmmo::Update(const GameTime& gameTime)
{
	if (IsActive())
	{

		TranslatePosition(0, GetSpeed() * gameTime.GetElapsedTime());

		// Deactivate the ship if it has moved off-screen
		if (!IsOnScreen()) Deactivate();
	}

	// Call parent class update to handle common enemy behavior
	EnemyShip::Update(gameTime);
}


// Draw: Render the ship sprite with fade effect
void BossAmmo::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		// Get the current alpha (transparency) value from the level
		const float alpha = GetCurrentLevel()->GetAlpha();
		// Draw the texture at the ship's position with fade applied, rotated 180 degrees
		spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}
