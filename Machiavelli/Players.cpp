#include "pch.h"
#include "Players.h"


Players::Players()
{
	player1_ = nullptr;
	player2_ = nullptr;
	current_player_ = PLAYER1;
	//map_[PLAYER1] = player1_;
	//map_[PLAYER2] = player2_;
	count_players_ = 0;
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

Player & Players::get_current_player_value() const
{
	if(current_player_ == PLAYER1)
	{
		return get_player1();
	}
	return get_player2();
}

Players::player Players::get_current_player_code() const
{
	return current_player_;
}

Player & Players::get_other_player_value() const
{
	if(current_player_ == PLAYER1)
	{
		return *player2_;
	}
//	if(current_player_ == PLAYER2)
//	{
		return *player1_;
//	}
//	throw std::exception("No character selected.");
}

Players::player Players::get_other_player_code() const
{
	if(current_player_ == PLAYER1)
	{
		return PLAYER2;
	}
	return PLAYER1;
}

void Players::set_current_player(player player)
{
	current_player_ = player;
}

void Players::set_player(Player & new_player)
{
	if(player1_ == nullptr)
	{
		player1_ = &new_player;
		count_players_++;
		map_[player1_] = PLAYER1;
	} 
	else if(player2_ == nullptr)
	{
		player2_ = &new_player;
		count_players_++;
		map_[player2_] = PLAYER2;
	}
	else
	{
		new_player.socket().write("Sorry de lobby is vol\r\n");
		throw std::exception("lobby is full");
	}
}

void Players::send_message_to_all_players(const std::string msg) const
{
	player1_->socket() << msg;
	player2_->socket() << msg;
}

void Players::switch_current_player()
{
	if(current_player_ == PLAYER1)
	{
		current_player_ = PLAYER2;
	}
	else
	{
		current_player_ = PLAYER1;
	}
}

int Players::get_count_players() const
{
	return count_players_;
}

bool Players::is_current_player(Player & player) const
{
	return map_.at(&player) == current_player_;
}

