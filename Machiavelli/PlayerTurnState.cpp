#include "pch.h"
#include "PlayerTurnState.h"
#include <algorithm>


PlayerTurnState::PlayerTurnState()
{
	current_activity_ = choosing;
	current_character_ = 0;
	character_stolen_ = -1;
	has_build = false;
	has_drawn = false;
	has_used_card = false;
}

void PlayerTurnState::enter(Game & game)
{
	set_current_player(game);
	current_activity_ = choosing;
	print_start_dialogue(game);
	print_act_choosing(game);
}

bool PlayerTurnState::act(std::string cmd, Game & game)
{
	if(current_activity_ == choosing)
	{
		act_choosing(cmd, game);
	}
	return false;
}

PlayerTurnState::~PlayerTurnState()
{
}

void PlayerTurnState::print_act_choosing(Game & game)
{
	game.players().get_current_player_value().socket() << "Kies een von de onderstaande opties\r\n";
	game.players().get_current_player_value().socket() << "[0] : Beindig de beurt\r\n";
	game.players().get_current_player_value().socket() << "[1] : Kijk bij de tegenspeler\r\n";
	game.players().get_current_player_value().socket() << "[2] : Pak 2 goudstukken of trek 1 gebouwkaarten en leg 1 weg\r\n";
	game.players().get_current_player_value().socket() << "[3] : Gebruik de karakterkaart\r\n";
}

void PlayerTurnState::act_choosing(std::string cmd, Game & game)
{
	try
	{
		const auto option = std::stoi(cmd);
		switch (option)
		{
		case 1:
			current_activity_ = looking;
			break;
		case 2:
			if (!has_drawn) {
				current_activity_ = drawing;
			} else
			{
				game.players().get_current_player_value().socket() << "Deze optie al verbruikt\r\n";
			}
			break;
		case 3:
			if (!has_used_card) {
				current_activity_ = using_character_card;
			}
			else
			{
				game.players().get_current_player_value().socket() << "Deze optie al verbruikt\r\n";
			}
			break;
		case 0:
			set_current_player(game);
			break;
		default:
			game.players().get_current_player_value().socket() << "Kies een optie uit de lijst\r\n";
			print_start_dialogue(game);
			print_act_choosing(game);
			break;
		}
	}
	catch (...)
	{
		game.players().get_other_player_value().socket() << "Kies een optie uit de lijst\r\n";
	}
}

void PlayerTurnState::act_looking(std::string cmd, Game & game)
{
	//if(game.players().get_current_player_code() == Players::PLAYER1)
	//{
	//	game.printDeckMap(game.players().get_current_player_value(),game.mapDeckCards(Game::PLAYER2));
	//} else
	//{
	//	game.printDeckMap(game.players().get_current_player_value(), game.mapDeckCards(Game::PLAYER1));
	//}
}

void PlayerTurnState::set_current_player(Game & game)
{
	current_character_ = game.get_first_unused_owned_character_card();
	if(current_character_ == -1)
	{
		game.set_current_state(Game::DEALINGCARDS);
	} else
	{
		auto& card = game.get_card_at(current_character_);
		if(card->owner() == PLAYER1)
		{
			game.players().set_current_player(Players::PLAYER1);
		} else
		{
			game.players().set_current_player(Players::PLAYER2);
		}
	}
}

void PlayerTurnState::print_start_dialogue(Game & game) const
{
	game.players().get_current_player_value().socket() << "Het is jouw buurt\r\n";
	game.players().get_current_player_value().socket() << "Je speelt nu als " << game.get_card_at(current_character_)->name() << "\r\n";
}
