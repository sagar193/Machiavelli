#include "pch.h"
#include "PlayingState.h"


PlayingState::PlayingState(Game& game) : State(game)
{
}

void PlayingState::onEnter()
{
}

bool PlayingState::act(ClientInfo& clientInfo,std::string cmd)
{
	throw "not implemented";
}

void PlayingState::onLeave()
{
}


PlayingState::~PlayingState()
{
}
