#pragma once
#include <string>
#include "Game.h"

class CharacterCard
{
public:
	CharacterCard()
	{
	//	rank_ = 0;
	//	gold_ = 0;
		owner_ = Game::cardOwners::DECK;
	}
	virtual void act() = 0;
	//void rank(int const rank) { rank_ = rank; }
	//int const rank() const { return rank_; }
	
	std::string const name() const { return name_; }
	//void gold(int const gold) { gold_ = gold; }
	//int const gold() const { return gold_; }
	Game::cardOwners owner() { return owner_; }
	void owner(Game::cardOwners newOwner) { owner_ = newOwner; }
	//void owner(Game::cardOwners newOwner) { owner_ = newOwner };
	//virtual ~CharacterCard() = 0;
protected:
	//void name(std::string name) { name_ = name; }

	//int rank_;
	std::string name_;
	//int gold_;
	Game::cardOwners owner_;
};

