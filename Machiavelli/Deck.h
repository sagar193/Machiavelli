#pragma once
#include <vector>
#include "BuildingCard.h"



class Deck
{
public:
	Deck();
	~Deck();
	void load_cards();
	std::vector<BuildingCard> building_cards_;
//private:
//	std::vector<BuildingCard> building_cards_;
};

