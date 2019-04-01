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
		EndState,
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
	bool placeBuildingCard(ClientInfo& clientInfo, std::string cmd);
	bool useCharacterCard(ClientInfo& clientInfo, std::string cmd);
	bool foldBuildingCard(ClientInfo& clientInfo, std::string cmd);
	bool endState(ClientInfo& clientInfo, std::string cmd);
	void returnToLastState();

	BuildingCard& getRandomBuildingCardFromDeck() const;
	BuildingCard* drawnBuildingCard1;
	BuildingCard* drawnBuildingCard2;
	void printBuildingCards() const;
	void drawBuildingCards();

	int currentCharacterIndex;
	void printHandMessage();

	void printAvailableBuildingCards() const;
	void printCurrentPlayerBuildingCardsNonActive() const;
	void printCurrentPlayerBuildingCardsActive() const;
	void printEndStateOptions() const;

	void printOrDontCharacterCardOption() const;
	void printInitState() const;
	bool lastround;
	void calcPoints();
	void calcColorPoints();
	void calcBuildingPoints();
	void endGame();

	bool initStateDone_;
	bool placeBuildingCardDone_;
	bool inFoldState_;
	bool endStateDone_;
	//Game::Players endPlayer;
};

