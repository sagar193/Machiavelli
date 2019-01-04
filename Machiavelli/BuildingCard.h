#pragma once
#include <string>
#include <ostream>

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
	BuildingCard() = default;
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
	static colorTypes getCollor(std::string color);
private:
	colorTypes color_;
	std::string name_;
	int cost_;
};