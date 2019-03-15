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
#include "State.h"
#include "DealCardState.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include "BuildingCard.h"
#include "PlayerTurnState.h"
#include <time.h>

std::ostream & operator<<(std::ostream & os, BuildingCard& card)
{
	os << "name: " << card.name() << "  color: " << card.color() << "  cost: " << card.cost();
	return os;
}

/*
std::istream & operator>>(std::istream & os, BuildingCard& card)
{
	/*
	std::string name;
	std::string colorstring;
	BuildingCard::colorTypes color;
	int cost;

	if(os >> name >> colorstring >> cost)
	{
		if (colorstring._Equal("geel"))
		{
			color = BuildingCard::colorTypes::GEEL;
		}
		else if (colorstring._Equal("blauw"))
		{
			color = BuildingCard::colorTypes::BLAUW;
		}
		else if (colorstring._Equal("groen"))
		{
			color = BuildingCard::colorTypes::GROEN;
		}
		else if (colorstring._Equal("rood"))
		{
			color = BuildingCard::colorTypes::ROOD;
		}
	}
	return os;
}*/

void Game::startGame()
{
	if (!running_ && players_->get_count_players()==2)
	{
		running_ = true;
		set_current_state(DEALINGCARDS);
	}
}


void Game::handleCommand(Player & const player, std::string cmd)
{
	if (current_state_ == WAITINGPLAYERS) {
		player.socket() << "Please wait til another player arrives";
	}
	else {
		bool received_input{ false };
		if (!players_->is_current_player(player))
		{
			player.socket() << "Wait your turn.\r\n";
		}
		else
		{
			//if (current_state_ == DEALINGCARDS) {
				states_[current_state_]->act(cmd, *this);
				/*if (current_activity_ == PICKINGCHARACTERCARDS)
				{
					const auto map = mapDeckCards();
					if (pickCharacterCard(player, map, cmd)) {
						current_activity_ = TURNINGCHARACTERCARDS;
						player.socket() << "Kies een kaart die je wilt omdraaien door zijn nummer te enteren\r\n";
					}
					printChooseAbleCharacters(player);
				}
				else if (current_activity_ == TURNINGCHARACTERCARDS)
				{
					const auto map = mapDeckCards();
					if (turnCharacterCard(player, map, cmd))
					{
						if (getAmountCharacterCardsOwned(GRAVE) < 4)
						{
							switchPlayer();
							current_activity_ = PICKINGCHARACTERCARDS;
							getCurrentPlayer().socket() << "Kies een characterkaart door zijn nummer te enteren\r\n";
							printChooseAbleCharacters(getCurrentPlayer());
						}
						else
						{
							current_state_ = PLAYERTURN;
							setCurrentPlayer();
							printPlayerTurnStateOptions(getCurrentPlayer());
						}
					}
					else
					{
						printChooseAbleCharacters(getCurrentPlayer());
					}
				}*/
			//} 
			//else if(current_state_ == PLAYERTURN)
			//{
				
			//}
		}
	}
}


