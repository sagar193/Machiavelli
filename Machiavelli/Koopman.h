#pragma once
#include "CharacterCard.h"

class Koopman : public CharacterCard
{
private:
	std::string name_;
	bool used_;

public:
	Koopman(Game& game);
	~Koopman();

	void onEnter() override;
	void onLeave() override;
	bool act(ClientInfo& clientInfo, std::string cmd) override;

	void name(std::string const name) override;
	std::string const name() const override;
	bool usable() const override;
};

