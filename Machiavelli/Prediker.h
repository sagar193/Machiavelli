#pragma once
#include "CharacterCard.h"
#include <algorithm>

class Prediker : public CharacterCard
{
private:
	std::string name_;
	bool used_;
public:
	Prediker(Game& game);
	~Prediker();

	void onEnter() override;
	bool act(ClientInfo& clientInfo, std::string cmd) override;
	void onLeave() override;

	void name(std::string const name) override;
	std::string const name() const override;
	bool usable() const override;

	void removeBuildingCard(int index) override;
};

