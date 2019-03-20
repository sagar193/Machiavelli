#include "pch.h"
#include "PlayingState.h"
#include "random.h"
#include <algorithm>

PlayingState::PlayingState(Game& game) : State(game)
{
	currentState_ = States::InitState;
	placedBuildingCard_ = false;
	usedCharacterCard_ = false;
	drawnBuildingCard1 = nullptr;
	drawnBuildingCard2 = nullptr;
}

void PlayingState::onEnter()
{
	currentState_ = States::InitState;
	placedBuildingCard_ = false;
	usedCharacterCard_ = false;
	this->game_.sendToCurrentPlayer("Jij bent aan de beurt \r\n");
	this->game_.sendToCurrentPlayer("Kies 1 om 2 goudstukken te ontvangen \r\n"
		"Kies 2 om 2 gebouwenkaarten te pakken \r\n");
	//game_.currentClient().get_socket() << "Kill frodo" << "\r\n";
}

bool PlayingState::act(ClientInfo& clientInfo,std::string cmd)
{
	//if (cmd == "quit") {
	//	return true;
	//}

	placeBuildingCard(clientInfo, cmd);

	if (currentState_ == States::InitState) 
	{
		initState(clientInfo, cmd);
	}
	else
	{
		if (chooseState(clientInfo, cmd)) {
			return true;
		}
	}

//	switch (currentState_)
//	{
//	case PlayingState::InitState:
//		initState(clientInfo, cmd);
//		break;
//	case PlayingState::ChooseState:
//		chooseState(clientInfo, cmd);
//		break;
//	case PlayingState::PlaceBuildingCard:
//		placeBuildingCard(clientInfo, cmd);
//		break;
//	case PlayingState::UseCharacterCard:
//		useCharacterCard(clientInfo, cmd);
//		break;
//	}
//	chooseState(clientInfo, cmd);
//	}

	
	return false;
}

void PlayingState::onLeave()
{
}


PlayingState::~PlayingState()
{
}

bool PlayingState::initState(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = std::stoi(cmd);
		if (cmdi == 1){
			game_.currentPlayer().gold(game_.currentPlayer().gold() + 2);

		}
		else if (cmdi == 2) {
			drawnBuildingCard1 = &getRandomBuildingCardFromDeck();
			drawnBuildingCard2 = &getRandomBuildingCardFromDeck();
			game_.sendToCurrentPlayer("Je hebt de volgende kaarten getrokken: \r\n"
			"1 " + drawnBuildingCard1->name() + " \r\n"
			"2 " + drawnBuildingCard2->name() + "\r\n"
			"Kies een van de 2 kaarten om weg te doen");
		}
		else
		{
			this->game_.sendToCurrentPlayer("ongeldige input \r\n");
			onEnter();
		}
	}
	return false;
}

bool PlayingState::chooseState(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = stoi(cmd);
		if (cmdi == 1 && !placedBuildingCard_) {
			currentState_ = PlaceBuildingCard;
		}
		else if (cmdi == 2 && !UseCharacterCard) {
			currentState_ = UseCharacterCard;
		}
		else {
			game_.currentClient().get_socket() << "ongeldige keuze\r\n";
			game_.currentClient().get_socket() << "kies uit een van de volgende mogelijkheden\r\n";
			game_.currentClient().get_socket() << "1: plaats gebouw\r\n";
			game_.currentClient().get_socket() << "2: gebuik\r\n";

			int r1;
			int r2;
			
		}
	}
	return false;
}

bool PlayingState::placeBuildingCard(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty())
	{
		int cmdi = stoi(cmd) - 1;
		if (cmdi == -1)
		{
			return true;
		}
		BuildingCard& chosenCard = game_.buildingCards().at(cmdi);
		if (chosenCard.owner() != game_.currentPlayer().ownertag()) {
			game_.sendToCurrentPlayer("Chosen card is not in your possession, please choose a card in your possession \r\n");
			printAvailableBuildingCards();
			return false;
		}
		else {
			if (chosenCard.cost() > game_.currentPlayer().gold()) {
				game_.sendToCurrentPlayer("You don't have enough gold for the chosen building card \r\n");
				printAvailableBuildingCards();
				return false;
			}
			else {
				game_.currentPlayer().gold(game_.currentPlayer().gold() - chosenCard.cost());
				///place card
				return true;
			}
		}
	}
}

bool PlayingState::useCharacterCard(ClientInfo & clientInfo, std::string cmd)
{
	return false;
}

bool PlayingState::foldBuildingCard(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = stoi(cmd);
		if (cmdi == 1) {
			drawnBuildingCard1 = nullptr;
			drawnBuildingCard1->owner((BuildingCard::Owner)game_.currentPlayer().ownertag());
			return true;
		}
		else if (cmdi == 2) {
			drawnBuildingCard2 = nullptr;
			drawnBuildingCard1->owner((BuildingCard::Owner)game_.currentPlayer().ownertag());
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

BuildingCard & PlayingState::getRandomBuildingCardFromDeck() const
{
	std::vector<int> unused;
	int count = 0;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == BuildingCard::Deck) {
			unused.push_back(count);
		}
		count++;
	});
	int randomint = random_int(0, unused.size() -1);
	return game_.buildingCards().at(randomint);

}

void PlayingState::printAvailableBuildingCards() const
{
	game_.sendToCurrentPlayer("Available cards: \r\n");
	int count = 1;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == game_.currentPlayer().ownertag()) {
			game_.sendToCurrentPlayer(count + " ");
			game_.sendToCurrentPlayer("cardname: " + card.name() + "cost: " + static_cast<char>(card.cost()) + "\r\n");
		}
	});
	game_.sendToCurrentPlayer("press 0 to don't place any buildings\r\n");
}
