//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: GameState.h
// Description	: Header file for CGameState class
// Author		: Lance Chaney
// Mail			: lance.cha7337@mediadesign.school.nz
//

#pragma once

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <array>

#include "State.h"
#include "utils.h"
#include "ActionList.h"

class CGameState : public IState
{
public:
	CGameState();
	virtual ~CGameState();

	/// <summary>
	/// Determines whether this state is terminal.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this state is terminal; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsTerminal() const override;

	/// <summary>
	/// Returns the utility heuristic for this state.
	/// </summary>
	/// <returns>The utility heuristic for this state.</returns>
	virtual int Utility() const override;

	/// <summary>
	/// Performs the action with id <paramref name="actionId"/>
	/// </summary>
	/// <param name="actionId">The action identifier.</param>
	virtual void PerformAction(size_t actionId) override;

	/// <summary>
	/// Rolls back the action with id <paramref name="actionId"/>.
	/// </summary>
	/// <param name="actionId">The action identifier.</param>
	virtual void RollbackAction(size_t actionId) override;

	/// <summary>
	/// Returns the number of available actions.
	/// </summary>
	/// <returns>The number of available actions.</returns>
	virtual size_t NumActionsAvailable() const override;

	/// <summary>
	/// Returns whos turn it is (player id 0 or 1).
	/// </summary>
	/// <returns>Whos turn it is (player id 0 or 1).</returns>
	virtual size_t Turn() const override;

	/// <summary>
	/// Toggles the player turn.
	/// </summary>
	void ToggleTurn();

	/// <summary>
	/// Performs the action.
	/// </summary>
	/// <param name="action">An action as a tuple containing a row and column to place at.</param>
	void PerformAction(const std::array<size_t, 2>& action);

	std::array<std::array<ETOKEN_TYPE, 3>, 3> m_board;

private:
	CActionList m_availableActions;
	size_t m_curTurn;
	mutable EWIN_STATE m_winState;
};

#endif // GAMESTATE_H
