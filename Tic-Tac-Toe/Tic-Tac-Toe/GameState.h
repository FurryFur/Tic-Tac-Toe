#pragma once

#include <array>

#include "State.h"
#include "utils.h"
#include "ActionList.h"

class CGameState : public IState
{
public:
	CGameState(std::array<std::array<ETOKEN_TYPE, 3>, 3>& rBoard);
	virtual ~CGameState();

	// Inherited via IState
	virtual bool IsTerminal() const override;
	virtual int Utility() const override;
	virtual void PerformAction(size_t actionId) override;
	virtual void RollbackAction(size_t actionId) override;
	virtual size_t NumActionsAvailable() const override;
	virtual size_t Turn() const override;

	void toggleTurn();
	void PerformAction(const std::array<size_t, 2>& action);

private:
	std::array<std::array<ETOKEN_TYPE, 3>, 3>& m_rBoard;
	CActionList m_availableActions;
	size_t m_curTurn;
	mutable EWIN_STATE m_winState;
};
