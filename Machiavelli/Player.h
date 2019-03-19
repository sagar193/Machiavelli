//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <string>
#include "Socket.h"
#include "CharacterCard.h"

class Player {
public:
	Player();
	//todo: in cpp
	Player(const std::string& name_, const int age) : name_{ name_ }, age_{ age } 
	{ 
		isKing_ = false; 
		gold_ = 0; 
		ownertag_ = CharacterCard::None;
	}

	//todo: rule of fif
	//Player& operator=(Player & other) = delete;
	//Player(const Player & other) = delete;
    std::string const name() const;
	void name(const std::string& new_name);
	int const age() const;
	//void socket(Socket& const socket) { socket_ = &socket; }
	//Socket& const socket() { return *socket_; }
	bool isKing() { return isKing_; }
	void isKing(bool isKing) { this->isKing_ = isKing; }
	int gold() { return gold_; }
	void gold(int gold) { gold_ = gold; }
	CharacterCard::Owner ownertag() { return ownertag_; }
	void ownertag(CharacterCard::Owner owner) { ownertag_ = owner; }


private:
	//todo: socket pointer reference?
	//todo: vector?
	CharacterCard::Owner ownertag_;
	bool isKing_;
	int gold_;
    std::string name_;
	int age_;
};

#endif /* Player_hpp */
