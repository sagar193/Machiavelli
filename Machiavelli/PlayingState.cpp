#include "pch.h"
#include "PlayingState.h"


PlayingState::PlayingState(Game& game) : State(game)
{
}

void PlayingState::onEnter()
{
}

void PlayingState::act(ClientInfo& clientInfo,std::string cmd)
{
}

void PlayingState::onLeave()
{
}


PlayingState::~PlayingState()
{
}
