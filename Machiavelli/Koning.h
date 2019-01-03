#pragma once
#include "CharacterCard.h"

class Koning : public CharacterCard
{
public:
	Koning();
	Koning(const Koning& other) = delete;
	Koning& operator =(const Koning& other) = delete;
	Koning(Koning&& other) = delete;
	Koning& operator=(Koning&& other) = delete;
	~Koning();
};

