#pragma once
#include "CharacterCard.h"

class Moordenaar : public CharacterCard
{
public:
	Moordenaar();
	Moordenaar(const Moordenaar& other) = delete;
	Moordenaar& operator =(const Moordenaar& other) = delete;
	Moordenaar(Moordenaar&& other) = delete;
	Moordenaar& operator=(Moordenaar&& other) = delete;
	~Moordenaar();
};

