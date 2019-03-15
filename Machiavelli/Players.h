#pragma once
#include "Player.h"
#include <map>
#include "CardOwners.h"

class Players
{
public:
	enum player
	{
		PLAYER1,
		PLAYER2,
	};
	Players();
	Players(Players& other) = delete;
	Players(Players&& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;
	~Players();

	Player& get_player1() const;
	Player& get_player2() const;
	Player& get_current_player_value() const;
	player get_current_player_code() const;
	CardOwners get_player_owner_code(player player) const;
	Player& get_other_player_value() const;
	player get_other_player_code() const;
	
	void set_current_player(player player);
	void set_player(Player& new_player);

	void send_message_to_all_players(const std::string msg) const;
	void switch_current_player();

	int get_count_players() const;

	bool is_current_player(Player& player) const;
private:
	Player* player1_;
	Player* player2_;
	player current_player_;
	std::map<Player*,player> map_;
	int count_players_;
};

