#include "pch.h"
#include "PlayerTurnState.h"

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
}

bool PlayerTurnState::act(std::string cmd, Game & game)
{
	if(current_activity_ == choosing)
	{
		act_choosing(cmd, game);
	}
	else if(current_activity_ == drawing)
	{
		act_drawing(cmd, game);
	}
	else if(current_activity_ == picking_cards)
	{
		act_picking_cards(cmd, game);
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
			act_looking(cmd, game);
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
			game.get_card_at(current_character_)->use();
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

void PlayerTurnState::print_act_drawing(Game & game)
{
	game.players().get_current_player_value().socket() << "kies een van de volgende opties:\r\n";
	game.players().get_current_player_value().socket() << "[0] : terug\r\n";
	game.players().get_current_player_value().socket() << "[1] : pak 1 gebouwkaart en leg er 1 af\r\n";
	game.players().get_current_player_value().socket() << "[2] : pak 2 goudstukken\r\n";
}

void PlayerTurnState::act_drawing(std::string cmd, Game & game)
{
	try
	{
		const auto option = std::stoi(cmd);
		switch (option)
		{
		case 1:
			current_activity_ = picking_cards;
			game.shuffleBuildingCards();
			break;
		case 2:
			game.players().get_current_player_value().ad_gold(2);
			game.players().get_current_player_value().socket() << "Twee goedstukken zijn toegevoegd aan je buidel\r\n";
			has_drawn = true;
			break;
		case 0:
			current_activity_ = choosing;
			game.get_card_at(current_character_)->use();
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

void PlayerTurnState::print_act_picking_cards(Game & game)
{
	game.players().get_current_player_value().socket() << "Voeg een van de volgende kaarten toe aan je hand\r\n";
}

void PlayerTurnState::act_picking_cards(std::string cmd, Game & game)
{
}

void PlayerTurnState::act_looking(std::string cmd, Game & game)
{
	game.players().get_current_player_value().socket() << "Zie hier de gebouwen van je tegenspeler\r\n";
	if (game.players().get_current_player_code() == Players::PLAYER1) {
		game.printBuildingMap(game.players().get_current_player_value(),game.mapBuildingCards(PLAYER2));
	} else
	{
		game.printBuildingMap(game.players().get_current_player_value(), game.mapBuildingCards(PLAYER1));
	}
	print_start_dialogue(game);
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
		}
		else {
			game.players().set_current_player(Players::PLAYER2);
		}
		print_start_dialogue(game);
		print_act_choosing(game);
	}
}

void PlayerTurnState::print_start_dialogue(Game & game)
{
	//game.players().get_current_player_value()
	
	game.players().get_current_player_value().socket() << "Het is jouw buurt\r\n";
	game.players().get_current_player_value().socket() << "Je speelt nu als " << game.get_card_at(current_character_)->name() << "\r\n\r\n";
	print_stats(game);
}

void PlayerTurnState::print_stats(Game & game)
{
	const auto owner = game.players().get_player_owner_code(game.players().get_current_player_code());
	game.players().get_current_player_value().print_line();
	game.players().get_current_player_value().socket() << "Je bezit de volgende characterkaarten:\r\n";
	game.printCharacterMap(game.players().get_current_player_value(), game.mapCharacterCards(owner));
	game.players().get_current_player_value().print_line();
	game.players().get_current_player_value().socket() << "Je bezit de volgende gebouwkaarten:\r\n";
	game.printBuildingMap(game.players().get_current_player_value(), game.mapBuildingCards(owner));;	
	game.players().get_current_player_value().print_line();
}
