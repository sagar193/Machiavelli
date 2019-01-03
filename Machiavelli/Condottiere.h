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
	void rank(int const rank) override;
	int const rank() const override;
	void name(std::string const name) override;
	std::string const name() const override;
};

