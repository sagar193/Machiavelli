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
public:
	enum Players
	{
		Player1,
		Player2
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
	void handleCommand(std::shared_ptr<ClientInfo> const clientInfo, std::string cmd);

	ClientInfo& currentClient() { return *currentClient_; }
	void setState(States state);

	//void setPlayer(Player& const player);
	//void handleCommand(Player& const player, std::string cmd);
	void startGame();
	~Game();
private:

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

};

