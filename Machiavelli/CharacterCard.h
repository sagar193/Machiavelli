#pragma once
#include <string>
#include "Owner.h"

class CharacterCard : public State
{
public:
	CharacterCard();
	virtual void onEnter() override =0;
	virtual bool act(ClientInfo& clientInfo, std::string cmd) override = 0;
	virtual void onLeave() override = 0;
	virtual void rank(int const rank) = 0;
	virtual int const rank() const = 0;
	virtual void name(std::string const name) = 0;
	virtual std::string const name() const = 0;
	Owner owner() { return owner_; }
	void owner(Owner owner) { owner_ = owner; }
private:
	Owner owner_;
};

