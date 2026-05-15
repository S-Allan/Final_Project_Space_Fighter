
#include "GameplayScreen.h"
#include "MainMenuScreen.h"
#include "Level.h"
#include "Level01.h"
#include "Level02.h" //added so Level02 can be used as a Boss level.

GameplayScreen::GameplayScreen(const int levelIndex)
	: m_levelIndex(levelIndex)
{
	SetTransitionInTime(1);
	SetTransitionOutTime(3);

	SetOnRemove([this](){ AddScreen(new MainMenuScreen()); });

	Show();
}

void GameplayScreen::LoadContent(ResourceManager& resourceManager)
{
	m_pResourceManager = &resourceManager;
	LoadLevel(m_levelIndex);
}

void GameplayScreen::LoadLevel(const int levelIndex)
{
	m_isTransitioning = true; //used to more smoothly transition between levels and not get an exception.

	Level* pOldLevel = m_pLevel; //sets current level to pOldLevel.

	m_pLevel = nullptr;
	

	switch (levelIndex)
	{
	case 0: m_pLevel = new Level01(); break;
	case 1: m_pLevel = new Level02(); break; //added level 02
	default: m_pLevel = new Level01(); break; //added a default level.
	}

	if (m_pLevel) //checks for a nullptr.
	{
		m_pLevel->SetGameplayScreen(this);
		m_pLevel->LoadContent(*m_pResourceManager);
	}
	if (pOldLevel) //needed to get around the execption. checks to see if the pOldLevel has a valid value and then deletes old level after new level is ready. 
	{
		delete pOldLevel; //delete previous level
		pOldLevel = nullptr; //sets previous level to nullptr.
	}
	m_isTransitioning = false; //changes m_isTransitioning back to false.
}

void GameplayScreen::HandleInput(const InputState& input)
{
	m_pLevel->HandleInput(input);
}

void GameplayScreen::Update(const GameTime& gameTime)
{
	if (m_pLevel){m_pLevel->Update(gameTime);}
}

void GameplayScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();

	m_pLevel->Draw(spriteBatch);

	spriteBatch.End();
}
void GameplayScreen::AdvanceLevel()
{

	int nextLevel = m_levelIndex + 1; //set nextLevel to the current level plus 1
	if (nextLevel < 2) //check if the nextlevel is 2 or less. If it is, advance to the next level.
	{
		LoadLevel(nextLevel); //load next level
		m_levelIndex = nextLevel; //set the level index to the next level.
	}
	else //if next level is 2 or more, exit the game.
	{
		CompleteGame();
	}
}
void GameplayScreen::CompleteGame() //Exit game if called.
{
	Exit();
}