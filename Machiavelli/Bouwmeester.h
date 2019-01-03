#pragma once
#include "CharacterCard.h"

class Bouwmeester : public CharacterCard
{
public:
	Bouwmeester();
	Bouwmeester(const Bouwmeester& other) = delete;
	Bouwmeester& operator =(const Bouwmeester& other) = delete;
	Bouwmeester(Bouwmeester&& other) = delete;
	Bouwmeester& operator=(Bouwmeester&& other) = delete;
	~Bouwmeester();


};

