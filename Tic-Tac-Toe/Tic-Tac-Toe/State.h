//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: State.h
// Description	: Header file for IState interface
// Author		: Lance Chaney
// Mail			: lance.cha7337@mediadesign.school.nz
//

#pragma once

#ifndef STATE_H
#define STATE_H

class IState
{
public:
	virtual ~IState() {};

	/// <summary>
	/// Determines whether this state is terminal.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this state is terminal; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsTerminal() const = 0;

	/// <summary>
	/// Returns the utility heuristic for this state.
	/// </summary>
	/// <returns>The utility heuristic for this state.</returns>
	virtual int Utility() const = 0;

	/// <summary>
	/// Performs the action with id <paramref name="actionId"/>
	/// </summary>
	/// <param name="actionId">The action identifier.</param>
	virtual void PerformAction(size_t actionId) = 0;

	/// <summary>
	/// Rolls back the action with id <paramref name="actionId"/>.
	/// </summary>
	/// <param name="actionId">The action identifier.</param>
	virtual void RollbackAction(size_t actionId) = 0;

	/// <summary>
	/// Returns the number of available actions.
	/// </summary>
	/// <returns>The number of available actions.</returns>
	virtual size_t NumActionsAvailable() const = 0;

	/// <summary>
	/// Returns whos turn it is (player id 0 or 1).
	/// </summary>
	/// <returns>Whos turn it is (player id 0 or 1).</returns>
	virtual size_t Turn() const = 0;

protected:
	IState() {};
};

#endif // STATE_H