#pragma once
#include "CharacterCard.h"

class Magier : public CharacterCard
{
public:
	Magier();
	Magier(const Magier& other) = delete;
	Magier& operator =(const Magier& other) = delete;
	Magier(Magier&& other) = delete;
	Magier& operator=(Magier&& other) = delete;
	~Magier();
};

