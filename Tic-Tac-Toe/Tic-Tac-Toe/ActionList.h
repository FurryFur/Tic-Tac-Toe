#pragma once

#include <array>

class CActionList
{
public:
	CActionList();
	~CActionList();

	/// <summary>
	/// Remove the action at the specified action index.
	/// </summary>
	/// <param name="actionIdx">The index of the action to remove.</param>
	void RemoveAction(size_t actionIdx);

	/// <summary>
	/// Restores the previously performed action to the specified action index.
	/// <remarks>
	/// The action that exists at the specified index will be moved to the end of the list.
	/// </remarks>
	/// </summary>
	/// <param name="actionIdx">The index to restore the previous action to.</param>
	void RestoreAction(size_t actionIdx);

	const std::array<size_t, 2>& GetAction(size_t actionIdx) const;

	size_t size() const;

private:
	size_t m_curEnd;
	std::array<std::array<size_t, 2>, 9> m_actions;

	void Swap(size_t idx1, size_t idx2);
};

