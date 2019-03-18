#pragma once
#include "State.h"

class PlayingState : State
{
public:
	PlayingState(Game& game);
	void onEnter() override;
	void act(std::string cmd) override;
	void onLeave() override;
	~PlayingState();
};

