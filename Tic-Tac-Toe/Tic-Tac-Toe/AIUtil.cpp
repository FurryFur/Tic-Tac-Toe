#include "AIUtil.h"
#include "State.h"

namespace AIUtil
{
	int minimax(IState& rState, size_t* pBestActionId, int alpha, int beta)
	{
		int& rBestActionUtility = (rState.turn() == 0) ? alpha : beta;

		for (size_t i = 0; (alpha < beta) && i < rState.numActionsAvailable(); ++i)
		{
			// Goto child state
			rState.performAction(i);

			// Get state utility
			int stateUtility;
			if (rState.isTerminal())
			{
				stateUtility = rState.utility();
			}
			else
			{
				stateUtility = minimax(rState, nullptr, alpha, beta);
			}

			// Revert to parent state 
			rState.rollbackAction(i);

			// Update best utility so far
			if ((rState.turn() == 0) ? (stateUtility > rBestActionUtility) : (stateUtility < rBestActionUtility))
			{
				// Set best action for the root node
				if (pBestActionId != nullptr)
				{
					*pBestActionId = i;
				}

				rBestActionUtility = stateUtility;
			}
		}

		return rBestActionUtility;
	}
}