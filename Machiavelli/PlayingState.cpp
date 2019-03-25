#include "pch.h"
#include "PlayingState.h"
#include "random.h"
#include <algorithm>
#include "ClientInfo.h"
#include "Game.h"

PlayingState::PlayingState(Game& game) : State(game)
{
	currentState_ = States::InitState;
	placedBuildingCard_ = false;
	usedCharacterCard_ = false;
	drawnBuildingCard1 = nullptr;
	drawnBuildingCard2 = nullptr;
	initState_ = false;

	currentCharacterIndex = 0;
}

void PlayingState::onEnter()
{
	int count = 0;
	auto position = std::find_if(game_.characterCards().begin(), game_.characterCards().end(), [&](std::unique_ptr<CharacterCard>& card) 
	{
		if (card->owner() != Owner::Deck && card->owner() != Owner::None) {
			return true;
		}
		count++;
		return false;
	});

	if (position != game_.characterCards().end()) {
		currentCharacterIndex = count;

		placedBuildingCard_ = false;
		usedCharacterCard_ = false;
		initState_ = false;
		currentState_ = States::ChooseState;

		//todo: set current player lelijk
		//todo: vertel aan de andere speler dat die moet wachten
		if (game_.characterCards()[currentCharacterIndex]->owner() == Owner::Player1) {
			game_.setCurrentClient(Game::Players::Player1);
			game_.sendToAllPlayers("de " + game_.characterCards()[currentCharacterIndex]->name() + " (speler1) is aan de beurt\r\n");
		}
		else 
		{
			game_.setCurrentClient(Game::Players::Player2);
			game_.sendToAllPlayers("de " + game_.characterCards()[currentCharacterIndex]->name() + " (speler2) is aan de beurt\r\n");
		}
		printChooseStateOptions();
	}
	else
	{
		//todo: niet netjes
		placedBuildingCard_ = true;
		usedCharacterCard_ = true;
		initState_ = true;
		currentCharacterIndex = -1;
	}
}

bool PlayingState::act(ClientInfo& clientInfo,std::string cmd)
{
	//er is iets fout gegaan
	if (currentCharacterIndex == -1) {
		onLeave();
		return false;
	}
	else {
		switch (currentState_)
		{
		case PlayingState::InitState:
			if (initState(clientInfo, cmd)) {
				initState_ = true;
				currentState_ = ChooseState;
			};
			break;
		case PlayingState::ChooseState:
			if (chooseState(clientInfo, cmd))
			{
				placedBuildingCard_ = true;
				usedCharacterCard_ = true;
				initState_ = true;
			}
			break;
		case PlayingState::PlaceBuildingCard:
			if (placeBuildingCard(clientInfo, cmd))
			{
				placedBuildingCard_ = true;
				currentState_ = ChooseState;
			}
			break;
		case PlayingState::UseCharacterCard:
			if (useCharacterCard(clientInfo, cmd))
			{
				usedCharacterCard_ = true;
				currentState_ = ChooseState;
			}
			break;
		}

		//todo:leave
		if (placedBuildingCard_ && usedCharacterCard_ && initState_) {
			onLeave();
			return true;
		}
		else if (currentState_ == ChooseState) {
			//todo: print options
			game_.currentClient().get_socket() << "kies uit een van de volgende mogelijkheden\r\n";
			printChooseStateOptions();
		}
	}
	return false;
}

void PlayingState::onLeave()
{
	game_.characterCards()[currentCharacterIndex]->owner(Owner::None);
	onEnter();
	if (currentCharacterIndex == -1) 
	{
		game_.setState(Game::DealCards);
		game_.currentState().onEnter();
	}
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
			return true;
		}
		else if (cmdi == 2) {
			drawnBuildingCard1 = &getRandomBuildingCardFromDeck();
			drawnBuildingCard2 = &getRandomBuildingCardFromDeck();
			game_.sendToCurrentPlayer("Je hebt de volgende kaarten getrokken: \r\n"
			"1 " + drawnBuildingCard1->name() + " \r\n"
			"2 " + drawnBuildingCard2->name() + "\r\n"
			"Kies een van de 2 kaarten om weg te doen");
			//todo: foldcard return true
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
		if (cmdi == 0) {
			if (initState_) {
				return true;
			}
			else {
				game_.currentClient().get_socket() << "de beurt mag niet eindigen zonder dat optie 1 gekozen is\r\n";
			}
		}
		else if (cmdi == 1 && !initState_) {
			currentState_ = InitState;
			//todo:text opties
			game_.currentClient().get_socket() << "kies een van de volgende opties\r\n";
			game_.currentClient().get_socket() << "1: pak 2 goudstukken\r\n";
			game_.currentClient().get_socket() << "2: pak 1 gebouwkaart en leg een weg\r\n";
		}
		else if (cmdi == 2 && !placedBuildingCard_) {
			currentState_ = PlaceBuildingCard;
			//todo:text opties
			printAvailableBuildingCards();
		}
		else if (cmdi == 3 && !usedCharacterCard_) {
			currentState_ = UseCharacterCard;
			//todo:text opties
		}
		else {
			game_.currentClient().get_socket() << "ongeldige keuze\r\n";
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
		//todo: out of range error
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
			drawnBuildingCard1->owner(game_.currentPlayer().ownertag());
			return true;
		}
		else if (cmdi == 2) {
			drawnBuildingCard2 = nullptr;
			drawnBuildingCard1->owner(game_.currentPlayer().ownertag());
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
		if (card.owner() == Owner::Deck) {
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

void PlayingState::printChooseStateOptions()
{
	if (!initState_) {
		game_.sendToCurrentPlayer("1: pak 2 munten of pak 1 en leg 1 gebouwkaart weg");
	}
	if (!placedBuildingCard_) {
		game_.sendToCurrentPlayer("2: plaats gebouw");
	}
	if (!usedCharacterCard_) {
		game_.sendToCurrentPlayer("3: gebuik karakterkaart");
	}
	game_.sendToCurrentPlayer("0: stop beurt");
}
