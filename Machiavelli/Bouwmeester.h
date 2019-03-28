#pragma once
#include "CharacterCard.h"
class ClientInfo;
class BuildingCard;
class Bouwmeester : public CharacterCard
{
private:
	std::string name_;
	int rank_;

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

	void rank(int const rank) override;
	int const rank() const override;
	void name(std::string const name) override;
	std::string const name() const override;

};

