#pragma once
#include "CharacterCard.h"

class Koopman : public CharacterCard
{
private:
	std::string name_;
	int rank_;
	bool used_;

public:
	Koopman(Game& game);
	~Koopman();

	void onEnter() override;
	void onLeave() override;
	bool act(ClientInfo& clientInfo, std::string cmd) override;

	void rank(int const rank) override;
	int const rank() const override;
	void name(std::string const name) override;
	std::string const name() const override;
};

