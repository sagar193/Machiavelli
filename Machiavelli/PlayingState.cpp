#include "pch.h"
#include "PlayingState.h"
#include "random.h"
#include <algorithm>
#include "ClientInfo.h"
#include "Game.h"

PlayingState::PlayingState(Game& game) : State(game)
{
	currentState_ = States::InitState;
	prevState_ = currentState_;
	//endPlayer = Game::Players::None;
	placedBuildingCard_ = false;
	usedCharacterCard_ = false;
	drawnBuildingCard1 = nullptr;
	drawnBuildingCard2 = nullptr;
	initState_ = false;
	lastround = false;
	currentCharacterIndex = 0;
}

void PlayingState::onEnter()
{
	int count = 0;
	auto position = std::find_if(game_.characterCards().begin(), game_.characterCards().end(), [&](std::unique_ptr<CharacterCard>& card) 
	{
		if (card->owner() != Owner::Deck && card->owner() != Owner::None && card->owner() != Owner::Killed) {
			return true;
		}
		count++;
		return false;
	});

	if (position != game_.characterCards().end()) {
		currentCharacterIndex = count;

		placedBuildingCard_ = false;
		usedCharacterCard_ = false;
		initState_ = false;
		currentState_ = States::InitState;
		prevState_ = currentState_;

		//todo: set current player lelijk
		//todo: vertel aan de andere speler dat die moet wachten
		if (game_.characterCards()[currentCharacterIndex]->owner() == Owner::Player1) {
			game_.setCurrentClient(Game::Players::Player1);
			game_.sendToAllPlayers("de " + game_.characterCards()[currentCharacterIndex]->name() + " (speler1) is aan de beurt\r\n");
		}
		else 
		{
			game_.setCurrentClient(Game::Players::Player2);
			game_.sendToAllPlayers("de " + game_.characterCards()[currentCharacterIndex]->name() + " (speler2) is aan de beurt\r\n");
		}
		
		if (game_.characterCards()[currentCharacterIndex]->mugged() == true)
		{
			game_.sendToAllPlayers("de " + game_.characterCards()[currentCharacterIndex]->name() + " was bestolen dus geeft zijn geld af aan de dief");
			auto& player = game_.getPlayer(game_.characterCards()[currentCharacterIndex]->owner());
			player.get_player().gold(player.get_player().gold() + game_.currentPlayer().gold());
			game_.currentPlayer().gold(0);
			game_.sendToCurrentPlayer("je hebt op het moment " + std::to_string(game_.currentClient().get_player().gold()) + " goudstukken");
		}


		//printChooseStateOptions();
		chooseState();
		drawBuildingCards();
	}
	else
	{
		//todo: niet netjes
		placedBuildingCard_ = true;
		usedCharacterCard_ = true;
		foldBuildingCard_ = false;
		initState_ = true;
		currentCharacterIndex = -1;
	}
}

bool PlayingState::act(ClientInfo& clientInfo,std::string cmd)
{
	//er is iets fout gegaan
	if (currentCharacterIndex == -1) {
		onLeave();
		return false;
	}
	else {
		switch (currentState_)
		{
		case PlayingState::InitState:
			if (initState(clientInfo, cmd)) {
				initState_ = true;
				currentState_ = PlaceBuildingCard;
				prevState_ = PlaceBuildingCard;
				chooseState();
			};
			break;
		case PlayingState::PlaceBuildingCard:
			if (placeBuildingCard(clientInfo, cmd))
			{
				if (game_.characterCards()[currentCharacterIndex]->usable()) {
					currentState_ = OptCharacterState;
					prevState_ = OptCharacterState;
					chooseState();
					return true;
				}
				onLeave();
			}
			break;
		case PlayingState::OptCharacterState:
			if (optCharacterState(clientInfo,cmd))
			{
				onLeave();
			}
			break;
		case PlayingState::UseCharacterCard:
			if (useCharacterCard(clientInfo, cmd))
			{
				currentState_ = prevState_;
				if (currentState_ == OptCharacterState && !game_.characterCards()[currentCharacterIndex]->usable()) {
					onLeave();
					return true;
				}
				chooseState();
			}
			break;
		case PlayingState::FoldBuildingCard:
			if (foldBuildingCard(clientInfo, cmd))
			{
				currentState_ = PlaceBuildingCard;
				prevState_ = PlaceBuildingCard;
				chooseState();
			}
			break;
		}

		//todo:leave
		if (placedBuildingCard_ && usedCharacterCard_ && initState_) {
			//onLeave();
			return true;
		}
		else {
			//todo: print options
			//game_.sendToCurrentPlayer("\r\n\r\n\r\n");
			//chooseState();
		}
	}
	return false;
}

