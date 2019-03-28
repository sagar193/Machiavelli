#pragma once
#include <string>
#include "Owner.h"
#include "State.h"
#include "CharacterCardEnum.h"

class ClientInfo;
class Game;
class CharacterCard : public State
{
public:
	CharacterCard(Game& game);
	
	virtual void onEnter() override = 0;
	virtual bool act(ClientInfo& clientInfo, std::string cmd) override = 0;
	virtual void onLeave() override = 0;

	virtual void rank(int const rank) = 0;
	virtual int const rank() const = 0;
	virtual void name(std::string const name) = 0;
	virtual std::string const name() const = 0;
	Owner owner() const { return owner_; }
	void owner(Owner owner) { owner_ = owner; }
	bool mugged() const { return mugged_; };
	virtual bool mugged(bool const mugged) { mugged_ = mugged; return true; }

	virtual void removeBuildingCard(int index);
	CharacterCardEnum characterCardIdentifier() { return characterCardIdentifier_; }
	virtual ~CharacterCard() {};

private:
	Owner owner_;

protected:
	bool mugged_;
	CharacterCardEnum characterCardIdentifier_;
};

