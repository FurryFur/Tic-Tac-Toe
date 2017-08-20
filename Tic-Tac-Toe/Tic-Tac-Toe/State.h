#pragma once

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