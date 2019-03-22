//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "pch.h"
#include "Player.h"
using namespace std;

Player::Player() {
	ownertag_ = Owner::None;
	isKing_ = false;
	gold_ = 0;
}

std::string const Player::name() const
{
	return name_;
}

void Player::name(const std::string& new_name)
{
	name_ = new_name;
}

int const Player::age() const
{
	return age_;
}
