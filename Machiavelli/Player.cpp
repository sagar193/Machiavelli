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

std::string const Player::name() const
{
	return name_;
}

void Player::name(const std::string& new_name)
{
	name_ = new_name;
	gold_ = 0;
	king_ = false;
}

int Player::age() const
{
	return age_;
}

void Player::makeKing()
{
	king_ = true;
}

void Player::unKing()
{
	king_ = false;
}


