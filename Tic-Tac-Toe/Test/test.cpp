#include <limits>
#include <array>

#include "catch.hpp"

#include <State.h>

const size_t kBranchFactor{ 3 };
const size_t kNumPlayers{ 2 };
const size_t kMaxDepth{ 3 };

class TestState : public IState
{
public:
	// Inherited via IState
	virtual bool isTerminal() const override
	{
		return curDepth == kMaxDepth;
	}
	virtual int utility() const override
	{
		if (isTerminal())
		{
			return terminalNodeUtil[curPath[0] * kBranchFactor * kBranchFactor + curPath[1] * kBranchFactor + curPath[2]];
		}
		else
		{
			return (curTurn == 0) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
		}
	}
	virtual void performAction(size_t actionId) override
	{
		curPath[curDepth] = actionId;

		// Alpha-Beta pruning access check
		size_t treeAccessIdx = 0;
		for (size_t i = 0; i <= curDepth; ++i)
		{
			treeAccessIdx = treeAccessIdx * 3 + curPath[i] + 1;
		}
		CAPTURE(curPath[0]);
		CAPTURE(curPath[1]);
		CAPTURE(curPath[2]);
		CAPTURE(curDepth);
		CAPTURE(treeAccessIdx);
		INFO("Unexpected Access");
		CHECK(expectedAccess[treeAccessIdx]);
		actualAccess[treeAccessIdx] = true;

		++curDepth;

		curTurn ^= 1;
	}
	virtual void rollbackAction(size_t actionId) override
	{
		--curDepth;

		curTurn ^= 1;
	}
	virtual size_t numActionsAvailable() const override
	{
		return kBranchFactor;
	}
	virtual size_t turn() const override
	{
		return curTurn;
	}

private:
	size_t curDepth{ 0 };
	std::array<int, kBranchFactor * kBranchFactor * kBranchFactor> terminalNodeUtil{ -3, -9, 16, -10, 15, 17, -12, 4, 10, -5, 5, 2, 16, 2, 16, 14, -12, 16, 17, -18, -14, -2, -8, 11, -5, 15, 5 };
	std::array<size_t, kMaxDepth> curPath{ 0, 0, 0 };
	size_t curTurn = 0;

public:
	// Expected and Actual access behavior (list of nodes that should and should not be visited)
	std::array<bool, 1 + kBranchFactor + kBranchFactor * kBranchFactor + kBranchFactor * kBranchFactor * kBranchFactor> expectedAccess {
		true,
		true, true, true,
		true, true, true, true, false, false, true, true, true,
		true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false, false, true, true, true, true, true, true, true, true, false
	};
	std::array<bool, 1 + kBranchFactor + kBranchFactor * kBranchFactor + kBranchFactor * kBranchFactor * kBranchFactor> actualAccess{
		true,
		false, false, false,
		false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
	};
};

// Inputs:
//     alpha - Highest (Best) utility seen by maximizer
//     beta  - Lowest (Best) utility seen by minimizer
int minimax(IState& rState, size_t* pBestActionId, int alpha = std::numeric_limits<int>::min(), int beta = std::numeric_limits<int>::max())
{
	int& rBestActionUtility = (rState.turn() == 0) ? alpha : beta;

	for (size_t i = 0; (alpha < beta) && i < rState.numActionsAvailable(); ++i)
	{
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

		rState.rollbackAction(i);

		// Update best move if better
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



TEST_CASE("Minimax")
{
	TestState state;

	size_t expectedActionId = 2;
	size_t actualActionId;
	int utility = minimax(state, &actualActionId);
	REQUIRE(utility == 11);
	REQUIRE(actualActionId == expectedActionId);
	REQUIRE(state.actualAccess == state.expectedAccess);
}