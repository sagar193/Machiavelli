#include "pch.h"
#include "DealCardState.h"
#include "ClientInfo.h"
#include "Bouwmeester.h"


DealCardState::DealCardState(Game& game) : State(game)
{
}

void DealCardState::onEnter()
{
}

void DealCardState::act(ClientInfo& clientInfo,std::string cmd)
{
	printCharacterCards(clientInfo);
	return;
}

void DealCardState::onLeave()
{
}

void DealCardState::printCharacterCards(ClientInfo & clientInfo)
{
	std::map<int, int> map;
	const auto l = [&map](int i, int j) {map[i] = j;};

	int count = 0;
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](std::unique_ptr<CharacterCard> card)
	{
		if (card->owner() == CharacterCard::Owner::Deck)
		{
			clientInfo.get_socket() << count << ": " << card->name() <<'\n';
		}
		count++;
	});
}


DealCardState::~DealCardState()
= default;
