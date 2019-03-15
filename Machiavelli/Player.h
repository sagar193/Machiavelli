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

class Player {
public:
	Player() = delete;
	Player(const std::string name, const int age) : name_{ name }, age_{ age }, king_{ false }, gold_{ 0 }, socket_{nullptr} {}

    std::string const name() const;
	void name(const std::string& new_name);
	int age() const;
	void socket(Socket& socket) { socket_ = &socket; }
	Socket& socket() { return *socket_; }
	
	////////////////////////////////////////////////
	void ad_gold(const int gold) { gold_ += gold; }
	int gold() const { return gold_; }
	void makeKing();
	void unKing();
	bool king() const { return king_; }
	void print_line() const { *socket_ << "==============================\r\n"; }
private:
    std::string name_;
	int age_;
	Socket* socket_;
	
	////////////////////////////////////////////////
	bool king_;
	int gold_;
};

#endif /* Player_hpp */
