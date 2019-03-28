//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "pch.h"
#include "Player.h"
#include "Game.h"
#include <algorithm>

using namespace std;

Player::Player() {
	ownertag_ = Owner::None;
	isKing_ = false;
	gold_ = 10;
	points_ = 0;
	//playertag_ = Game::Players::None;
}

std::string const Player::name() const
{
	return name_;
}

void Player::name(const std::string& new_name)
{
	name_ = new_name;
}

int const Player::age() const
{
	return age_;
}

int Player::countBuildings(Game& game)
{
	int count = 0;
	std::for_each(game.buildingCards().begin(), game.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == ownertag_ && card.active()) {
			count++;
		}
	});
	return count;
}

int Player::countBuidlingPounts(Game & game)
{
	int count = 0;
	std::for_each(game.buildingCards().begin(), game.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == ownertag_ && card.active()) {
			count+=card.cost();
		}
	});
	return count;
}

bool Player::hasAllColors(Game & game)
{
	//todo:
	int countColors = 4;
	std::vector<int> colors(countColors);
	std::for_each(colors.begin(), colors.end(), [&](int& i)
	{
		i = 0;
	});
	std::for_each(game.buildingCards().begin(), game.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == ownertag_ && card.active()) {
			if (card.color() == BuildingCard::GEEL) {
				colors[0]++;
			}
			else if (card.color() == BuildingCard::BLAUW) {
				colors[1]++;
			}
			else if (card.color() == BuildingCard::ROOD) {
				colors[2]++;
			}
			else if (card.color() == BuildingCard::GROEN) {
				colors[3]++;
			}
		}
	});

	bool hasAllColors = true;
	std::for_each(colors.begin(), colors.end(), [&](int& i)
	{
		if (i <= 0) {
			hasAllColors = false;
		}
	});
	return hasAllColors;
}