int Game::getAmountCharacterCardsOwned(CardOwners owner) const
{
	return std::accumulate(character_cards_.begin(),character_cards_.end(),
		0,[&owner](int total,const std::unique_ptr<CharacterCard>& card)
	{
		if(card->owner()==owner)
		{
			return total + 1;
		}
		return total;
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

std::map<int, int> Game::mapCharacterCards(CardOwners owner) const
{
	std::map<int, int> map;
	const auto l = [&map](int i, int j) {map[i] = j;};
	
	int current_count_map = 0;
	int current_count_list = 0;
	std::for_each(character_cards_.begin(), character_cards_.end(),[&](const std::unique_ptr<CharacterCard>& card)
	{
		if(card->owner() == owner)
		{
			map[current_count_map] = current_count_list;
			current_count_map++;
		}
		current_count_list++;
	});
	return map;
}

std::map<int, int> Game::mapBuildingCards(CardOwners owner) const
{
	std::map<int, int> map;

	int current_count_map = 0;
	int current_count_list = 0;
	std::for_each(building_cards_.begin(), building_cards_.end(), [&](const std::unique_ptr<BuildingCard>& card)
	{
		if (card->owner() == owner)
		{
			map[current_count_map] = current_count_list;
			current_count_map++;
		}
		current_count_list++;
	});
	return map;
}


void Game::printCharacterMap(Player & player, std::map<int, int> map) const
{
	for (const auto el : map)
	{
		player.socket() << '[' << el.first << ']' << " : " << character_cards_[el.second]->name() << "\r\n";
	}
}
void Game::printBuildingMap(Player & player, std::map<int, int> map)
{
	for (const auto el : map)
	{
		std::stringstream ss;
		ss << *get_buildingcard_at(el.second);
		player.socket() << '[' << el.first << ']' << " : " << ss.str() << "\r\n";
	}
}

void Game::printChooseAbleCharacters(Player & player) const
{
	printCharacterMap(player, mapCharacterCards(DECK));
}

void Game::printChooseAbleBuildings(Player & player)
{
	printBuildingMap(player, mapBuildingCards(DECK));
}

void Game::shuffleCharacterCards()
{
	std::for_each(character_cards_.begin(), character_cards_.end(),
		[](std::unique_ptr<CharacterCard>& card) {card->reset();});
}

void Game::shuffleBuildingCards()
{
	//const auto half = std::floor(building_cards_.size() / 2);
	//const auto half = 0;

	std::default_random_engine generator;
	generator.seed(time(0));
	std::uniform_int_distribution<int> distribution(0, building_cards_.size()-1);
	
	for(auto i = 0;i<building_card_map_.size();i++)
	{
		const auto f = distribution(generator);
		const auto s = distribution(generator);
		const auto buffer = building_card_map_[s];
		building_card_map_[s] = building_card_map_[f];
		building_card_map_[f] = buffer;
	}
}

void Game::ownCharacterCard(int cardIndex, CardOwners owner)
{
	character_cards_[cardIndex]->owner(owner);
}

void Game::ownBuildingCard(int cardIndex, CardOwners owner)
{
	building_cards_[cardIndex]->owner(owner);
}

void Game::set_current_state(state newState)
{
	current_state_ = newState;
	states_[current_state_]->enter(*this);
}
int Game::get_first_unused_owned_character_card() const
{
	int count = 0;
	const auto currentCharacter = std::find_if(character_cards_.begin(), character_cards_.end(),
		[&count](const std::unique_ptr<CharacterCard>& card)
	{
		if (((card->owner() == PLAYER1) || (card->owner() == PLAYER2))&& !card->used())
		{
			return true;
		}
		count++;
		return false;
	});

	if (currentCharacter == character_cards_.end())
	{
		return -1;
	}
	return count;
}
std::unique_ptr<CharacterCard>& Game::get_card_at(int index)
{
	return character_cards_.at(index);
}


std::unique_ptr<BuildingCard>& Game::get_buildingcard_at(int index)
{
	return building_cards_.at(building_card_map_[index]);
}

///<summary>
///inits
///</summary>
Game::Game()
{
	players_ = std::make_unique<Players>();
	player1_ = nullptr;
	player2_ = nullptr;
	playerSwitched = 0;

	current_player_ = 0;

	running_ = false;
	current_state_ = WAITINGPLAYERS;
	currentCharacterIndex = 0;
	initGame();
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

	states_[DEALINGCARDS] = std::make_unique<DealCardState>();
	states_[PLAYERTURN] = std::make_unique<PlayerTurnState>();
	load_building_cards();

	for(int i = 0;i<building_cards_.size();i++)
	{
		building_card_map_[i] = i;
	}


}
void Game::load_building_cards()
{
	std::ifstream is("..\\Files\\Bouwkaarten.csv", std::ifstream::binary);
	if (is) {

		std::vector<std::unique_ptr<BuildingCard>> buffer;
		std::string line;
		//try {
		while (std::getline(is, line)) {
			std::istringstream ss(line);

			std::string name;
			std::string costString;
			std::string colorString;
			std::getline(ss, name, ';');
			std::getline(ss, costString, ';');
			std::getline(ss, colorString, ';');

			auto color = BuildingCard::color(colorString);
			if (color != BuildingCard::NONE) {
				//todo try cost
				buffer.push_back(std::make_unique<BuildingCard>(name, std::stoi(costString), color));
			}
			else
			{
				std::cout << "color :" << colorString << " does not exist \n";
			}
			//else
			//{
			//	throw std::exception("color does not exist");
			//}
		}
		this->building_cards_ = std::move(buffer);
		//} 
		//catch (std::exception &e)
		//{
		//	int k = 0;
		//}
	}
	else
	{
		std::cout << "file could not be loaded" << std::endl;
	}
	is.close();
}
void Game::setPlayer(Player& const player)
{
	players_->set_player(player);
	/*
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
	}*/
}
Game::~Game()
{
}

