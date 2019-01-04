#pragma once
#include "Player.h"
#include "Socket.h"

class Game
{
private:
	Player* player1_;
	Player* player2_;

public:
	Game();
	void setPlayer(Player& const player);
	~Game();
};

