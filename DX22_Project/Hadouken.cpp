#include "Hadouken.h"

Hadouken::Hadouken()
{
	m_command = {
		{2, false, false, false, false, false, false},
		{3, false, false, false, false, false, false},
		{6, false, false, false, false, false, false},
		{0, true, false, false, false, false, false},
	};
}

Hadouken::~Hadouken()
{
}

void Hadouken::Action()
{
	std::cout << "hadouken" << std::endl;
}
