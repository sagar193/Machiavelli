#pragma once
#include "State.h"

class PlayerTurnState : public State
{
public:
	PlayerTurnState();
	void enter(Game& game) override;
	bool act(std::string cmd, Game& game) override;
	~PlayerTurnState();
private:
	enum activity
	{
		draw,
		use_character_card,
		build
	};
	int current_character_;
};


