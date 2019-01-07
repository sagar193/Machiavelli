#pragma once
#include <string>
#include <ostream>
#include "Game.h"

class BuildingCard
{
public:
	enum colorTypes
	{
		GEEL,
		BLAUW,
		GROEN,
		ROOD,
		NONE
	};
	BuildingCard();
	BuildingCard(std::string name,int cost,colorTypes color);
	//BuildingCard(const BuildingCard& other) = delete;
	//BuildingCard& operator =(const BuildingCard& other) = delete;
	//BuildingCard(BuildingCard&& other) = delete;
	//BuildingCard& operator=(BuildingCard&& other) = delete;
	~BuildingCard();

	//friend std::istream &operator>>(std::istream &strm,BuildingCard &card);
	std::ostream &operator<<(std::ostream &os) const;

	void color(colorTypes color);
	int const color() const;
	void name(std::string const name);
	std::string const name() const;
	void cost(int const cost);
	int const cost() const;
	static colorTypes color(std::string color);
	CardOwners owner() const { return owner_; }
	void owner(CardOwners owner) { owner_ = owner; }
	void reset() { owner_ = DECK; }
private:
	colorTypes color_;
	std::string name_;
	int cost_;
	CardOwners owner_;
};
