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
	Player(const std::string& name_, const int age) : name_{ name_ }, age_{ age } {}

    std::string const name() const;
	void name(const std::string& new_name);
	int const age() const;
	void socket(Socket& const socket) { socket_ = &socket; }
	Socket& const socket() { return *socket_; }

private:
    std::string name_;
	int age_;
	Socket* socket_;
};

#endif /* Player_hpp */
