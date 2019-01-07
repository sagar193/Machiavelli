#include "pch.h"
#include "Deck.h"
#include <iostream>
#include <fstream>
#include <sstream>
Deck::Deck()
{
}


Deck::~Deck()
{
}

void Deck::load_cards()
{
	std::ifstream is("..\\Files\\Bouwkaarten.csv", std::ifstream::binary);
	if (is) {
		
		std::vector<BuildingCard> buffer;
		std::string line;
		//try {
		while (std::getline(is, line)) {
			std::istringstream ss(line);

			std::string name;
			std::string costString;
			std::string colorString;
			std::getline(ss, name, ';');
			std::getline(ss, costString, ';');
			std::getline(ss, colorString, ';');

			auto color = BuildingCard::color(colorString);
			if (color != BuildingCard::NONE) {
				BuildingCard card(name, std::stoi(costString), color);
				//std::cout << card;
				buffer.push_back(card);
			}
			else
			{
				std::cout << "color :" << colorString << " does not exist \n";
			}
			//else
			//{
			//	throw std::exception("color does not exist");
			//}
		}
		this->building_cards_ = buffer;
		//} 
		//catch (std::exception &e)
		//{
		//	int k = 0;
		//}
	}
	else
	{
		std::cout << "file could not be loaded" << std::endl;
	}
	is.close();
}

