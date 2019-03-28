#include "pch.h"
#include "CharacterCard.h"
#include "ClientInfo.h"
#include "Game.h"

CharacterCard::CharacterCard(Game& game) : State(game)
{
	owner_ = Deck;
	mugged_ = false;
}

void CharacterCard::removeBuildingCard(int index)
{
	if (game_.buildingCards()[index].active() && game_.buildingCards()[index].owner() == game_.currentClient().get_player().ownertag()) {
		game_.buildingCards()[index].owner(Owner::None);
	}
	else {
		game_.sendToCurrentPlayer("deze kaart kan niet verwijderd worden");
	}
}
