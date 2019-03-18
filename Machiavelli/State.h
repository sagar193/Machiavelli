#pragma once
#include "Game.h"
class State
{
public:
	//State(Game& game);
	virtual void onEnter() = 0;
	virtual void act(std::string cmd) = 0;
	virtual void onLeave() = 0;
private:
	//Game& game_;
};

