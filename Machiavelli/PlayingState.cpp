#include "pch.h"
#include "PlayingState.h"
#include <algorithm>


PlayingState::PlayingState(Game& game) : State(game)
{
	currentState_ = States::InitState;
	placedBuildingCard_ = false;
	usedCharacterCard_ = false;
}

void PlayingState::onEnter()
{
	currentState_ = States::InitState;
	placedBuildingCard_ = false;
	usedCharacterCard_ = false;
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
	std::vector<int> unused;
	int count = 0;
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](std::unique_ptr<CharacterCard>& card)
	{
		if (card->owner() == CharacterCard::Deck) {
			unused.push_back(count);
		}
		count++;
	});
	return false;
}

bool PlayingState::useCharacterCard(ClientInfo & clientInfo, std::string cmd)
{
	return false;
}
