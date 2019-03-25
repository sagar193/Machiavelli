#pragma once
#include "State.h"

class Game;
class ClientInfo;
class BuildingCard;
class PlayingState : public State
{
public:
	enum States {
		InitState,
		ChooseState,
		PlaceBuildingCard,
		UseCharacterCard,
		FoldBuildingCard
	};
	PlayingState(Game& game);
	void onEnter() override;
	bool act(ClientInfo& clientInfo,std::string cmd) override;
	void onLeave() override;
	~PlayingState();
private:
	States currentState_;
	bool initState(ClientInfo& clientInfo, std::string cmd);
	bool chooseState(ClientInfo& clientInfo, std::string cmd);
	bool placeBuildingCard(ClientInfo& clientInfo, std::string cmd);
	bool useCharacterCard(ClientInfo& clientInfo, std::string cmd);
	bool foldBuildingCard(ClientInfo& clientInfo, std::string cmd);
	bool initState_;
	bool placedBuildingCard_;
	bool usedCharacterCard_;
	bool foldBuildingCard_;
	BuildingCard& getRandomBuildingCardFromDeck() const;
	//BuildingCard& getBuildingCardFromPlayer() const;
	BuildingCard* drawnBuildingCard1;
	BuildingCard* drawnBuildingCard2;
	void drawBuildingCards();
	int currentCharacterIndex;
	void printChooseStateOptions();

	void printAvailableBuildingCards() const;

};

