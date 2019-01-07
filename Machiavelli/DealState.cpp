#include "pch.h"
#include "DealState.h"


DealState::DealState()
{
}


DealState::~DealState()
{
}

void DealState::onEnter(Player & player, const Game & game) 
{
	player.socket() << "Kies een van de volgende kaarten:";
	const auto map = game.mapDeckCards();
	game.printDeckMap(player,map);
}
