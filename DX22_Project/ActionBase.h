#include "Command.h"
#include <iostream>
#include <vector>

#pragma once
class ActionBase
{
public:
	ActionBase();
	~ActionBase();

	virtual void Action() {};
	std::vector<Command::COMMAND> GetCommand() { return m_command; }


protected:
	std::vector<Command::COMMAND> m_command;
};
