#pragma once
#include "Game.h"
class State
{
public:
	State(Game& game);
	virtual void onEnter() = 0;
	virtual bool act(ClientInfo& clientInfo, std::string cmd) = 0;
	virtual void onLeave() = 0;
protected:
	Game& game_;
};

