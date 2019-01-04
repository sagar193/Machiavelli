#pragma once
#include "CharacterCard.h"

class Magier : public CharacterCard
{
private:
	std::string name_;
	int rank_;

public:
	Magier();
	Magier(const Magier& other) = delete;
	Magier& operator =(const Magier& other) = delete;
	Magier(Magier&& other) = delete;
	Magier& operator=(Magier&& other) = delete;
	~Magier();

	void act() override;
};

