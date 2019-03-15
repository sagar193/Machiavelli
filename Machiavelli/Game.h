#pragma once
#include "Player.h"
#include "Socket.h"

#include <map>
#include "Players.h"
#include "CardOwners.h"
//#include "BuildingCard.h"

class BuildingCard;
class CharacterCard;
class State;
class Game
{
public:
	enum state
	{
		WAITINGPLAYERS,
		DEALINGCARDS,
		PLAYERTURN,
	};

	void startGame();

	void handleCommand(Player& const player,std::string cmd);

	Game();
	void setPlayer(Player& const player);
	~Game();

	void printCharacterMap(Player& player, std::map<int, int> map) const;
	void printBuildingMap(Player& player, std::map<int, int> map);

	int getAmountCharacterCardsOwned(CardOwners owner) const;
	int getAmountCharacterCardsOwnedByCurrentPlayer() const;

	std::map<int, int> mapCharacterCards(CardOwners owner) const;
	std::map<int, int> mapBuildingCards(CardOwners owner) const;



	void printChooseAbleCharacters(Player & player) const;
	void printChooseAbleBuildings(Player & player);


	void shuffleCharacterCards();
	void shuffleBuildingCards();

	Players& players() const { return *players_; }
	//std::vector<std::unique_ptr<BuildingCard>>& building_cards() { return building_cards_; }

	void ownCharacterCard(int cardIndex, CardOwners owner);
	void ownBuildingCard(int cardIndex, CardOwners owner);

	void set_current_state(state newState);
	int get_first_unused_owned_character_card() const;
	std::unique_ptr<CharacterCard>& get_card_at(int index);
	std::unique_ptr<BuildingCard>& get_buildingcard_at(int index);


private:
	void initGame();
	std::unique_ptr<Players> players_;
	Player* player1_;
	Player* player2_;
	
	int playerSwitched;
	int currentCharacterIndex;

	std::vector<std::unique_ptr<CharacterCard>> character_cards_;
	std::vector< std::unique_ptr<BuildingCard>> building_cards_;
	std::map<int, int> building_card_map_;
	std::map<std::unique_ptr<CharacterCard>, Player*> character_distribution_;
	std::map<CardOwners, Player*> ownerPlayerMap;
	std::map<Player*, CardOwners> playerOwnerMap;
	std::map<state,std::unique_ptr<State>> states_;

	bool running_;
	state current_state_;
	int current_player_;


	std::map<int, Player*> player_index_;
	void load_building_cards();
};

