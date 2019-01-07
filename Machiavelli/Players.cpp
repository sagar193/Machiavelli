#include "pch.h"
#include "Players.h"


Players::Players()
{
	player1_ = nullptr;
	player2_ = nullptr;
	current_player_ = NONE;
	map_[PLAYER1] = player1_;
	map_[PLAYER2] = player2_;
	map_[NONE] = nullptr;
}

Players::~Players()
= default;

Player & Players::get_player1() const
{
	return *player1_;
}

Player & Players::get_player2() const
{
	return *player2_;
}

Player & Players::get_current_player() const
{
	return *map_.at(PLAYER1);
}

void Players::set_current_player(player player)
{
	current_player_ = player;
}

void Players::set_player(Player & new_player)
{
	if(player1_ != nullptr)
	{
		player1_ = &new_player;
	} 
	else if(player2_ != nullptr)
	{
		player2_ = &new_player;
	}
	else
	{
		new_player.socket().write("Sorry de lobby is vol\r\n");
	}
}

