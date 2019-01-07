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
		choosing,
		drawing,
		using_character_card,
		building,
		looking
	};
	activity current_activity_;
	int current_character_;
	int character_stolen_;

	bool has_drawn;
	bool has_used_card;
	bool has_build;

	void print_act_choosing(Game& game);
	void act_choosing(std::string cmd, Game& game);
	void print_act_drawing(Game& game);
	void act_drawing(std::string cmd, Game& game);
	
	void act_using_character_card(std::string cmd, Game& game);
	void print_act_building(Game& game);
	void act_building(std::string cmd, Game& game);
	void act_looking(std::string cmd, Game& game);

	void set_current_player(Game& game);
	void print_start_dialogue(Game& game) const;
};


