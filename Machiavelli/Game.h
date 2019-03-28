#pragma once
#include "Player.h"

#include "Socket.h"
//#include "CharacterCard.h"
#include "BuildingCard.h"
#include <map>
#include <memory>
//#include "ClientInfo.h"

class CharacterCard;
class ClientInfo;
class State;
class Game
{
public:
	enum Players
	{
		Player1,
		Player2,
		None
	};

	enum States
	{
		DealCards,
		Playing,
	};
	std::vector<std::unique_ptr<CharacterCard>>& characterCards() { return characterCards_; }
	std::vector<BuildingCard>& buildingCards() { return buildingCards_; }

	ClientInfo& client1() { return *client_info1; }
	ClientInfo& client2() { return *client_info2; }

	State& currentState() { return *currentState_; }

	void switchCurrentClientInfo();
	void setCurrentClient(Game::Players player);

	Game();
	void setPlayer(std::shared_ptr<ClientInfo> const clientInfo);
	bool handleCommand(std::shared_ptr<ClientInfo> const clientInfo, std::string cmd);

	ClientInfo& currentClient() { return *currentClient_; }
	Player& currentPlayer();
	void sendToCurrentPlayer(const std::string message) const;
	void sendToAllPlayers(const std::string message) const;
	void setState(States state);
	ClientInfo& getPlayer(CharacterCardEnum characterCardEnum);
	ClientInfo& getPlayer(Owner owner);

	//void setPlayer(Player& const player);
	//void handleCommand(Player& const player, std::string cmd);
	void startGame();
	void endGame();
	~Game();
private:

	std::map<Players, std::unique_ptr<Player>> players_;

	std::shared_ptr<ClientInfo> client_info1;
	std::shared_ptr<ClientInfo> client_info2;

	//Player* player1_;
	//Player* player2_;
	ClientInfo* currentClient_;
	bool running;

	std::vector<std::unique_ptr<CharacterCard>> characterCards_;
	std::vector<BuildingCard> buildingCards_;
	std::map<States, std::unique_ptr<State>> states_;
	State* currentState_;

	void loadCharacterCards();
	void loadBuildingCards();

};