void PlayingState::onLeave()
{
	int count = 0;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == game_.currentClient().get_player().ownertag() && card.active()) {
			count++;
		}
	});
	if (count >= 8) {
		if (game_.characterCards()[currentCharacterIndex]->owner() == Owner::Player1) {
			game_.sendToAllPlayers("speler 1 heeft acht steden gebouwd en krijgt 4 punten");
			game_.currentClient().get_player().addPoints(4);
		}
		else {
			game_.sendToAllPlayers("speler 2 heeft acht steden gebouwd en krijgt 4 punten");
		}
		game_.sendToAllPlayers("na deze ronde zal het spel stoppen en bepaalt worden wie er gewonnen heeft");
		lastround = true;
	}

	game_.characterCards()[currentCharacterIndex]->owner(Owner::None);
	onEnter();
	if (currentCharacterIndex == -1) 
	{
		
		std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](std::unique_ptr<CharacterCard>& card) 
		{
			card->owner(Owner::Deck);
			card->onLeave();
		});
		std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
		{
			if (card.owner() == Owner::None) {
				card.owner(Owner::Deck);
			}
		});
		if (!lastround) {
			game_.setState(Game::DealCards);
			game_.currentState().onEnter();
		}
		else {
			//todo: stop spel
			endGame();
		}
	}
}


PlayingState::~PlayingState()
{
}

bool PlayingState::initState(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = std::stoi(cmd);
		if (cmdi == -1 && game_.characterCards()[currentCharacterIndex]->usable()) {
			currentState_ = UseCharacterCard;
			chooseState();
		}
		
		else if (cmdi == 1){
			game_.currentPlayer().gold(game_.currentPlayer().gold() + 2);
			return true;
		}
		else if (cmdi == 2) {
			currentState_ = FoldBuildingCard;
			prevState_ = FoldBuildingCard;
			chooseState();
			return false;
		}
		else
		{
			this->game_.sendToCurrentPlayer("ongeldige input \r\n");
			onEnter();
		}
	}
	return false;
}

bool PlayingState::optCharacterState(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = stoi(cmd);
		if (cmdi == 1) {
			currentState_ = UseCharacterCard;
			chooseState();
		}
		else {
			return true;
		}
	}
	return false;
}

void PlayingState::chooseState()
{
	game_.sendToCurrentPlayer("");
	printChooseStateOptions();
	if (currentState_ == InitState) {
		game_.currentClient().get_socket() << "kies een van de volgende opties\r\n";
		game_.currentClient().get_socket() << "1: pak 2 goudstukken\r\n";
		game_.currentClient().get_socket() << "2: pak 1 gebouwkaart en leg een weg\r\n";
		if (game_.characterCards()[currentCharacterIndex]->usable()) {
			game_.currentClient().get_socket() << "-1: gebruik karakterkaart\r\n";
		}
	}
	else if (currentState_ == FoldBuildingCard) {
		//drawBuildingCards();
		printDrawnBuildingCards();
		if (game_.characterCards()[currentCharacterIndex]->usable()) {
			game_.currentClient().get_socket() << "-1: gebruik karakterkaart\r\n";
		}
	}
	else if (currentState_ == PlaceBuildingCard) {
		printAvailableBuildingCards();
		if (game_.characterCards()[currentCharacterIndex]->usable()) {
			game_.currentClient().get_socket() << "-1: gebruik karakterkaart\r\n";
		}
	}
	else if (currentState_ == UseCharacterCard) {
		game_.characterCards()[currentCharacterIndex]->onEnter();
	}
	else if (currentState_ == OptCharacterState) {
		game_.sendToCurrentPlayer("de karakterkaart kan nog gebruikt worden wil je de kaart nu gebruiken?");
		game_.sendToCurrentPlayer("1: ja");
		game_.sendToCurrentPlayer("2: nee");
	}
	else {
		game_.currentClient().get_socket() << "ongeldige keuze\r\n";
	}
	
}

