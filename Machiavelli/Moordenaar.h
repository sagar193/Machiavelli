#pragma once
#include "CharacterCard.h"

class Moordenaar : public CharacterCard
{
private:
	std::string name_;
	int rank_;

public:
	Moordenaar(Game& game);
	~Moordenaar();

	void onEnter() override {};
	void onLeave() override {};
	bool act(ClientInfo& clientInfo, std::string cmd) override;

	void rank(int const rank) override;
	int const rank() const override;
	void name(std::string const name) override;
	std::string const name() const override;
};

