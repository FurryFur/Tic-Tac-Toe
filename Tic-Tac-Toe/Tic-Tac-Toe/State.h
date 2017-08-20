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

	virtual bool IsTerminal() const = 0;
	virtual int Utility() const = 0;
	virtual void PerformAction(size_t actionId) = 0;
	virtual void RollbackAction(size_t actionId) = 0;
	virtual size_t NumActionsAvailable() const = 0;
	virtual size_t Turn() const = 0;

protected:
	IState() {};
};

#endif // STATE_H