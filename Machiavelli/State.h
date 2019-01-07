#pragma once
#include "Player.h"
#include "CharacterCard.h"

class State
{
public:
	State();
	virtual ~State();
	virtual void enter(Game& game)  = 0;
	virtual bool act(std::string cmd, Game& game) = 0;
};

