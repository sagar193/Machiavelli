#pragma once
#include "CharacterCard.h"

class Condottiere : public CharacterCard
{
private:
	std::string name_;
	int rank_;
	bool canChoose;
	void printOtherPlayerBuildingCards();
public:
	Condottiere(Game& game);
	~Condottiere();
	void onEnter() override;
	void onLeave() override;
	bool act(ClientInfo& clientInfo, std::string cmd) override;
	void rank(int const rank) override;
	int const rank() const override;
	void name(std::string const name) override;
	std::string const name() const override;
};

