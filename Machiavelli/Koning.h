#pragma once
#include "CharacterCard.h"

class Koning : public CharacterCard
{
private:
	std::string name_;
	int rank_;

public:
	Koning();
	~Koning();

	void act() override;
	void rank(int const rank) override;
	int const rank() const override;
	void name(std::string const name) override;
	std::string const name() const override;
};

