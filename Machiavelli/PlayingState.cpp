#include "pch.h"
#include "PlayingState.h"
#include <algorithm>


PlayingState::PlayingState(Game& game) : State(game)
{
	currentState_ = States::InitState;
	placedBuildingCard_ = false;
	usedCharacterCard_ = false;
	initState_ = false;

	currentCharacterIndex = 0;
}

void PlayingState::onEnter()
{
	int count = 0;
	auto position = std::find_if(game_.characterCards().begin(), game_.characterCards().end(), [&](std::unique_ptr<CharacterCard>& card) 
	{
		if (card->owner() != CharacterCard::Deck && card->owner() != CharacterCard::None) {
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
		if (game_.characterCards()[currentCharacterIndex]->owner() == CharacterCard::Player1) {
			game_.setCurrentClient(Game::Players::Player1);
		}
		else 
		{
			game_.setCurrentClient(Game::Players::Player2);
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
	game_.characterCards()[currentCharacterIndex]->owner(CharacterCard::None);
	onEnter();
	if (currentCharacterIndex == -1) 
	{
		game_.setState(Game::DealCards);
	}
}


PlayingState::~PlayingState()
{
}

bool PlayingState::initState(ClientInfo & clientInfo, std::string cmd)
{
	return true;
}

bool PlayingState::chooseState(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = stoi(cmd);
		if (cmdi == -1) {
			return true;
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
	std::vector<int> unused;
	int count = 0;
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](std::unique_ptr<CharacterCard>& card)
	{
		if (card->owner() == CharacterCard::Deck) {
			unused.push_back(count);
		}
		count++;
	});
	return true;
}

bool PlayingState::useCharacterCard(ClientInfo & clientInfo, std::string cmd)
{
	return true;
}

void PlayingState::printChooseStateOptions()
{
	if (!initState_) {
		game_.currentClient().get_socket() << "1: pak 2 munten of pak 1 en leg 1 gebouwkaart weg\r\n";
	}
	if (!placedBuildingCard_) {
		game_.currentClient().get_socket() << "2: plaats gebouw\r\n";
	}
	if (!usedCharacterCard_) {
		game_.currentClient().get_socket() << "3: gebuik karakterkaart\r\n";
	}
	game_.currentClient().get_socket() << "-1: stop beurt\r\n";
}
