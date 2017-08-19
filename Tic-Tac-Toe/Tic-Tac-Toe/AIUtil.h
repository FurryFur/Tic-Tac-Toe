#pragma once

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
	/// The best action id, according to the minimax algorithm, is returned in this variable.
	/// Can take nullptr if no action id is required.
	/// </param>
	/// <param name="alpha">Highest (Best) utility seen by maximizer.</param>
	/// <param name="beta">Lowest (Best) utility seen by minimizer.</param>
	/// <returns>Utility of the current state.</returns>
	int minimax(IState& rState, size_t* pBestActionId, int alpha = std::numeric_limits<int>::min(), int beta = std::numeric_limits<int>::max());
}