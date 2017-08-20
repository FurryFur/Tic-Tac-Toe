//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: AIUtil.h
// Description	: Header file for AI utility functions
// Author		: Lance Chaney
// Mail			: lance.cha7337@mediadesign.school.nz
//

#pragma once

#ifndef AIUTIL_H
#define AIUTIL_H

#include <limits>

class IState;

namespace AIUtil 
{
	/// <summary>
	/// Minimax algorithm.
	/// Returns utility of the current state.
	/// </summary>
	/// <param name="rState">Reference to the current state.</param>
	/// <param name="pBestActionId">
	/// The best action id, according to the Minimax algorithm, is returned in this variable.
	/// Can take nullptr if no action id is required.
	/// </param>
	/// <param name="alpha">Highest (Best) utility seen so far by a max node on path to root.</param>
	/// <param name="beta">Lowest (Best) utility seen so far by a min node on path to root.</param>
	/// <returns>Utility of the current state.</returns>
	int Minimax(IState& rState, size_t* pBestActionId, int alpha = std::numeric_limits<int>::min(), int beta = std::numeric_limits<int>::max());
}

#endif // AIUTIL_H