#include "pch.h"
#include "Game.h"
#include "CharacterCard.h"
#include "Bouwmeester.h"
#include "Condottiere.h"
#include "Dief.h"
#include "Koning.h"
#include "Koopman.h"
#include "Magier.h"
#include "Moordenaar.h"
#include "Prediker.h"

#include <algorithm>
#include <numeric>

void Game::startGame()
{
	if (!running_ && player1_ != nullptr && player2_ != nullptr)
	{
		running_ = true;
		player1_->socket() << "\r\nWelcome to Machiavelli the most convoluted game that \"nobunny\" likes to play.\r\nYou are Player1\r\n";
		player2_->socket() << "\r\nWelcome to Machiavelli the most convoluted game that \"nobunny\" likes to play.\r\nYou are Player2\r\n";
		if(player1_->age()>=player2_->age())
		{
			player1_->socket() << "Based on your age you are king. Enjoy it.\r\nIt is you turn\r\n";
			player1_->makeKing();
			current_player_ = 1;
			current_state_ = PICKINGCHARACTERCARDS;
			player2_->socket() << "Based on your age Player1 is king. You loser.\r\nIt is Player1's turn\r\n";
		}else
		{
			player1_->socket() << "Based on your age Player2 is king. You loser.\r\nIt is Player2's turn\r\n";
			player2_->socket() << "Based on your age you are king. Enjoy it.\r\nIt is your turn\r\n";
			player2_->makeKing();
			current_player_ = 2;
			current_state_ = PICKINGCHARACTERCARDS;
		}
		//enterDealState();
		//playGame();
		getCurrentPlayer().socket() << "Kies een kaart die je wilt omdraaien door zijn nummer te enteren\r\n";
	}
}

void Game::playGame()
{
	dealCards();
}

void Game::dealCards()
{
	while (getUnownedCharacterCards() >= 0) {
		for (int i = 0;i < 2;i++) {
			bool pickedCard = false;
			bool placedCard = false;
			while (!pickedCard)
			{

				player_index_[current_player_]->socket() << "Kies een characterkaart door zijn nummer in te voeren\r\n\r\n";
				auto map = mapDeckCards();
				for (const auto el : map)
				{
					player_index_[current_player_]->socket() << '[' << el.first << ']' << " : " << character_cards_[el.second]->name() << "\r\n";
				}

				std::string cmd;
				auto done = false;
				while (!done) {
					done = player_index_[current_player_]->socket().readline([&cmd](std::string input) {cmd = input;});

				}

				try
				{
					const auto index = std::stoi(cmd);
					if (index >= 0 && index < map.size() - 1)
					{
						if (current_player_ == 1) {
							character_cards_[index]->owner(PLAYER1);
						}
						else
						{
							character_cards_[index]->owner(PLAYER2);
						}
						pickedCard = true;
					}
					else
					{
						player_index_[current_player_]->socket() << "Kies een kaart uit de lijst!";
					}
				}
				catch (...)
				{
					player_index_[current_player_]->socket() << "Kies een kaart uit de lijst!";
				}
			}

			while (!placedCard)
			{
				//todo::lock
				player_index_[current_player_]->socket() << "Plaats een van de kaarten in de afgelegde stapel door zij nummer in te voeren\r\n\r\n";
				auto map = mapDeckCards();
				for (auto el : map)
				{
					auto& kk = character_cards_[el.second];
					player_index_[current_player_]->socket() << '[' << el.first << ']' << " : " << character_cards_[el.second]->name() << "\r\n";
				}

				std::string cmd;
				auto done = false;
				while (!done) {
					done = player_index_[current_player_]->socket().readline([&cmd](std::string input) {cmd = input;});

				}

				try
				{
					const auto index = std::stoi(cmd);
					if (index >= 0 && index < map.size() - 1)
					{
						character_cards_[index]->owner(GRAVE);
						placedCard = true;
					}
					else
					{
						player_index_[current_player_]->socket() << "Kies een kaart uit de lijst!";
					}
				}
				catch (...)
				{
					player_index_[current_player_]->socket() << "Kies een kaart uit de lijst!";
				}
			}
			switchPlayer();
		}
	}
}

