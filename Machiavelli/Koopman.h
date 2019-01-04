#pragma once
#include "CharacterCard.h"

class Koopman : public CharacterCard
{
private:
	std::string name_;
	int rank_;

public:
	Koopman();
	Koopman(const Koopman& other) = delete;
	Koopman& operator =(const Koopman& other) = delete;
	Koopman(Koopman&& other) = delete;
	Koopman& operator=(Koopman&& other) = delete;
	~Koopman();

	void act() override;
	void rank(int const rank) override;
	int const rank() const override;
	void name(std::string const name) override;
	std::string const name() const override;
};

