#include "pch.h"
#include "Game.h"
#include "DealCardState.h"
#include "State.h"

Game::Game()
{
	player1_ = nullptr;
	player2_ = nullptr;

	states_[Game::States::DealCards] = std::make_unique<DealCardState>(*this);


}



void Game::setPlayer(Player& const player)
{
	if (player1_ == nullptr) {
		player1_ = &player;
		player1_->socket() << "jij bent speler1";
	}
	else if (player2_ == nullptr) {
		player2_ = &player;
		player2_->socket() << "jij bent speler2";
	}
	else {
		//todo: je moet eerst iets schrijven is niet mooi nicht richtig
		player.socket() << "fuck off, game is full!!!!!!!!!!";
		throw std::exception("Game already full");
	}

	if (player1_ != nullptr && player2_ != nullptr) {
		startGame();
	}
}

void Game::handleCommand(Player & const player, std::string cmd)
{
	
}

void Game::startGame()
{
	if (player1_->age() >= player2_->age()) {
		player1_->socket() << "jij bent koning!";
		player2_->socket() << "speler1 is koning";
		player1_->isKing(true);
	}
	else {
		player2_->socket() << "jij bent koning!";
		player1_->socket() << "speler2 is koning";
		player2_->isKing(true);
	}

	currentState_ = nullptr;
}


Game::~Game()
{
}
