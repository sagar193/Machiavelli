#pragma once
#include "CharacterCard.h"

class Koopman : public CharacterCard
{
//private:
//	std::string name_;
//	int rank_;

public:
	Koopman();
	//Koopman(const Koopman& other) = delete;
	//Koopman& operator =(const Koopman& other) = delete;
	//Koopman(Koopman&& other) = delete;
	//Koopman& operator=(Koopman&& other) = delete;
	~Koopman();

	void act() override;
};

