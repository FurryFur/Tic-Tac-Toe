#include "AIUtil.h"
#include "State.h"

namespace AIUtil
{
	int minimax(IState& rState, size_t* pBestActionId, int alpha, int beta)
	{
		int& rBestActionUtility = (rState.Turn() == 0) ? alpha : beta;

		for (size_t i = 0; (alpha < beta) && i < rState.NumActionsAvailable(); ++i)
		{
			// Goto child state
			rState.PerformAction(i);

			// Get state utility
			int stateUtility;
			if (rState.IsTerminal())
			{
				stateUtility = rState.Utility();
			}
			else
			{
				stateUtility = minimax(rState, nullptr, alpha, beta);
			}

			// Revert to parent state 
			rState.RollbackAction(i);

			// Update best utility so far
			if ((rState.Turn() == 0) ? (stateUtility > rBestActionUtility) : (stateUtility < rBestActionUtility))
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