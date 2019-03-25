#include "pch.h"
#include "Moordenaar.h"
#include "ClientInfo.h"

Moordenaar::Moordenaar(Game& game) : CharacterCard(game)
{
	this->name_ = "Moordenaar";
	this->inputState_ = false;
}


Moordenaar::~Moordenaar()
{
}

bool Moordenaar::act(ClientInfo & clientInfo, std::string cmd)
{
	if (inputState_ == true)
	{

	}
	else
	{
		this->game_.sendToCurrentPlayer("Welke karakter wil je vermoorden?");
		
		int count = 1;
		std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](const std::unique_ptr<CharacterCard>& card)
		{
			game_.sendToCurrentPlayer( std::to_string(count) + ": " + card->name());
			
			count++;
		});
	}
	return false;
}


void Moordenaar::rank(int const rank)
{
	rank_ = rank;
}

int const Moordenaar::rank() const
{
	return rank_;
}

void Moordenaar::name(std::string const name)
{
	name_ = name;
}

std::string const Moordenaar::name() const
{
	return name_;
}
