#include "pch.h"
#include "DealCardState.h"


DealCardState::DealCardState()
{
	current_activity_ = picking_cards;
}

DealCardState::~DealCardState()
= default;

void DealCardState::enter(Game & game)
{
	game.players().send_message_to_all_players("Iedereen moet nu 2 characterkaarten kiezen en\r\n");
	set_current_player(game);
	game.shuffleCharacterCards();
	current_activity_ = picking_cards;
	game.players().get_current_player_value().socket() << "Kies een characterkaart ide je dadelijk wilt gebruiken\r\n";
	print_dialogue(game);
}

bool DealCardState::act(std::string cmd, Game & game)
{
	auto map = game.mapCharacterCards(DECK);
	if(current_activity_ == picking_cards)
	{
		try
		{
			const auto index = map.at(std::stoi(cmd));
			if(game.players().get_current_player_code() == Players::PLAYER1)
			{
				game.ownCharacterCard(index, PLAYER1);
			}
			else if (game.players().get_current_player_code() == Players::PLAYER2)
			{
				game.ownCharacterCard(index, PLAYER2);
			}
			current_activity_ = putting_cards_away;
			game.players().get_current_player_value().socket() << "Leg 1 kaart weg\r\n";
			print_dialogue(game);
		}
		catch(...)
		{
			game.players().get_current_player_value().socket() << "Kies een geldige kaart\r\n";
		}
	}
	else if(current_activity_ == putting_cards_away)
	{
		try
		{
			const auto index = map.at(std::stoi(cmd));
			game.ownCharacterCard(index, GRAVE);
			if (game.getAmountCharacterCardsOwned(GRAVE) < 4) {
				current_activity_ = picking_cards;
				game.players().switch_current_player();
				game.players().get_current_player_value().socket() << "Kies een characterkaart die je dadelijk wilt gebruiken\r\n";
				print_dialogue(game);
			} else
			{
				game.set_current_state(Game::PLAYERTURN);
			}
		}
		catch (...)
		{
			game.players().get_current_player_value().socket() << "Kies een geldige kaart\r\n";
		}
	}
	return false;
}

void DealCardState::set_current_player(Game & game) const
{
	if(game.players().get_player1().king())
	{
		game.players().set_current_player(Players::PLAYER1);
	}
	else if (game.players().get_player2().king())
	{
		game.players().set_current_player(Players::PLAYER2);
	} else
	{
		if(game.players().get_player1().age()>=game.players().get_player2().age())
		{
			game.players().set_current_player(Players::PLAYER1);
		}
		else
		{
			game.players().set_current_player(Players::PLAYER2);
		}
		game.players().get_current_player_value().socket() << "Omdat jij de oudste bent, ben jij nu koning\r\n";
		game.players().get_other_player_value().socket() << "Omdat jij de jongste bent, ben jij als tweede aan de beurt\r\n";
	}
}

void DealCardState::print_dialogue(Game & game) const
{
	const auto map = game.mapCharacterCards(DECK);
	game.printDeckMap(game.players().get_current_player_value(), map);
}

bool DealCardState::pick_card(Game & game)
{
	//const auto
	return false;
}
