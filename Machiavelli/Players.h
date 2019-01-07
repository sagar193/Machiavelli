#pragma once
#include "Player.h"
#include <map>

class Players
{
public:
	enum player
	{
		PLAYER1,
		PLAYER2,
		NONE
	};
	Players();
	Players(Players& other) = delete;
	Players(Players&& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;

	~Players();
	Player& get_player1() const;
	Player& get_player2() const;
	Player& get_current_player() const;
	void set_current_player(player player);
	void set_player(Player& new_player);
private:
	Player* player1_;
	Player* player2_;
	player current_player_;
	std::map<player, Player*> map_;
};

