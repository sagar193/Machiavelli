#pragma once
#include <string>

class CharacterCard
{
public:
	virtual void act() = 0;
	virtual void rank(int const rank) { rank_ = rank; }
	virtual int const rank() const { return rank_; }
	virtual void name(std::string const name) { name_ = name; }
	virtual std::string const name() const { return name_; }
	virtual void gold(int const gold) { gold_ = gold; }
	virtual int const gold() const { return gold_; }


private:
	int rank_;
	std::string name_;
	int gold_;
};

