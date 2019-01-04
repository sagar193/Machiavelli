#pragma once
#include <string>

class CharacterCard
{
public:
	virtual void act() = 0;
	virtual void rank(int const rank) = 0;
	virtual int const rank() const = 0;
	virtual void name(std::string const name) = 0;
	virtual std::string const name() const = 0;

private:
};

