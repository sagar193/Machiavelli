#pragma once
#include "CharacterCard.h"

class Prediker : public CharacterCard
{
public:
	Prediker();
	Prediker(const Prediker& other) = delete;
	Prediker& operator =(const Prediker& other) = delete;
	Prediker(Prediker&& other) = delete;
	Prediker& operator=(Prediker&& other) = delete;
	~Prediker();
};

