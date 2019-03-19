#include "pch.h"
#include "PlayingState.h"


PlayingState::PlayingState(Game& game) : State(game)
{
}

void PlayingState::onEnter()
{
	game_.currentClient().get_socket() << "Kill frodo" << "\r\n";
}

bool PlayingState::act(ClientInfo& clientInfo,std::string cmd)
{
	return true;
	//throw "not implemented";
}

void PlayingState::onLeave()
{
}


PlayingState::~PlayingState()
{
}
