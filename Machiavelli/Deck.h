#pragma once
#include <vector>
#include "BuildingCard.h"



class Deck
{
public:
	Deck();
	~Deck();
	void load_cards();
private:
	std::vector<BuildingCard> building_cards_;
};

