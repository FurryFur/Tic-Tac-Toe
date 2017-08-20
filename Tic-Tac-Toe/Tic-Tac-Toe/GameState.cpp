//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: GameState.cpp
// Description	: Implementation file for CGameState class
// Author		: Lance Chaney
// Mail			: lance.cha7337@mediadesign.school.nz
//

#include "GameState.h"
#include "game.h"

CGameState::CGameState() :
	m_curTurn{ 0 },
	m_winState{ NO_WIN }
{
	for (size_t i = 0; i < m_board.size(); ++i)
	{
		for (size_t j = 0; j < m_board[i].size(); ++j)
		{
			m_board[i][j] = FREE;
		}
	}
}

CGameState::~CGameState()
{
}

bool CGameState::IsTerminal() const
{
	m_winState = CGame::GetInstance().CheckWinCondition();
	return m_winState != NO_WIN;
}

int CGameState::Utility() const
{
	if (m_winState == DRAW)
	{
		return 0;
	}
	else if (static_cast<EWIN_STATE>(CGame::GetPlayerToken(0)) == m_winState)
	{
		return static_cast<int>(m_availableActions.size() + 1);
	}
	else
	{
		return -static_cast<int>(m_availableActions.size() + 1);
	}
}

void CGameState::PerformAction(size_t actionId)
{
	if (actionId >= m_availableActions.size())
		return;

	const std::array<size_t, 2>& action = m_availableActions.GetAction(actionId);
	size_t r = action[0];
	size_t c = action[1];
	m_board[r][c] = CGame::GetPlayerToken(m_curTurn);

	ToggleTurn();
	m_availableActions.RemoveAction(actionId);
}

void CGameState::RollbackAction(size_t actionId)
{
	if (actionId > m_availableActions.size())
		return;

	m_availableActions.RestoreAction(actionId);
	ToggleTurn();

	const std::array<size_t, 2>& action = m_availableActions.GetAction(actionId);
	size_t r = action[0];
	size_t c = action[1];
	m_board[r][c] = FREE;
}

size_t CGameState::NumActionsAvailable() const
{
	return m_availableActions.size();
}

size_t CGameState::Turn() const
{
	return m_curTurn;
}

void CGameState::ToggleTurn()
{
	m_curTurn ^= 1;
}

void CGameState::PerformAction(const std::array<size_t, 2>& action)
{
	for (size_t i = 0; i < m_availableActions.size(); ++i)
	{
		if (m_availableActions.GetAction(i) == action)
		{
			PerformAction(i);
			return;
		}
	}
}
