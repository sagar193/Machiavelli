#pragma once
#include "CharacterCard.h"

class Prediker : public CharacterCard
{
//private:
//	std::string name_;
//	int rank_;

public:
	Prediker();
	//Prediker(const Prediker& other) = delete;
	//Prediker& operator =(const Prediker& other) = delete;
	//Prediker(Prediker&& other) = delete;
	//Prediker& operator=(Prediker&& other) = delete;
	~Prediker();

	void act() override;
};

