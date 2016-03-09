#include "StateManager.h"

StateManager::StateManager():
m_gameSceneState(GAMESCENE_NORMAL)
{
}

StateManager::~StateManager()
{
}

GAMESCENE_STATE StateManager::GetGameSceneState()
{
	return m_gameSceneState;
}

void StateManager::SetGameSceneState(GAMESCENE_STATE _gameSceneState)
{
	m_gameSceneState = _gameSceneState;
}
