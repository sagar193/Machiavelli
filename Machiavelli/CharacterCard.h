#pragma once
#include <string>
#include "Owner.h"

class CharacterCard
{
public:
	CharacterCard();
	virtual void act() = 0;
	virtual void rank(int const rank) = 0;
	virtual int const rank() const = 0;
	virtual void name(std::string const name) = 0;
	virtual std::string const name() const = 0;
	Owner owner() { return owner_; }
	void owner(Owner owner) { owner_ = owner; }
private:
	Owner owner_;
};

