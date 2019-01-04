#include "pch.h"
#include "Game.h"


Game::Game()
{
	player1_ = nullptr;
	player2_ = nullptr;
}

void Game::setPlayer(Player& const player)
{
	if (player1_ == nullptr) {
		player1_ = &player;
	}
	else if (player2_ == nullptr) {
		player2_ = &player;
	}
	else
		throw std::exception("Game already full");
}


Game::~Game()
{
}
