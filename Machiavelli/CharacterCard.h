#pragma once
#include <string>
#include "Game.h"

class CharacterCard
{
public:
	CharacterCard()
	{
		owner_ = DECK;
		used_ = false;
	}
	virtual ~CharacterCard() = default;
	virtual void act() = 0;
	std::string name() const { return name_; }
	CardOwners owner() const { return owner_; }
	void owner(CardOwners new_owner) { owner_ = new_owner; }
	bool used() const { return used_; }
	void use() { used_ = true; }
	void reset()
	{
		used_ = false;
		owner_ = DECK;
	}
	
protected:
	std::string name_;
	CardOwners owner_;
	bool used_;
};

