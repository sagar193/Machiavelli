#pragma once
#include "State.h"

class DealCardState : State
{
public:
	DealCardState(Game& game);
	void onEnter() override;
	void act(std::string cmd) override;
	void onLeave() override;
	~DealCardState();
};

