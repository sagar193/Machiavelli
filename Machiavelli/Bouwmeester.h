#pragma once
#include "CharacterCard.h"

class Bouwmeester : public CharacterCard
{
private:
	std::string name_;
	int rank_;

public:
	Bouwmeester();
	Bouwmeester(const Bouwmeester& other) = delete;
	Bouwmeester& operator =(const Bouwmeester& other) = delete;
	//Bouwmeester(Bouwmeester&& other) = delete;
	//Bouwmeester& operator=(Bouwmeester&& other) = delete;
	~Bouwmeester();

	void act() override;
	void rank(int const rank) override;
	int const rank() const override;
	void name(std::string const name) override;
	std::string const name() const override;

};

