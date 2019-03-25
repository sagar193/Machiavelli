#include "pch.h"
#include "Moordenaar.h"


Moordenaar::Moordenaar() : CharacterCard()
{
	this->name_ = "Moordenaar";
	this->inputState_ = false;
}


Moordenaar::~Moordenaar()
{
}

void Moordenaar::act()
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
