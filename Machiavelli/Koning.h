#pragma once
#include "CharacterCard.h"

class Koning : public CharacterCard
{
private:
	std::string name_;
	bool usable_;

public:
	Koning(Game& game);
	~Koning();

	void onEnter() override;
	void onLeave() override;
	bool act(ClientInfo& clientInfo, std::string cmd) override;

	void name(std::string const name) override;
	std::string const name() const override;
	bool usable() const override;
};

