#include "StateManager.h"

StateManager::StateManager():
m_gameSceneState(GAMESCENE_NORMAL),
m_buildState(BUILD_NONE)
{
}

StateManager::~StateManager()
{
}

GAMESCENE_STATE StateManager::GetGameSceneState()
{
	return m_gameSceneState;
}

BUILD_STATE StateManager::GetBuildState()
{
	return m_buildState;
}

void StateManager::SetGameSceneState(GAMESCENE_STATE _gameSceneState)
{
	m_gameSceneState = _gameSceneState;
}

void StateManager::SetBuildState(BUILD_STATE _buildState)
{
	m_buildState = _buildState;
}


