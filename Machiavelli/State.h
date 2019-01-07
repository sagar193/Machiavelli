#pragma once
#include "Player.h"
#include "CharacterCard.h"

class State
{
public:
	State();
	~State();
	virtual void onEnter( Player& player,const Game& game)  = 0;
	//void onEnter(const Player& player, std::vector<std::unique_ptr<CharacterCard>> characters);
	//void onEnter(const Player& player, std::vector<std::unique_ptr<CharacterCard>> characters);
};

