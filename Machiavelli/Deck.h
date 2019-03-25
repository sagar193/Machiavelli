#pragma once
#include <vector>
#include "BuildingCard.h"



class Deck
{
public:
	Deck();
	~Deck();
private:
	std::vector<BuildingCard> building_cards_;
};

