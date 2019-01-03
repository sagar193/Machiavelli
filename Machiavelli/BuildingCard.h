#pragma once
class BuildingCard
{
	int color;


public:
	BuildingCard();
	BuildingCard(const BuildingCard& other) = delete;
	BuildingCard& operator =(const BuildingCard& other) = delete;
	BuildingCard(BuildingCard&& other) = delete;
	BuildingCard& operator=(BuildingCard&& other) = delete;
	~BuildingCard();

	enum color
	{
		YELLOW,
		BLAUW,
		GROEN,
		ROOD
	};
};

