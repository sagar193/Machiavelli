#pragma once
#include "Player.h"

#include "Socket.h"
#include "CharacterCard.h"
#include "BuildingCard.h"
#include <map>
#include <memory>

class State;
class Game
{
private:
	enum States
	{
		DealCards,
		Playing,
	};

	Player* player1_;
	Player* player2_;
	std::vector<CharacterCard> characterCards_;
	std::vector<BuildingCard> buildingCards_;
	std::map<States, std::unique_ptr<State>> states_;
	State* currentState_;
public:
	Game();
	void setPlayer(Player& const player);
	void handleCommand(Player& const player, std::string cmd);
	void startGame();
	~Game();
};