bool PlayingState::placeBuildingCard(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty())
	{
		int cmdi = stoi(cmd) - 1;
		if (cmdi == -1) {
			return true;
		}
		
		if (cmdi == -2 && game_.characterCards()[currentCharacterIndex]->usable())
		{
			currentState_ = UseCharacterCard;
			chooseState();
			return false;
		}
		//todo: out of range error
		else if (cmdi < 0 || cmdi >= game_.buildingCards().size()) {
			game_.sendToCurrentPlayer("Je kunt deze kaart niet kiezen.");
			return false;
		}
		BuildingCard& chosenCard = game_.buildingCards().at(cmdi);
		if (chosenCard.owner() != game_.currentPlayer().ownertag() || chosenCard.active()) {
			//game_.sendToCurrentPlayer("Chosen card is not in your possession, please choose a card in your possession \r\n");
			game_.sendToCurrentPlayer("Je kan deze kaart niet kiezen.");
			printAvailableBuildingCards();
			return false;
		}
		else {
			if (chosenCard.cost() > game_.currentPlayer().gold()) {
				game_.sendToCurrentPlayer("Je hebt niet genoeg goud voor de gekozen gebouwenkaart.");
				printAvailableBuildingCards();
				return false;
			}
			else {
				game_.currentPlayer().gold(game_.currentPlayer().gold() - chosenCard.cost());
				chosenCard.active(true);
				placedBuildingCard_ = true;
				return true;
			}
		}
	}

	game_.sendToCurrentPlayer("Ongeldige input.");
	printAvailableBuildingCards();
	return false;
}



//todo: kan mooier?
bool PlayingState::useCharacterCard(ClientInfo & clientInfo, std::string cmd)
{
	return game_.characterCards()[currentCharacterIndex]->act(clientInfo,cmd);
}

bool PlayingState::foldBuildingCard(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = stoi(cmd);
		if (cmdi == -1 && game_.characterCards()[currentCharacterIndex]->usable()) {
			currentState_ = UseCharacterCard;
			chooseState();
		}
		else if (cmdi == 1) {
			drawnBuildingCard1->owner(game_.currentPlayer().ownertag());
			drawnBuildingCard1 = nullptr;
			drawnBuildingCard2->owner(Owner::None);
			drawnBuildingCard2 = nullptr;
			return true;
		}
		else if (cmdi == 2) {
			drawnBuildingCard2->owner(game_.currentPlayer().ownertag());
			drawnBuildingCard2 = nullptr;
			drawnBuildingCard1->owner(Owner::None);
			drawnBuildingCard1 = nullptr;
			return true;
		}
		else {
			game_.sendToCurrentPlayer("Verkeerde keuze, kies kaart 1 of 2");
			return false;
		}
	}
	return false;
}

BuildingCard & PlayingState::getRandomBuildingCardFromDeck() const
{
	std::vector<int> unused;
	int count = 0;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == Owner::Deck) {
			unused.push_back(count);
		}
		count++;
	});
	int randomint = random_int(0, unused.size() -1);
	return game_.buildingCards().at(unused.at(randomint));

}

void PlayingState::printAvailableBuildingCards() const
{
	game_.sendToCurrentPlayer("Beschikbare kaarten: ");
	printCurrentPlayerBuildingCardsNonActive();
	game_.sendToCurrentPlayer("Toets 0 om geen gebouwen te plaatsen.");
}

void PlayingState::printCurrentPlayerBuildingCardsActive() const
{
	int count = 1;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == game_.currentPlayer().ownertag() && card.active()) {
			game_.sendToCurrentPlayer("\t" + std::to_string(count) + "| Kaartnaam: " + card.name() + "| Kosten: " + std::to_string(card.cost()) +
				"| kleur: " + card.colorString());
		}
		count++;
	});
}

void PlayingState::calcPoints()
{
	calcColorPoints();
	calcBuildingPoints();
}

