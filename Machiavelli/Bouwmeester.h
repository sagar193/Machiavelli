#pragma once
#include "CharacterCard.h"

class Bouwmeester : public CharacterCard
{
//private:
//	std::string name_;
//	int rank_;

public:
	Bouwmeester();
	//Bouwmeester(const Bouwmeester& other) = delete;
	//Bouwmeester& operator =(const Bouwmeester& other) = delete;
	//Bouwmeester(Bouwmeester&& other) = delete;
	//Bouwmeester& operator=(Bouwmeester&& other) = delete;
	~Bouwmeester();

	void act() override;

};

