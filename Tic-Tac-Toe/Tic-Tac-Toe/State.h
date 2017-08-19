#pragma once

class IState
{
public:
	virtual ~IState() {};

	virtual bool isTerminal() const = 0;
	virtual int utility() const = 0;
	virtual void performAction(size_t actionId) = 0;
	virtual void rollbackAction(size_t actionId) = 0;
	virtual size_t numActionsAvailable() const = 0;
	virtual size_t turn() const = 0;

protected:
	IState() {};
};