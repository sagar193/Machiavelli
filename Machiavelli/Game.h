#pragma once
#include "Player.h"

#include "Socket.h"
#include "CharacterCard.h"
#include "BuildingCard.h"
#include <map>
#include <memory>

class ClientInfo;
class State;
class Game
{
private:
	enum States
	{
		DealCards,
		Playing,
	};
	enum Players
	{
		Player1,
		Player2
	};

	std::map<Players, std::unique_ptr<Player>> players_;
	
	std::shared_ptr<ClientInfo> client_info1;
	std::shared_ptr<ClientInfo> client_info2;
	
	//Player* player1_;
	//Player* player2_;
	ClientInfo* currentClient_;

	std::vector<std::unique_ptr<CharacterCard>> characterCards_;
	std::vector<BuildingCard> buildingCards_;
	std::map<States, std::unique_ptr<State>> states_;
	State* currentState_;

	void loadCharacterCards();

public:
	std::vector<std::unique_ptr<CharacterCard>> characterCards() { return characterCards_; }
	std::vector<BuildingCard> buildingCards() { return buildingCards_; }




	Game();
	void setPlayer(std::shared_ptr<ClientInfo> const clientInfo);
	void handleCommand(std::shared_ptr<ClientInfo> const clientInfo, std::string cmd);
	//void setPlayer(Player& const player);
	//void handleCommand(Player& const player, std::string cmd);
	void startGame();
	~Game();
};

