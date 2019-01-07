#pragma once
#include "Player.h"
#include "Socket.h"

#include <map>
//#include "CharacterCard.h"

class CharacterCard;
class Game
{
public:
	enum cardOwners
	{
		PLAYER1,
		PLAYER2,
		DECK,
		GRAVE
	};

	void startGame();
	void playGame();
	void dealCards();
	void dealCards(Player& const player, std::map<int,int> deckMap,std::string cmd);

	void handleCommand(Player& const player);
	void handleCommand(Player& const player,std::string cmd);

	Game();
	void setPlayer(Player& const player);
	~Game();

	int getUnownedCharacterCards() const;
	
	void printUnownedCharacterCards() const;
	void printDeckMap(Player& player, std::map<int, int> map) const;

	int getAmountCharacterCardsOwned(cardOwners owner) const;
	int getAmountCharacterCardsOwnedByCurrentPlayer() const;

	std::map<int, int> mapDeckCards() const;

	bool pickCharacterCard(Player& const player, std::map<int, int> deckMap, std::string cmd);
	bool turnCharacterCard(Player& const player, std::map<int, int> deckMap, std::string cmd);

	Player& getCurrentPlayer();
	Player& getOtherPlayer();

	bool isCurrentPlayer(const Player & player);

	void printChooseAbleCharacters(Player & player) const;
	void enterDealState();

	void printEnterPickCardState(Player & player) const;
	void printEnterTurnCardState(Player & player) const;
private:
	enum state
	{
		WAITINGPLAYERS,
		PICKINGCHARACTERCARDS,
		TURNINGCHARACTERCARDS,
		DEALINGCARDS
	};

	void switchPlayer();

	void initGame();
	Player* player1_;
	Player* player2_;
	int playerSwitched;

	std::vector<std::unique_ptr<CharacterCard>> character_cards_;
	std::map<std::unique_ptr<CharacterCard>, Player*> character_distribution_;
	std::map<cardOwners, Player*> ownerPlayerMap;
	std::map<Player*, cardOwners> playerOwnerMap;


	bool running_;
	state current_state_;
	int current_player_;


	std::map<int, Player*> player_index_;
};

