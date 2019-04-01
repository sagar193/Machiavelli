#pragma once
#include "CharacterCard.h"

class Magier : public CharacterCard
{
private:
	std::string name_;
	bool usable_;

public:
	Magier(Game& game);
	~Magier();

	void onEnter() override;
	void onLeave() override;
	bool act(ClientInfo& clientInfo, std::string cmd) override;

	void name(std::string const name) override;
	std::string const name() const override;
	bool usable() const override;
};