void Game::dealCards(Player & const player, std::map<int, int> deckMap, std::string cmd)
{
	try
	{
		auto index = std::stoi(cmd);
		if(index>=0 && index < deckMap.size())
		{
			character_cards_[index]->owner(playerOwnerMap[&player]);
			switchPlayer();
		}
		else
		{
			player.socket() << "kies een kaart uit de lijst";
		}
	}
	catch(...)
	{
		player.socket() << "kies een kaart uit de lijst";
	}
	
}

void Game::handleCommand(Player & const player)
{
	if (current_state_ == WAITINGPLAYERS) {
		player.socket() << "Please wait til another player arrives";
	}
	else {
		std::string cmd;
		bool received_input{ false };
		if (player_index_[current_player_] != &player)
		{
			player.socket() << "Wait your turn.\r\n";
		}
		else
		{
			if (current_state_ == DEALINGCARDS) 
			{
			}
		}
	}
}

void Game::handleCommand(Player & const player, std::string cmd)
{
	if (current_state_ == WAITINGPLAYERS) {
		player.socket() << "Please wait til another player arrives";
	}
	else {
		bool received_input{ false };
		if (player_index_[current_player_] != &player)
		{
			player.socket() << "Wait your turn.\r\n";
		}
		else
		{
			if (current_state_ == PICKINGCHARACTERCARDS)
			{
				const auto map = mapDeckCards();
				if (pickCharacterCard(player, map, cmd)) {
					current_state_ = TURNINGCHARACTERCARDS;
					player.socket() << "Kies een kaart die je wilt omdraaien door zijn nummer te enteren\r\n";
				}
				printChooseAbleCharacters(player);
			}
			else if(current_state_ == TURNINGCHARACTERCARDS)
			{
				const auto map = mapDeckCards();
				if(turnCharacterCard(player, map, cmd))
				{
					if (getAmountCharacterCardsOwned(GRAVE) < 4)
					{
						switchPlayer();
						current_state_ = PICKINGCHARACTERCARDS;
						getOtherPlayer().socket() << "Kies een characterkaart door zijn nummer te enteren\r\n";
						printChooseAbleCharacters(getCurrentPlayer());
					}
					else
					{
						int k = 0;
					}
				}
				else 
				{
					printChooseAbleCharacters(getCurrentPlayer());
				}
			} 
		}
	}
}

Game::Game()
{
	player1_ = nullptr;
	player2_ = nullptr;
	playerSwitched = 0;

	current_player_ = 0;
	
	running_ = false;
	current_state_ = WAITINGPLAYERS;
	initGame();
}

void Game::setPlayer(Player& const player)
{
	if (player1_ == nullptr) {
		player1_ = &player;

		player_index_[1] = &player;

	}
	else if (player2_ == nullptr) {
		player2_ = &player;

		player_index_[2] = &player;

	}
	else {
		player.socket() << "fuck off, game is full!!!!!!!!!!";
		throw std::exception("Game already full");
	}
}

Game::~Game()
{
}

int Game::getUnownedCharacterCards() const
{
	return std::accumulate(character_cards_.begin(), character_cards_.end(), 0, [](int current_sum,const std::unique_ptr<CharacterCard>& card)
	{
		if (card->owner() == Game::cardOwners::DECK)
		{
			return current_sum + 1;
		}
		return current_sum;
	});
	//return 0;
}

void Game::printUnownedCharacterCards() const
{
	//std::for_each(character_cards_.begin(), character_cards_.end(),
	//	[](const std::unique_ptr<CharacterCard>& card)
	//{
	//	
	//});
}

void Game::printDeckMap(Player & player, std::map<int, int> map) const
{
	for (const auto el : map)
	{
		player.socket() << '[' << el.first << ']' << " : " << character_cards_[el.second]->name() << "\r\n";
	}
}

int Game::getAmountCharacterCardsOwned(cardOwners owner) const
{
	return std::accumulate(character_cards_.begin(),character_cards_.end(),
		0,[&owner](int total,const std::unique_ptr<CharacterCard>& card)
	{
		if(card->owner()==owner)
		{
			return total + 1;
		}
	});
}

