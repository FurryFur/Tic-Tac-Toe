//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: ActionList.cpp
// Description	: Implementation file for CActionList class
// Author		: Lance Chaney
// Mail			: lance.cha7337@mediadesign.school.nz
//

#include "ActionList.h"

CActionList::CActionList() :
	m_curEnd{m_actions.size() - 1}
{
	for (size_t r = 0; r < 3; ++r)
	{
		for (size_t c = 0; c < 3; ++c)
		{
			m_actions[r * 3 + c] = { r, c };
		}
	}
}

CActionList::~CActionList()
{
}

void CActionList::RemoveAction(size_t actionId)
{
	Swap(actionId, m_curEnd);
	--m_curEnd;
}

void CActionList::RestoreAction(size_t actionId)
{
	++m_curEnd;
	Swap(actionId, m_curEnd);
}

const std::array<size_t, 2>& CActionList::GetAction(size_t actionIdx) const
{
	return m_actions.at(actionIdx);
}

size_t CActionList::size() const
{
	return m_curEnd + 1;
}

void CActionList::Swap(size_t idx1, size_t idx2)
{
	std::array<size_t, 2> tmp = m_actions.at(idx1);
	m_actions.at(idx1) = m_actions.at(idx2);
	m_actions.at(idx2) = tmp;
}
