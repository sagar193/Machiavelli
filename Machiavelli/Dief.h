#pragma once
#include "CharacterCard.h"

class Dief : public CharacterCard
{
public:
	Dief();
	Dief(const Dief& other) = delete;
	Dief& operator =(const Dief& other) = delete;
	Dief(Dief&& other) = delete;
	Dief& operator=(Dief&& other) = delete;
	~Dief();
};

