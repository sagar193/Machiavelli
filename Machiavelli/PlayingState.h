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
		FoldBuildingCard,
		OptCharacterState
	};
	PlayingState(Game& game);
	void onEnter() override;
	bool act(ClientInfo& clientInfo,std::string cmd) override;
	void onLeave() override;
	~PlayingState();
private:
	States currentState_;
	States prevState_;
	bool initState(ClientInfo& clientInfo, std::string cmd);
	bool optCharacterState(ClientInfo& clientInfo, std::string cmd);
	void chooseState();
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
	void printCurrentPlayerBuildingCardsNonActive() const;
	void printCurrentPlayerBuildingCardsActive() const;
	bool lastround;
	void calcPoints();
	void calcColorPoints();
	void calcBuildingPoints();
	void endGame();
	//Game::Players endPlayer;
};

