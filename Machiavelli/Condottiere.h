#pragma once
#include "CharacterCard.h"

class Condottiere : public CharacterCard
{
private:
	std::string name_;
	int rank_;

public:
	Condottiere();
	Condottiere(const Condottiere& other) = delete;
	Condottiere& operator =(const Condottiere& other) = delete;
	Condottiere(Condottiere&& other) = delete;
	Condottiere& operator=(Condottiere&& other) = delete;
	~Condottiere();

	void act() override;
};

