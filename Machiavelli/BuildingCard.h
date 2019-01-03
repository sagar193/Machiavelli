#pragma once
#include <string>

class BuildingCard
{
private:
	int color_;
	std::string name_;
	int gold_;

public:
	BuildingCard();
	BuildingCard(const BuildingCard& other) = delete;
	BuildingCard& operator =(const BuildingCard& other) = delete;
	BuildingCard(BuildingCard&& other) = delete;
	BuildingCard& operator=(BuildingCard&& other) = delete;
	~BuildingCard();

	void color(int const color);
	int const color() const;
	void name(std::string const name);
	std::string const name() const;
	void gold(int const gold);
	int const gold() const;


	enum color
	{
		YELLOW,
		BLAUW,
		GROEN,
		ROOD
	};
};