void PlayingState::calcColorPoints()
{
	auto& p1 = game_.client1().get_player();
	auto& p2 = game_.client2().get_player();
	if (p1.hasAllColors(game_)) {
		game_.sendToAllPlayers("speler1 bezit van alle kleuren minstens 1 gebouw en krijgt daarmee 3 punten");
		p1.addPoints(3);
	}
	if (p2.hasAllColors(game_)) {
		game_.sendToAllPlayers("speler2 bezit van alle kleuren minstens 1 gebouw en krijgt daarmee 3 punten");
		p2.addPoints(3);
	}
}

void PlayingState::calcBuildingPoints()
{
	//todo: calc point for building;
	auto& player1 = game_.client1().get_player();
	auto& player2 = game_.client2().get_player();

	int countP1 = player1.countBuildings(game_);
	int countP2 = player2.countBuildings(game_);


	if (countP1 >= 8) {
		game_.sendToAllPlayers("speler 1 heeft 8 gebouwen en krijgt daarmee 2 punten");
		player1.addPoints(2);
	}

	if (countP2 >= 8) {
		game_.sendToAllPlayers("speler 2 heeft 8 gebouwen en krijgt daarmee 2 punten");
		player2.addPoints(2);
	}
	//todo: correct?
	int bp1 = player1.countBuidlingPounts(game_);
	int bp2 = player2.countBuidlingPounts(game_);
	game_.sendToAllPlayers("de volgende punten worden berekent op basis van de kosten van de geplaatste gebouwen");
	game_.sendToAllPlayers("speler 1 krijgt " + std::to_string(bp1) + " punten");
	player1.addPoints(bp1);
	game_.sendToAllPlayers("speler 2 krijgt " + std::to_string(bp2) + " punten");
	player2.addPoints(bp2);
}

void PlayingState::endGame()
{
	calcPoints();
	int p1 = game_.client1().get_player().points();
	int p2 = game_.client2().get_player().points();

	game_.sendToAllPlayers("speler 1 heeft " + std::to_string(p1) + "punten");
	game_.sendToAllPlayers("speler 2 heeft " + std::to_string(p2) + "punten");

	if (p1 > p2) {
		game_.sendToAllPlayers("speler 1 heeft de meeste punten en wint daarmee het spel");
	}
	else if (p2 > p1) {
		game_.sendToAllPlayers("speler 2 heeft de meeste punten en wint daarmee het spel");
	}
	else {
		game_.sendToAllPlayers("gelijk spel");
	}
	game_.endGame();
}

void PlayingState::printCurrentPlayerBuildingCardsNonActive() const
{
	int count = 1;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == game_.currentPlayer().ownertag() && !card.active()) {
			game_.sendToCurrentPlayer("\t" + std::to_string(count) + "| Kaartnaam: " + card.name() + "| Kosten: " + std::to_string(card.cost()) +
				"| kleur: " + card.colorString());
		}
		count++;
	});
}

void PlayingState::printDrawnBuildingCards() {
	game_.sendToCurrentPlayer("Je hebt de volgende kaarten getrokken:");
	game_.sendToCurrentPlayer("1| Kaartnaam: " + drawnBuildingCard1->name() + "| Kosten: " + std::to_string(drawnBuildingCard1->cost()) +
		"| kleur: " + drawnBuildingCard1->colorString());
	game_.sendToCurrentPlayer("2| Kaartnaam: " + drawnBuildingCard2->name() + "| Kosten: " + std::to_string(drawnBuildingCard2->cost()) +
		"| kleur: " + drawnBuildingCard2->colorString());
	game_.sendToCurrentPlayer("Kies een van de 2 kaarten om te houden, de andere word weggelegd");
	foldBuildingCard_ = true;
}

void PlayingState::drawBuildingCards()
{
	drawnBuildingCard1 = &getRandomBuildingCardFromDeck();
	drawnBuildingCard1->owner(Owner::None);
	drawnBuildingCard2 = &getRandomBuildingCardFromDeck();
	drawnBuildingCard2->owner(Owner::None);
}

void PlayingState::printChooseStateOptions()
{
	game_.sendToCurrentPlayer("je hebt op het moment deze kaarten in je hand");
	printCurrentPlayerBuildingCardsNonActive();
	game_.sendToCurrentPlayer("je stad bestaat op het moment uit deze gebouwen");
	printCurrentPlayerBuildingCardsActive();
	game_.sendToCurrentPlayer("je hebt op het moment " + std::to_string(game_.currentClient().get_player().gold()) + " goudstukken");
}
