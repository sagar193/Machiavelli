#include "pch.h"
#include "BuildingCard.h"


BuildingCard::BuildingCard()
{
}


BuildingCard::~BuildingCard()
{
}

void BuildingCard::color(int const color)
{
	color_ = color;
}

int const BuildingCard::color() const
{
	return color_;
}

void BuildingCard::name(std::string const name)
{
	name_ = name;
}

std::string const BuildingCard::name() const
{
	return name_;
}

void BuildingCard::cost(int const cost)
{
	cost_ = cost;
}

int const BuildingCard::cost() const
{
	return cost_;
}
