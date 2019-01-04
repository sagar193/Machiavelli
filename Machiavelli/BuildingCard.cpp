#include "pch.h"
#include "BuildingCard.h"

BuildingCard::BuildingCard(std::string name, int cost, colorTypes color)
{
	name_ = name;
	cost_ = cost;
	color_ = color;
}

BuildingCard::~BuildingCard()
{
}

std::ostream & BuildingCard::operator<<(std::ostream & os) const
{
	os << name_ << " " << cost_ << " ";
	return os;
}

void BuildingCard::color(colorTypes color)
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

BuildingCard::colorTypes BuildingCard::getCollor(std::string color)
{
	if (color._Equal("geel"))
	{
		return GEEL;
	}
	if (color._Equal("blauw"))
	{
		return BLAUW;
	}
	if (color._Equal("groen"))
	{
		return GROEN;
	}
	if (color._Equal("rood"))
	{
		return ROOD;
	}
	return NONE;
}
/*
std::istream & operator>>(std::istream & strm,BuildingCard & card)
{
	std::string name;
	int cost;
	std::string color;
	auto colorExist = true;
	if (strm >> name >> cost >> color)
	{
		
		if(color._Equal("geel"))
		{
			card.color(BuildingCard::colorTypes::GEEL);
		} 
		else if(color._Equal("blauw"))
		{
			card.color(BuildingCard::colorTypes::BLAUW);
		}
		else if (color._Equal("groen"))
		{
			card.color(BuildingCard::colorTypes::GROEN);
		}
		else if (color._Equal("rood"))
		{
			card.color(BuildingCard::colorTypes::ROOD);
		}
		else
		{
			colorExist = false;
		}

		if(colorExist)
		{
			card.name(name);
			card.cost(cost);
		}
	}
	return strm;
}*/
