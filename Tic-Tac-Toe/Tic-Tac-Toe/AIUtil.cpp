//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: AIUtil.cpp
// Description	: Implementation file for AI utility functions
// Author		: Lance Chaney
// Mail			: lance.cha7337@mediadesign.school.nz
//

#include "AIUtil.h"
#include "State.h"

namespace AIUtil
{
	int Minimax(IState& rState, size_t* pBestActionId, int alpha, int beta)
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
				stateUtility = Minimax(rState, nullptr, alpha, beta);
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