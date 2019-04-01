#pragma once
#include "CharacterCard.h"
class ClientInfo;
class BuildingCard;
class Bouwmeester : public CharacterCard
{
private:
	std::string name_;

	BuildingCard & getRandomBuildingCardFromDeck() const;
	int countPlacableBuildings;
	bool hasdrawn_;
	void printAllBuidlingCards();
public:
	Bouwmeester(Game& game);
	~Bouwmeester();

	void onEnter() override;
	bool act(ClientInfo& clientInfo, std::string cmd) override;
	void onLeave() override;

	bool usable() const override;
	void name(std::string const name) override;
	std::string const name() const override;

};

