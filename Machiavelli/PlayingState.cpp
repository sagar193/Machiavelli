#include "pch.h"
#include "PlayingState.h"


PlayingState::PlayingState(Game& game) : State(game)
{
	currentState_ = States::ChooseState;
}

void PlayingState::onEnter()
{
	currentState_ = States::ChooseState;
	//game_.currentClient().get_socket() << "Kill frodo" << "\r\n";
}

bool PlayingState::act(ClientInfo& clientInfo,std::string cmd)
{
	//if (cmd == "quit") {
	//	return true;
	//}
	switch (currentState_)
	{
	case States::ChooseState:
		chooseState(clientInfo, cmd);
		break;
	case States::PlaceBuildingCard:
		placeBuildingCard(clientInfo, cmd);
		break;
	case States::UseCharacterCard:
		useCharacterCard(clientInfo, cmd);
		break;
	default:
		break;
	}
	return true;
}

void PlayingState::onLeave()
{
}


PlayingState::~PlayingState()
{
}

void PlayingState::chooseState(ClientInfo & clientInfo, std::string cmd)
{
}

void PlayingState::placeBuildingCard(ClientInfo & clientInfo, std::string cmd)
{
}

void PlayingState::useCharacterCard(ClientInfo & clientInfo, std::string cmd)
{
}
