#pragma once
#include "CharacterCard.h"

class Condottiere : public CharacterCard
{
public:
	Condottiere();
	Condottiere(const Condottiere& other) = delete;
	Condottiere& operator =(const Condottiere& other) = delete;
	Condottiere(Condottiere&& other) = delete;
	Condottiere& operator=(Condottiere&& other) = delete;
	~Condottiere();
};

