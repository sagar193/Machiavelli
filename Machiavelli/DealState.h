#pragma once
#include "State.h"

class DealState : State
{
public:
	DealState();
	~DealState();
	void onEnter(Player& player, const Game& game) override;
};

