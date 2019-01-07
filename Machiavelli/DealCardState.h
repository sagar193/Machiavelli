#pragma once
#include "State.h"

class DealCardState : public State
{
public:
	DealCardState();
	~DealCardState();
	void enter(Game& game) override;
	bool act(std::string cmd, Game& game) override;
private:
	enum activity
	{
		picking_cards,
		putting_cards_away,
	};
	activity current_activity_;
	void set_current_player(Game & game) const;
	void print_dialogue(Game& game) const;
	bool pick_card(Game& game);
};

