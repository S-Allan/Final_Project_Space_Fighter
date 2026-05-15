
#include "EnemyShip.h"

// Constructor: Initialize the EnemyShip with base properties
EnemyShip::EnemyShip()
{
	// Set maximum health to 150 hit points
	SetMaxHitPoints(150);
	// Set collision detection radius to 20 units
	SetCollisionRadius(20);
}


// Update: Handle delayed activation and deactivation each frame
void EnemyShip::Update(const GameTime& gameTime)
{
	// Count down the spawn delay timer
	if (m_delaySeconds > 0)
	{
		m_delaySeconds -= gameTime.GetElapsedTime();

		// Activate the ship once the delay expires
		if (m_delaySeconds <= 0)
		{
			GameObject::Activate();
		}
	}

	// Deactivate the ship if it's been active for more than 2 seconds and is off-screen
	if (IsActive())
	{
		m_activationSeconds += gameTime.GetElapsedTime();
		if (m_activationSeconds > 2 && !IsOnScreen()) Deactivate();
	}

	// Call parent class update to handle common ship behavior
	Ship::Update(gameTime);
}


void EnemyShip::Initialize(const Vector2 position, const double delaySeconds)
{
	SetPosition(position);
	m_delaySeconds = delaySeconds;

	Ship::Initialize();
}


void EnemyShip::Hit(const float damage)
{
	Ship::Hit(damage);
}