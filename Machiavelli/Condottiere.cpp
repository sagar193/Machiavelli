#include "pch.h"
#include "Condottiere.h"


Condottiere::Condottiere() : CharacterCard()
{
	this->name_ = "Condottiere";
}


Condottiere::~Condottiere()
{
}

void Condottiere::act()
{
	std::cout << "ehollo";
}
