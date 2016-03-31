#include "StateManager.h"

StateManager::StateManager():
m_gameSceneState(GAMESCENE_NORMAL),
m_buildState(BUILD_NONE),
m_roadManagerState(ROADMANAGER_ENUM::START_POS_SET),
m_buildAreaManagerState(BUILDAREAMANAGER_ENUM::START_POS_SET)
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

ROADMANAGER_ENUM::STATE StateManager::GetRoadManagerState()
{
	return m_roadManagerState;
}

BUILDAREAMANAGER_ENUM::STATE StateManager::GetBuildAreaManagerState()
{
	return m_buildAreaManagerState;
}


void StateManager::SetGameSceneState(GAMESCENE_STATE _gameSceneState)
{
	m_gameSceneState = _gameSceneState;
}

void StateManager::SetBuildState(BUILD_STATE _buildState)
{
	m_buildState = _buildState;
}

void StateManager::SetRoadManagerState(ROADMANAGER_ENUM::STATE _roadManagerState)
{
	m_roadManagerState = _roadManagerState;
}

void StateManager::SetBuildAreaManagerState(BUILDAREAMANAGER_ENUM::STATE _buildAreaManager)
{
	m_buildAreaManagerState = _buildAreaManager;
}
