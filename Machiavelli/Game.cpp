#include "pch.h"
#include "Game.h"
#include "DealCardState.h"
#include "PlayingState.h"
#include "State.h"
#include "ClientInfo.h"
#include "Moordenaar.h"
#include "Dief.h"
#include "Magier.h"
#include "Koning.h"
#include "Prediker.h"
#include "Koopman.h"
#include "Bouwmeester.h"
#include "Condottiere.h"
#include <fstream>
#include <sstream>
#include <algorithm>

//todo: player1 leave 

void Game::loadCharacterCards()
{
	characterCards_.push_back(std::make_unique<Moordenaar>(*this));
	characterCards_.push_back(std::make_unique<Dief>(*this));
	characterCards_.push_back(std::make_unique<Magier>(*this));
	characterCards_.push_back(std::make_unique<Koning>(*this));
	characterCards_.push_back(std::make_unique<Prediker>(*this));
	characterCards_.push_back(std::make_unique<Koopman>(*this));
	characterCards_.push_back(std::make_unique<Bouwmeester>(*this));
	characterCards_.push_back(std::make_unique<Condottiere>(*this));
}

void Game::loadBuildingCards()
{
	std::ifstream is("..\\Files\\Bouwkaarten.csv", std::ifstream::binary);
	if (is) {

		std::vector<BuildingCard> buffer;
		std::string line;
		//try {
		while (std::getline(is, line)) {
			std::istringstream ss(line);

			std::string name;
			std::string costString;
			std::string colorString;
			std::getline(ss, name, ';');
			std::getline(ss, costString, ';');
			std::getline(ss, colorString, ';');

			auto color = BuildingCard::getCollor(colorString);
			if (color != BuildingCard::NONE) {
				BuildingCard card(name, std::stoi(costString), color);
				//std::cout << card;
				buffer.push_back(card);
			}
			else
			{
				std::cout << "color :" << colorString << " does not exist \n";
			}
			//else
			//{
			//	throw std::exception("color does not exist");
			//}
		}
		this->buildingCards_ = buffer;
		//} 
		//catch (std::exception &e)
		//{
		//	int k = 0;
		//}
	}
	else
	{
		std::cout << "file could not be loaded" << std::endl;
	}
	is.close();
}

void Game::switchCurrentClientInfo()
{
	sendToCurrentPlayer("de andere speler is nu aan de beurt");
	if (&(*client_info1) == currentClient_)
		currentClient_ = &(*client_info2);
	else
		currentClient_ = &(*client_info1);
	sendToCurrentPlayer("het is jouw beurt");

}

void Game::setCurrentClient(Players player)
{
	if (player == Players::Player1) 
	{
		currentClient_ = &(*client_info1);
	}
	else if (player == Players::Player2)
	{
		currentClient_ = &(*client_info2);
	}
}

Game::Game()
{
	client_info1 = nullptr;
	client_info2 = nullptr;
	running = true;

	states_[Game::States::DealCards] = std::make_unique<DealCardState>(*this);
	states_[Game::States::Playing] = std::make_unique<PlayingState>(*this);
	currentState_ = nullptr;
	loadCharacterCards();
	loadBuildingCards();
}

void Game::setPlayer(std::shared_ptr<ClientInfo> const clientInfo)
{
	if (client_info1 == nullptr) {
		client_info1 = clientInfo;
		client_info1->get_socket() << "jij bent speler1\r\n";
		client_info1->get_player().ownertag(Owner::Player1);
		//client_info1->get_player().playertag(Players::Player1);
	}
	else if (client_info2 == nullptr) {
		client_info2 = clientInfo;
		client_info2->get_socket() << "jij bent speler2\r\n";
		client_info2->get_player().ownertag(Owner::Player2);
		//client_info2->get_player().playertag(Players::Player2);
	}
	else {
		//todo: je moet eerst iets schrijven is niet mooi nicht richtig
		clientInfo->get_socket() << "fuck off, game is full!!!!!!!!!!\r\n";
		throw std::exception("Game already full");
	}
	
	if (client_info1 != nullptr && client_info2 != nullptr) {
		startGame();
	}
}

bool Game::handleCommand(std::shared_ptr<ClientInfo> const clientInfo, std::string cmd)
{
		endGame();
		return running;
	if (currentClient_ == &(*clientInfo)) {
		auto callback = currentState_->act(*clientInfo, cmd);
		if (callback == true) {
		}
	}
	else {
		clientInfo->get_socket() << "je bent niet aan de beurt\r\n";
	}
	return running;
}

Player & Game::currentPlayer()
{
	return currentClient_->get_player();
}

void Game::sendToCurrentPlayer(const std::string message) const
{
	currentClient_->get_socket() << message << "\r\n";
}

void Game::sendToAllPlayers(const std::string message) const
{
	client_info1->get_socket() << message << "\r\n";
	client_info2->get_socket() << message << "\r\n";
}

void Game::setState(States state)
{
	currentState_ = states_[state].get();
}

ClientInfo & Game::getPlayer(CharacterCardEnum characterCardEnum)
{
	std::for_each(characterCards_.begin(), characterCards_.end(), [&](const std::unique_ptr<CharacterCard>& card)
	{
		if (card->characterCardIdentifier() == characterCardEnum) {
			return &getPlayer(card->owner());
		}
	});
	throw "getting non existing character";

}

ClientInfo & Game::getPlayer(Owner owner)
{
	if (client_info1->get_player().ownertag() == owner)
	{
		return *client_info1;
	}
	else if (client_info2->get_player().ownertag() == owner)
	{
		return *client_info2;
	}
	else {
		throw "getting non existing owner";
	}
}



void Game::startGame()
{
	
	
	currentState_ = states_[States::DealCards].get();
	currentState_->onEnter();

	
}

void Game::endGame()
{
	sendToAllPlayers("Game has ended");
	running == false;
}


Game::~Game()
{
}
