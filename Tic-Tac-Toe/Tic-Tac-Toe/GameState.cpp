#include "GameState.h"
#include "game.h"


CGameState::CGameState(std::array<std::array<ETOKEN_TYPE, 3>, 3>& rBoard) :
	m_rBoard{ rBoard },
	m_curTurn{ 0 },
	m_winState{ NO_WIN }
{
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
	m_rBoard[r][c] = CGame::GetPlayerToken(m_curTurn);

	toggleTurn();
	m_availableActions.RemoveAction(actionId);
}

void CGameState::RollbackAction(size_t actionId)
{
	if (actionId > m_availableActions.size())
		return;

	m_availableActions.RestoreAction(actionId);
	toggleTurn();

	const std::array<size_t, 2>& action = m_availableActions.GetAction(actionId);
	size_t r = action[0];
	size_t c = action[1];
	m_rBoard[r][c] = FREE;
}

size_t CGameState::NumActionsAvailable() const
{
	return m_availableActions.size();
}

size_t CGameState::Turn() const
{
	return m_curTurn;
}

void CGameState::toggleTurn()
{
	m_curTurn ^= 1;
}

void CGameState::PerformAction(const std::array<size_t, 2>& action)
{
	size_t r = action[0];
	size_t c = action[1];
	size_t guessedStart = r * 3 + c;
	size_t end = m_availableActions.size() - 1;

	for (int i = guessedStart <= end ? guessedStart : end; i >= 0; --i) // Start search at furthest possible action index
	{
		if (m_availableActions.GetAction(i) == action)
		{
			PerformAction(i);
			return;
		}
	}
}
