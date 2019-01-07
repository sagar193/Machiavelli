#include "pch.h"
#include "DealCardState.h"


DealCardState::DealCardState()
{
}


DealCardState::~DealCardState()
{
}

void DealCardState::enter(Game & game)
{
	game.shuffleCharacterCards();
	game.getCurrentPlayer().socket() << "Ieder moet nu een Characterkaart kiezen\n";
}

bool DealCardState::act(Game & game)
{
	return false;
}

void DealCardState::set_current_player(Game & game)
{
}