int Game::getAmountCharacterCardsOwnedByCurrentPlayer() const
{
	if(current_player_ == 1)
	{
		return getAmountCharacterCardsOwned(PLAYER1);
	}
	return getAmountCharacterCardsOwned(PLAYER2);
}

std::map<int, int> Game::mapDeckCards() const
{
	std::map<int, int> map;
	const auto l = [&map](int i, int j) {map[i] = j;};
	
	int current_count_map = 0;
	int current_count_list = 0;
	std::for_each(character_cards_.begin(), character_cards_.end(),[&](const std::unique_ptr<CharacterCard>& card)
	{
		if(card->owner() == DECK)
		{
			map[current_count_map] = current_count_list;
			current_count_map++;
		}
		current_count_list++;
	});
	return map;
}

bool Game::pickCharacterCard(Player & const player, std::map<int, int> deckMap, std::string cmd)
{
	try
	{
		auto index = std::stoi(cmd);
		if (index >= 0 && index < deckMap.size())
		{
			character_cards_[deckMap[index]]->owner(playerOwnerMap[&player]);
			return true;
		}
		player.socket() << "kies een kaart uit de lijst\r\n";
		return false;
		
	}
	catch (...)
	{
		player.socket() << "kies een kaart uit de lijst\r\n";
		return false;
	}

}

bool Game::turnCharacterCard(Player & const player, std::map<int, int> deckMap, std::string cmd)
{
	try
	{
		auto index = std::stoi(cmd);
		if (index >= 0 && index < deckMap.size())
		{
			character_cards_[deckMap[index]]->owner(GRAVE);
			return true;
		}
		player.socket() << "kies een kaart uit de lijst\n";
		return false;
	}
	catch (...)
	{
		player.socket() << "kies een kaart uit de lijst\n";
		return false;
	}

}



Player & Game::getCurrentPlayer()
{
	return *player_index_[current_player_];
}

Player & Game::getOtherPlayer()
{
	if(current_player_ == 1)
	{
		return *player2_;
	}
	return *player1_;
}

bool Game::isCurrentPlayer(const Player & player)
{
	bool isCurrent = false;
	try
	{
		isCurrent = player_index_[current_player_] == &player;
		return isCurrent;
	} catch(...)
	{
		return false;
	}
}

void Game::printChooseAbleCharacters(Player & player) const
{
	printDeckMap(player, mapDeckCards());
}

void Game::enterDealState()
{
	if(player_index_[current_player_] == player1_)
	{
		player1_->socket() << "please choose on of the following cards\r\n";
		printChooseAbleCharacters(*player1_);
	} 
	else
	{
		player2_->socket() << "please choose on of the following cards\r\n";
		printChooseAbleCharacters(*player2_);
	}
}

void Game::printEnterTurnCardState(Player & player) const
{
	player.socket()<<"Kies een kaart die je wilt omdraaien door zijn nummer te enteren\r\n"
}

void Game::switchPlayer()
{
	if(current_player_ == 1)
	{
		current_player_ = 2;
	}
	else
	{
		current_player_ = 1;
	}
	playerSwitched++;
}

void Game::initGame()
{
	//auto ptr = std::make_unique<Bouwmeester>();
	character_cards_.push_back(std::make_unique<Bouwmeester>());
	character_cards_.push_back(std::make_unique<Condottiere>());
	character_cards_.push_back(std::make_unique<Dief>());
	character_cards_.push_back(std::make_unique<Koning>());
	character_cards_.push_back(std::make_unique<Koopman>());
	character_cards_.push_back(std::make_unique<Magier>());
	character_cards_.push_back(std::make_unique<Moordenaar>());
	character_cards_.push_back(std::make_unique<Prediker>());

	playerOwnerMap[player1_] = PLAYER1;
	ownerPlayerMap[PLAYER1] = player1_;
	playerOwnerMap[player2_] = PLAYER2;
	ownerPlayerMap[PLAYER2] = player2_;

}
