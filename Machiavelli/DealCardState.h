#pragma once
#include "State.h"

class DealCardState : State
{
public:
	DealCardState();
	~DealCardState();
	void enter(Game& game) override;
	bool act(Game& game) override;
private:
	void set_current_player(Game & game);
};

