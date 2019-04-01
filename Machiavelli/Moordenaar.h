#pragma once
#include "CharacterCard.h"

class Moordenaar : public CharacterCard
{
private:
	std::string name_;
	bool usable_;

public:
	Moordenaar(Game& game);
	~Moordenaar();

	void onEnter() override;
	void onLeave() override;
	bool act(ClientInfo& clientInfo, std::string cmd) override;

	bool mugged(bool const mugged) override;
	void name(std::string const name) override;
	std::string const name() const override;
	bool usable() const override;

	void printAllCharacters() const;
};

