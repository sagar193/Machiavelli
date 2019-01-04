#pragma once
#include "CharacterCard.h"

class Moordenaar : public CharacterCard
{
private:
	std::string name_;
	int rank_;

public:
	Moordenaar();
	Moordenaar(const Moordenaar& other) = delete;
	Moordenaar& operator =(const Moordenaar& other) = delete;
	Moordenaar(Moordenaar&& other) = delete;
	Moordenaar& operator=(Moordenaar&& other) = delete;
	~Moordenaar();

	void act() override;
};

