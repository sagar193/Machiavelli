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
	void rank(int const rank) override;
	int const rank() const override;
	void name(std::string const name) override;
	std::string const name() const override;
};

